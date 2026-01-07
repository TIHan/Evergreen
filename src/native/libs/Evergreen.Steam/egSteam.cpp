#include "steam/steam_api.h"
#include "steam/isteamnetworkingsockets.h" 
#include "steam/steamclientpublic.h"

#include "egSteam.h"

#include <queue>
#include <assert.h>

#define MAX_CONNECTIONS 256

class EgSteamNetworking_ListenSocket_Internal {
private:
	std::queue<int> connectionQueue;

	int GetNewConnectionIndex()
	{
		if (this->connectionQueue.size() > 0)
		{
			auto connectionIndex = this->connectionQueue.front();
			this->connectionQueue.pop();
			return connectionIndex;
		}

		auto connectionIndex = this->connectionCount;
		this->connectionCount++;
		return connectionIndex;
	}

public:
	int connectionCount = 0;
	HSteamNetConnection connections[MAX_CONNECTIONS] = {};

	HSteamListenSocket socket = k_HSteamListenSocket_Invalid;
	HSteamNetPollGroup pollGroup = k_HSteamNetPollGroup_Invalid;

	void RemoveConnectionIndex(int connectionIndex)
	{
		this->connections[connectionIndex] = {};
		this->connectionCount--;
		this->connectionQueue.push(connectionIndex);
	}

	void OnConnectionStatusChanged(SteamNetConnectionStatusChangedCallback_t* pCallback)
	{
		switch (pCallback->m_info.m_eState)
		{
		case ESteamNetworkingConnectionState::k_ESteamNetworkingConnectionState_Connecting:
		{
			if (this->connectionCount >= MAX_CONNECTIONS)
			{
				SteamNetworkingSockets()->CloseConnection(pCallback->m_hConn, EgDisconnectReason::ServerFull, nullptr, false);
				return;
			}

			if (SteamNetworkingSockets()->AcceptConnection(pCallback->m_hConn) == EResult::k_EResultOK)
			{
				if (!SteamNetworkingSockets()->SetConnectionPollGroup(pCallback->m_hConn, this->pollGroup))
				{
					SteamNetworkingSockets()->CloseConnection(pCallback->m_hConn, EgDisconnectReason::ServerReject, nullptr, false);
					return;
				}
				auto connectionIndex = this->GetNewConnectionIndex();
				this->connections[connectionIndex] = pCallback->m_hConn;
				SteamNetworkingSockets()->SetConnectionUserData(pCallback->m_hConn, connectionIndex);
			}
			else
			{
				SteamNetworkingSockets()->CloseConnection(pCallback->m_hConn, EgDisconnectReason::ServerReject, nullptr, false);
			}
			break;
		}
		case ESteamNetworkingConnectionState::k_ESteamNetworkingConnectionState_ClosedByPeer:
		case ESteamNetworkingConnectionState::k_ESteamNetworkingConnectionState_ProblemDetectedLocally:
		{
			if (pCallback->m_eOldState == k_ESteamNetworkingConnectionState_Connected)
			{
				auto connectionIndex = SteamNetworkingSockets()->GetConnectionUserData(pCallback->m_hConn);
				if (connectionIndex == -1)
				{
					assert(false);
					printf("[SteamNetworking] Invalid connection index encountered\n");
				}
				else
				{
					this->RemoveConnectionIndex(connectionIndex);
				}
			}
			
			SteamNetworkingSockets()->CloseConnection(pCallback->m_hConn, pCallback->m_info.m_eEndReason, nullptr, false);
			break;
		}
		default:
		{
			break;
		}
		}
	}
};

HSteamListenSocket GetHSteamListenSocket(EgSteamNetworking_ListenSocket egSocket)
{
	return ((EgSteamNetworking_ListenSocket_Internal*)egSocket.internal)->socket;
}

HSteamNetConnection GetHSteamNetConnection(EgSteamNetworking_Connection egConnection)
{
	return egConnection.internal;
}

HSteamNetPollGroup GetHSteamNetPollGroup(EgSteamNetworking_ListenSocket egSocket)
{
	return ((EgSteamNetworking_ListenSocket_Internal*)egSocket.internal)->pollGroup;
}

// REVIEW: Is there a better way to do this without a global?
EgSteamNetworking_ListenSocket_Internal* g_currentListenSocket = nullptr;
void OnServerNetConnectionStatusChanged(SteamNetConnectionStatusChangedCallback_t* pCallback)
{
	if (g_currentListenSocket)
	{
		g_currentListenSocket->OnConnectionStatusChanged(pCallback);
	}
}

void OnClientNetConnectionStatusChanged(SteamNetConnectionStatusChangedCallback_t* pCallback)
{
}

void DebugOutput(ESteamNetworkingSocketsDebugOutputType eType, const char* pMsg)
{
	printf("%s\n", pMsg);
}

extern "C" {

	EG_EXPORT bool egSteam_Initialize(EgSteam_InitializeOptions& options)
	{
		if (!SteamAPI_Init())
			return false;

		if ((options.flags & EgSteam_InitializeFlags::InitializeRelayNetworkAccess) != EgSteam_InitializeFlags::None)
		{
			SteamNetworkingUtils()->InitRelayNetworkAccess();
		}

		if ((options.flags & EgSteam_InitializeFlags::DebugOutputEnabled) != EgSteam_InitializeFlags::None)
		{
			SteamNetworkingUtils()->SetDebugOutputFunction(ESteamNetworkingSocketsDebugOutputType::k_ESteamNetworkingSocketsDebugOutputType_Verbose, DebugOutput);
		}

		return true;
	}

	EG_EXPORT void egSteam_Shutdown()
	{
		SteamAPI_Shutdown();
	}

	EG_EXPORT void egSteam_RunCallbacks()
	{
		SteamAPI_RunCallbacks();
	}

	EG_EXPORT void egSteamNetworking_RunCallbacks()
	{
		SteamNetworkingSockets()->RunCallbacks();
	}

	EG_EXPORT EgSteamNetworking_ListenSocket egSteamNetworking_CreateListenSocketIP(EgSteamNetworking_CreateListenSocketOptions& options)
	{
		if (g_currentListenSocket)
		{
			return {};
		}

		SteamNetworkingIPAddr addr = {};
		addr.Clear();
		addr.m_port = options.port;

		auto egInternalSocket = new EgSteamNetworking_ListenSocket_Internal();

		SteamNetworkingConfigValue_t opt0 = {};
		opt0.SetPtr(k_ESteamNetworkingConfig_ConnectionUserData, egInternalSocket);
		opt0.SetPtr(k_ESteamNetworkingConfig_Callback_ConnectionStatusChanged, OnServerNetConnectionStatusChanged);
		SteamNetworkingConfigValue_t opts[1] = {};
		opts[0] = opt0;
		
		egInternalSocket->pollGroup = SteamNetworkingSockets()->CreatePollGroup();
		egInternalSocket->socket = SteamNetworkingSockets()->CreateListenSocketIP(addr, 1, opts);

		EgSteamNetworking_ListenSocket egSocket = {};
		egSocket.internal = egInternalSocket;

		g_currentListenSocket = egInternalSocket;

		return egSocket;
	}

	EG_EXPORT EgSteamNetworking_ListenSocket egSteamNetworking_CreateListenSocketP2P(EgSteamNetworking_CreateListenSocketOptions& options)
	{
		if (g_currentListenSocket)
		{
			return {};
		}

		auto egInternalSocket = new EgSteamNetworking_ListenSocket_Internal();

		SteamNetworkingConfigValue_t opt0 = {};
		opt0.SetPtr(k_ESteamNetworkingConfig_ConnectionUserData, egInternalSocket);
		opt0.SetPtr(k_ESteamNetworkingConfig_Callback_ConnectionStatusChanged, OnServerNetConnectionStatusChanged);
		SteamNetworkingConfigValue_t opts[1] = {};
		opts[0] = opt0;

		egInternalSocket->pollGroup = SteamNetworkingSockets()->CreatePollGroup();
		egInternalSocket->socket = SteamNetworkingSockets()->CreateListenSocketP2P(options.port, 1, opts);

		EgSteamNetworking_ListenSocket egSocket = {};
		egSocket.internal = egInternalSocket;

		g_currentListenSocket = egInternalSocket;

		return egSocket;
	}

	EG_EXPORT bool egSteamNetworking_CloseListenSocket(EgSteamNetworking_ListenSocket egSocket)
	{
		auto socket = GetHSteamListenSocket(egSocket);
		auto pollGroup = GetHSteamNetPollGroup(egSocket);

		auto numConnections = egSteamNetworking_GetConnectionCount(egSocket);
		for (auto i = 0; i < numConnections; i++)
		{
			auto connection = egSteamNetworking_GetConnection(egSocket, i);
			egSteamNetworking_CloseConnection(connection);
		}

		auto result = SteamNetworkingSockets()->DestroyPollGroup(pollGroup);
		result = SteamNetworkingSockets()->CloseListenSocket(socket) && result;

		delete egSocket.internal;

		g_currentListenSocket = nullptr;

		return result;
	}

	EG_EXPORT bool egSteamNetworking_IsListenSocketInvalid(EgSteamNetworking_ListenSocket egSocket)
	{
		if (!egSocket.internal)
			return true;
		return GetHSteamListenSocket(egSocket) == k_HSteamListenSocket_Invalid;
	}

	EG_EXPORT EgSteamNetworking_Connection egSteamNetworking_ConnectIP(EgSteamNetworking_ConnectOptions& options)
	{
		SteamNetworkingIPAddr addr = {};
		if (!SteamNetworkingUtils()->SteamNetworkingIPAddr_ParseString(&addr, options.address))
		{
			return {};
		}
		addr.m_port = options.port;

		SteamNetworkingConfigValue_t opt0 = {};
		opt0.SetPtr(k_ESteamNetworkingConfig_Callback_ConnectionStatusChanged, OnClientNetConnectionStatusChanged);
		SteamNetworkingConfigValue_t opts[1] = {};
		opts[0] = opt0;

		EgSteamNetworking_Connection egConnection = {};
		egConnection.internal = SteamNetworkingSockets()->ConnectByIPAddress(addr, 1, opts);

		return egConnection;
	}

	EG_EXPORT EgSteamNetworking_Connection egSteamNetworking_ConnectP2P(EgSteamNetworking_ConnectOptions& options)
	{
		SteamNetworkingIPAddr addr = {};
		if (!SteamNetworkingUtils()->SteamNetworkingIPAddr_ParseString(&addr, options.address))
		{
			return {};
		}
		addr.m_port = options.port;

		SteamNetworkingConfigValue_t opt0 = {};
		opt0.SetPtr(k_ESteamNetworkingConfig_Callback_ConnectionStatusChanged, OnClientNetConnectionStatusChanged);
		SteamNetworkingConfigValue_t opts[1] = {};
		opts[0] = opt0;

		SteamNetworkingIdentity identity = {};
		identity.Clear();
		identity.SetIPAddr(addr);

		EgSteamNetworking_Connection egConnection = {};
		egConnection.internal = SteamNetworkingSockets()->ConnectP2P(identity, options.port, 1, opts);

		return egConnection;
	}

	EG_EXPORT bool egSteamNetworking_CloseConnection(EgSteamNetworking_Connection egConnection)
	{
		auto connection = GetHSteamNetConnection(egConnection);

		auto connectionIndex = SteamNetworkingSockets()->GetConnectionUserData(connection);
		if (g_currentListenSocket && connectionIndex != -1)
		{
			g_currentListenSocket->RemoveConnectionIndex(connectionIndex);
		}

		return SteamNetworkingSockets()->CloseConnection(connection, EgDisconnectReason::ClientKicked, nullptr, false);
	}

	EG_EXPORT bool egSteamNetworking_IsConnectionInvalid(EgSteamNetworking_Connection egConnection)
	{
		return GetHSteamNetConnection(egConnection) == k_HSteamNetConnection_Invalid;
	}

	EG_EXPORT bool egSteamNetworking_SendMessage(EgSteamNetworking_Connection egConnection, int size, unsigned char* pData)
	{
		auto connection = GetHSteamNetConnection(egConnection);
		
		int64 messageNumber = 0;
		return SteamNetworkingSockets()->SendMessageToConnection(connection, pData, size, k_nSteamNetworkingSend_Unreliable, &messageNumber) == EResult::k_EResultOK;
	}

	EG_EXPORT int egSteamNetworking_GetConnectionCount(EgSteamNetworking_ListenSocket egSocket)
	{
		auto internal = (EgSteamNetworking_ListenSocket_Internal*)egSocket.internal;
		return internal->connectionCount;
	}

	EG_EXPORT EgSteamNetworking_Connection egSteamNetworking_GetConnection(EgSteamNetworking_ListenSocket egSocket, int connectionIndex)
	{
		if (connectionIndex < 0 || connectionIndex >= MAX_CONNECTIONS)
			return {};

		auto internal = (EgSteamNetworking_ListenSocket_Internal*)egSocket.internal;

		EgSteamNetworking_Connection egConnection = {};
		egConnection.internal = internal->connections[connectionIndex];
		return egConnection;
	}

	EG_EXPORT int egSteamNetworking_ReceiveMessageFromConnection(EgSteamNetworking_Connection egConnection, unsigned char* pBuffer)
	{
		auto connection = GetHSteamNetConnection(egConnection);

		auto msg = SteamNetworkingUtils()->AllocateMessage(0);
		auto numMsgs = SteamNetworkingSockets()->ReceiveMessagesOnConnection(connection, &msg, 1);
		if (numMsgs <= 0)
		{
			msg->Release();
			return 0;
		}

		auto bytesRead = msg->GetSize();
		memcpy(pBuffer, msg->GetData(), bytesRead);

		msg->Release();

		return bytesRead;
	}

	EG_EXPORT int egSteamNetworking_ReceiveMessageFromListenSocket(EgSteamNetworking_ListenSocket egSocket, unsigned char* pBuffer, EgSteamNetworking_Connection* pOutEgConnection)
	{
		auto pollGroup = GetHSteamNetPollGroup(egSocket);

		auto msg = SteamNetworkingUtils()->AllocateMessage(0);
		auto numMsgs = SteamNetworkingSockets()->ReceiveMessagesOnPollGroup(pollGroup, &msg, 1);
		if (numMsgs <= 0)
		{
			msg->Release();
			return 0;
		}

		EgSteamNetworking_Connection egConnection = {};
		egConnection.internal = msg->GetConnection();
		*pOutEgConnection = egConnection;

		auto bytesRead = msg->GetSize();
		memcpy(pBuffer, msg->GetData(), bytesRead);

		msg->Release();

		return bytesRead;
	}

}
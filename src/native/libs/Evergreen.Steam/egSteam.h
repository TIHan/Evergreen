#pragma once

#define EG_EXPORT __declspec(dllexport)

enum EgSteam_InitializeFlags {
	None							= 0,
	InitializeRelayNetworkAccess	= 1 << 0,
	DebugOutputEnabled              = 1 << 1,
};

typedef struct {
	EgSteam_InitializeFlags flags;
} EgSteam_InitializeOptions;

typedef struct {
	unsigned short port;
} EgSteamNetworking_CreateListenSocketOptions;

typedef struct {
	const char* address;
	unsigned short port;
} EgSteamNetworking_ConnectOptions;

enum EgDisconnectReason
{
	ClientDisconnect	= 1000 + 1,
	ServerClosed		= 1000 + 2,
	ServerReject		= 1000 + 3,
	ServerFull			= 1000 + 4,
	ClientKicked		= 1000 + 5,
};

typedef struct {
	void* internal;
} EgSteamNetworking_ListenSocket;

typedef struct {
	unsigned int internal;
} EgSteamNetworking_Connection;

extern "C" {

	EG_EXPORT bool egSteam_Initialize(EgSteam_InitializeOptions& options);
	EG_EXPORT void egSteam_Shutdown();
	EG_EXPORT void egSteam_RunCallbacks();

	EG_EXPORT void egSteamNetworking_RunCallbacks();

	EG_EXPORT EgSteamNetworking_ListenSocket egSteamNetworking_CreateListenSocketIP(EgSteamNetworking_CreateListenSocketOptions& options);
	EG_EXPORT EgSteamNetworking_ListenSocket egSteamNetworking_CreateListenSocketP2P(EgSteamNetworking_CreateListenSocketOptions& options);
	EG_EXPORT bool egSteamNetworking_CloseListenSocket(EgSteamNetworking_ListenSocket egSocket);
	EG_EXPORT bool egSteamNetworking_IsListenSocketInvalid(EgSteamNetworking_ListenSocket egSocket);

	EG_EXPORT EgSteamNetworking_Connection egSteamNetworking_ConnectIP(EgSteamNetworking_ConnectOptions& options);
	EG_EXPORT EgSteamNetworking_Connection egSteamNetworking_ConnectP2P(EgSteamNetworking_ConnectOptions& options);
	EG_EXPORT bool egSteamNetworking_CloseConnection(EgSteamNetworking_Connection egConnection);
	EG_EXPORT bool egSteamNetworking_IsConnectionInvalid(EgSteamNetworking_Connection egConnection);

	EG_EXPORT bool egSteamNetworking_SendMessage(EgSteamNetworking_Connection egConnection, int size, unsigned char* pData);
	EG_EXPORT int egSteamNetworking_GetConnectionCount(EgSteamNetworking_ListenSocket egSocket);
	EG_EXPORT EgSteamNetworking_Connection egSteamNetworking_GetConnection(EgSteamNetworking_ListenSocket egSocket, int connectionIndex);
	EG_EXPORT int egSteamNetworking_ReceiveMessageFromConnection(EgSteamNetworking_Connection egConnection, unsigned char* pBuffer);
	EG_EXPORT int egSteamNetworking_ReceiveMessageFromListenSocket(EgSteamNetworking_ListenSocket egSocket, unsigned char* pBuffer, EgSteamNetworking_Connection* pOutEgConnection);
}

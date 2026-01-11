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

enum class EgSteamFriends_AvatarLoadStatus
{
	Missing = 0,
	Loading = 1,
	Loaded  = 2,
};

// Same as steamworks 'EPersonaState'
enum class EgSteamFriends_PersonaState
{
	Offline = 0,	    // friend is not currently logged on
	Online = 1,			// friend is logged on
	Busy = 2,			// user is on, but busy
	Away = 3,			// auto-away feature
	Snooze = 4,			// auto-away for a long time
	LookingToTrade = 5,	// Online, trading
	LookingToPlay = 6,	// Online, wanting to play
	Invisible = 7,		// Online, but appears offline to friends.  This status is never published to clients.
	Max,
};

// Same as steamworks 'ELobbyType'
enum class EgLobbyType
{
	Private = 0,		// only way to join the lobby is to invite to someone else
	FriendsOnly = 1,	// shows for friends or invitees, but not in public lobby list, allows those who join to invite their own friends
	Public = 2,			// visible for friends and in lobby list
	Invisible = 3,		// returned by search, but not visible to other friends 
	//    useful if you want a user in two lobbies, for example matching groups together
	//	  a user can be in only one regular lobby, and up to two invisible lobbies
	PrivateUnique = 4,	// private, unique and does not delete when empty - only one of these may exist per unique keypair set
	// can only create from webapi
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

	EG_EXPORT unsigned long long egSteamUser_GetSteamID();
	EG_EXPORT bool egSteamUser_IsInvalidSteamID(unsigned long long egSteamID);

	EG_EXPORT EgSteamNetworking_ListenSocket egSteamNetworking_CreateListenSocketIP(unsigned short port);
	EG_EXPORT EgSteamNetworking_ListenSocket egSteamNetworking_CreateListenSocketP2P(unsigned short port);
	EG_EXPORT bool egSteamNetworking_CloseListenSocket(EgSteamNetworking_ListenSocket egSocket);
	EG_EXPORT bool egSteamNetworking_IsInvalidListenSocket(EgSteamNetworking_ListenSocket egSocket);

	EG_EXPORT EgSteamNetworking_Connection egSteamNetworking_ConnectIP(const char* address, unsigned short port);
	EG_EXPORT EgSteamNetworking_Connection egSteamNetworking_ConnectP2P(unsigned long long steamID, unsigned short port);
	EG_EXPORT bool egSteamNetworking_CloseConnection(EgSteamNetworking_Connection egConnection);
	EG_EXPORT bool egSteamNetworking_IsInvalidConnection(EgSteamNetworking_Connection egConnection);

	EG_EXPORT bool egSteamNetworking_SendMessage(EgSteamNetworking_Connection egConnection, int size, unsigned char* pData);
	EG_EXPORT int egSteamNetworking_GetConnectionCount(EgSteamNetworking_ListenSocket egSocket);
	EG_EXPORT EgSteamNetworking_Connection egSteamNetworking_GetConnection(EgSteamNetworking_ListenSocket egSocket, int connectionIndex);
	EG_EXPORT int egSteamNetworking_ReceiveMessageFromConnection(EgSteamNetworking_Connection egConnection, unsigned char* pBuffer);
	EG_EXPORT int egSteamNetworking_ReceiveMessageFromListenSocket(EgSteamNetworking_ListenSocket egSocket, unsigned char* pBuffer, EgSteamNetworking_Connection* pOutEgConnection);

	EG_EXPORT void egSteamFriends_ActivateGameOverlay(const char* dialog);
	EG_EXPORT void egSteamFriends_ActivateGameOverlayToUser(const char* dialog, unsigned long long steamID);
	EG_EXPORT void egSteamFriends_ActivateGameOverlayInviteDialog(unsigned long long steamIDLobby);
	EG_EXPORT void egSteamFriends_ActivateGameOverlayInviteDialogConnectString(const char* connectString);
	EG_EXPORT int egSteamFriends_GetFriendCount();
	EG_EXPORT unsigned long long egSteamFriends_GetFriendByIndex(int friendIndex);
	EG_EXPORT const char* egSteamFriends_GetPersonaName();
	EG_EXPORT const char* egSteamFriends_GetFriendPersonaName(unsigned long long steamFriendID);
	EG_EXPORT EgSteamFriends_PersonaState egSteamFriends_GetFriendPersonaState(unsigned long long steamFriendID);
	EG_EXPORT bool egSteamFriends_SetRichPresence(const char* key, const char* value);
	EG_EXPORT void egSteamFriends_ClearRichPresence();
	EG_EXPORT const char* egSteamFriends_GetFriendRichPresence(unsigned long long steamFriendID, const char* key);

	EG_EXPORT EgSteamFriends_AvatarLoadStatus egSteamFriends_GetLargeFriendAvatar(unsigned long long steamIDFriend, int* pOutImageHandle);
	EG_EXPORT EgSteamFriends_AvatarLoadStatus egSteamFriends_GetMediumFriendAvatar(unsigned long long steamIDFriend, int* pOutImageHandle);
	EG_EXPORT EgSteamFriends_AvatarLoadStatus egSteamFriends_GetSmallFriendAvatar(unsigned long long steamIDFriend, int* pOutImageHandle);
	EG_EXPORT bool egSteam_GetImageSize(int imageHandle, int* pOutWidth, int* pOutHeight);
	EG_EXPORT bool egSteam_GetImageRGBA(int imageHandle, int destinationSize, unsigned char* pDestinationBuffer);
}

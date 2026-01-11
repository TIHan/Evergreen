using System.Runtime.InteropServices;

namespace Evergreen.Steam.Interop;

public static unsafe partial class Methods
{
    [DllImport("Evergreen.Steam.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    [return: NativeTypeName("bool")]
    public static extern byte egSteam_Initialize([NativeTypeName("EgSteam_InitializeOptions &")] EgSteam_InitializeOptions* options);

    [DllImport("Evergreen.Steam.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egSteam_Shutdown();

    [DllImport("Evergreen.Steam.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egSteam_RunCallbacks();

    [DllImport("Evergreen.Steam.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egSteamNetworking_RunCallbacks();

    [DllImport("Evergreen.Steam.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    [return: NativeTypeName("unsigned long long")]
    public static extern ulong egSteamNetworking_GetSteamID();

    [DllImport("Evergreen.Steam.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    [return: NativeTypeName("bool")]
    public static extern byte egSteamNetworking_IsSteamIDInvalid([NativeTypeName("unsigned long long")] ulong steamID);

    [DllImport("Evergreen.Steam.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern EgSteamNetworking_ListenSocket egSteamNetworking_CreateListenSocketIP([NativeTypeName("unsigned short")] ushort port);

    [DllImport("Evergreen.Steam.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern EgSteamNetworking_ListenSocket egSteamNetworking_CreateListenSocketP2P([NativeTypeName("unsigned short")] ushort port);

    [DllImport("Evergreen.Steam.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    [return: NativeTypeName("bool")]
    public static extern byte egSteamNetworking_CloseListenSocket(EgSteamNetworking_ListenSocket egSocket);

    [DllImport("Evergreen.Steam.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    [return: NativeTypeName("bool")]
    public static extern byte egSteamNetworking_IsListenSocketInvalid(EgSteamNetworking_ListenSocket egSocket);

    [DllImport("Evergreen.Steam.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern EgSteamNetworking_Connection egSteamNetworking_ConnectIP([NativeTypeName("const char *")] sbyte* address, [NativeTypeName("unsigned short")] ushort port);

    [DllImport("Evergreen.Steam.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern EgSteamNetworking_Connection egSteamNetworking_ConnectP2P([NativeTypeName("unsigned long long")] ulong steamID, [NativeTypeName("unsigned short")] ushort port);

    [DllImport("Evergreen.Steam.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    [return: NativeTypeName("bool")]
    public static extern byte egSteamNetworking_CloseConnection(EgSteamNetworking_Connection egConnection);

    [DllImport("Evergreen.Steam.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    [return: NativeTypeName("bool")]
    public static extern byte egSteamNetworking_IsConnectionInvalid(EgSteamNetworking_Connection egConnection);

    [DllImport("Evergreen.Steam.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    [return: NativeTypeName("bool")]
    public static extern byte egSteamNetworking_SendMessage(EgSteamNetworking_Connection egConnection, int size, [NativeTypeName("unsigned char *")] byte* pData);

    [DllImport("Evergreen.Steam.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern int egSteamNetworking_GetConnectionCount(EgSteamNetworking_ListenSocket egSocket);

    [DllImport("Evergreen.Steam.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern EgSteamNetworking_Connection egSteamNetworking_GetConnection(EgSteamNetworking_ListenSocket egSocket, int connectionIndex);

    [DllImport("Evergreen.Steam.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern int egSteamNetworking_ReceiveMessageFromConnection(EgSteamNetworking_Connection egConnection, [NativeTypeName("unsigned char *")] byte* pBuffer);

    [DllImport("Evergreen.Steam.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern int egSteamNetworking_ReceiveMessageFromListenSocket(EgSteamNetworking_ListenSocket egSocket, [NativeTypeName("unsigned char *")] byte* pBuffer, EgSteamNetworking_Connection* pOutEgConnection);

    [DllImport("Evergreen.Steam.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egSteamFriends_ActivateGameOverlay([NativeTypeName("const char *")] sbyte* dialog);

    [DllImport("Evergreen.Steam.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egSteamFriends_ActivateGameOverlayToUser([NativeTypeName("const char *")] sbyte* dialog, [NativeTypeName("unsigned long long")] ulong steamID);

    [DllImport("Evergreen.Steam.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egSteamFriends_ActivateGameOverlayInviteDialog([NativeTypeName("unsigned long long")] ulong steamIDLobby);

    [DllImport("Evergreen.Steam.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egSteamFriends_ActivateGameOverlayInviteDialogConnectString([NativeTypeName("const char *")] sbyte* connectString);

    [DllImport("Evergreen.Steam.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egSteamFriends_InviteUserToGame([NativeTypeName("unsigned long long")] ulong steamIDFriend, [NativeTypeName("const char *")] sbyte* connectString);

    [DllImport("Evergreen.Steam.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern int egSteamFriends_GetFriendCount();

    [DllImport("Evergreen.Steam.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    [return: NativeTypeName("unsigned long long")]
    public static extern ulong egSteamFriends_GetFriendByIndex(int friendIndex);

    [DllImport("Evergreen.Steam.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    [return: NativeTypeName("const char *")]
    public static extern sbyte* egSteamFriends_GetPersonaName();

    [DllImport("Evergreen.Steam.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    [return: NativeTypeName("const char *")]
    public static extern sbyte* egSteamFriends_GetFriendPersonaName([NativeTypeName("unsigned long long")] ulong steamFriendID);

    [DllImport("Evergreen.Steam.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern EgSteamFriends_PersonaState egSteamFriends_GetFriendPersonaState([NativeTypeName("unsigned long long")] ulong steamFriendID);

    [DllImport("Evergreen.Steam.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    [return: NativeTypeName("bool")]
    public static extern byte egSteamFriends_SetRichPresence([NativeTypeName("const char *")] sbyte* key, [NativeTypeName("const char *")] sbyte* value);

    [DllImport("Evergreen.Steam.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egSteamFriends_ClearRichPresence();

    [DllImport("Evergreen.Steam.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    [return: NativeTypeName("const char *")]
    public static extern sbyte* egSteamFriends_GetFriendRichPresence([NativeTypeName("unsigned long long")] ulong steamFriendID, [NativeTypeName("const char *")] sbyte* key);

    [DllImport("Evergreen.Steam.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern EgSteamFriends_AvatarLoadStatus egSteamFriends_GetLargeFriendAvatar([NativeTypeName("unsigned long long")] ulong steamIDFriend, int* pOutImageHandle);

    [DllImport("Evergreen.Steam.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    [return: NativeTypeName("bool")]
    public static extern byte egSteam_GetImageSize(int imageHandle, int* pOutWidth, int* pOutHeight);

    [DllImport("Evergreen.Steam.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    [return: NativeTypeName("bool")]
    public static extern byte egSteam_GetImageRGBA(int imageHandle, int destinationSize, [NativeTypeName("unsigned char *")] byte* pDestinationBuffer);
}

#include <stdio.h>
#include<windows.h>

#include "../egSteam.h"

#undef NDEBUG // allow assertions in non-debug builds
#include <assert.h>

#define TEST_PORT 27015

void test_listen_socket_ip_creation(bool clientInitiatesDisconnect)
{
    auto server = egSteamNetworking_CreateListenSocketIP(TEST_PORT);
    auto isInvalid = egSteamNetworking_IsInvalidListenSocket(server);
    assert(!isInvalid);

    for (auto i = 0; i < 1000; i++)
    {
        egSteam_RunCallbacks();
        egSteamNetworking_RunCallbacks();
        Sleep(1);
    }

    auto client = egSteamNetworking_ConnectIP("127.0.0.1", TEST_PORT);

    auto isInvalidConnection = egSteamNetworking_IsInvalidConnection(client);
    assert(!isInvalidConnection);

    for (auto i = 0; i < 1000; i++)
    {
        egSteamNetworking_RunCallbacks();
        Sleep(1);
    }

    unsigned char inputBuffer[10] = {5,4,3,2,1,2,3,4,5,6};
    unsigned char outputBuffer[10] = {0,0,0,0,0,0,0,0,0,0};

    auto connectionCount = egSteamNetworking_GetConnectionCount(server);
    assert(connectionCount == 1);

    auto clientConnection = egSteamNetworking_GetConnection(server, 0);

    auto wasSentSuccess = egSteamNetworking_SendMessage(clientConnection, 10, inputBuffer);
    assert(wasSentSuccess);

    auto wasRead = false;
    for (auto i = 0; i < 1000; i++)
    {
        egSteamNetworking_RunCallbacks();

        EgSteamNetworking_Connection outClientConnection = {};
        int outSize = 0;
        auto bytesRead = egSteamNetworking_ReceiveMessageFromConnection(client, outputBuffer);

        if (bytesRead > 0)
        {
            wasRead = true;
            for (auto j = 0; j < 10; j++)
            {
                assert(inputBuffer[j] == outputBuffer[j]);
            }
            break;
        }

        Sleep(1);
    }

    assert(wasRead);

    if (clientInitiatesDisconnect)
    {
        assert(egSteamNetworking_CloseConnection(client));
    }
    else
    {
        assert(egSteamNetworking_CloseConnection(clientConnection));
    }

    for (auto i = 0; i < 1000; i++)
    {
        egSteamNetworking_RunCallbacks();
        Sleep(1);
    }

    connectionCount = egSteamNetworking_GetConnectionCount(server);
    assert(connectionCount == 0);

    if (!clientInitiatesDisconnect)
    {
        assert(egSteamNetworking_CloseConnection(client));
    }
    assert(egSteamNetworking_CloseListenSocket(server));
}

void test_listen_socket_p2p_creation(bool clientInitiatesDisconnect)
{
    auto server = egSteamNetworking_CreateListenSocketP2P(TEST_PORT);
    auto isInvalid = egSteamNetworking_IsInvalidListenSocket(server);
    assert(!isInvalid);

    for (auto i = 0; i < 1000; i++)
    {
        egSteam_RunCallbacks();
        egSteamNetworking_RunCallbacks();
        Sleep(1);
    }

    auto client = egSteamNetworking_ConnectP2P(egSteamUser_GetSteamID(), TEST_PORT);

    auto isInvalidConnection = egSteamNetworking_IsInvalidConnection(client);
    assert(!isInvalidConnection);

    for (auto i = 0; i < 1000; i++)
    {
        egSteamNetworking_RunCallbacks();
        Sleep(1);
    }

    unsigned char inputBuffer[10] = { 5,4,3,2,1,2,3,4,5,6 };
    unsigned char outputBuffer[10] = { 0,0,0,0,0,0,0,0,0,0 };

    auto connectionCount = egSteamNetworking_GetConnectionCount(server);
    assert(connectionCount == 1);

    auto clientConnection = egSteamNetworking_GetConnection(server, 0);

    auto wasSentSuccess = egSteamNetworking_SendMessage(clientConnection, 10, inputBuffer);
    assert(wasSentSuccess);

    auto wasRead = false;
    for (auto i = 0; i < 1000; i++)
    {
        egSteamNetworking_RunCallbacks();

        EgSteamNetworking_Connection outClientConnection = {};
        int outSize = 0;
        auto bytesRead = egSteamNetworking_ReceiveMessageFromConnection(client, outputBuffer);

        if (bytesRead > 0)
        {
            wasRead = true;
            for (auto j = 0; j < 10; j++)
            {
                assert(inputBuffer[j] == outputBuffer[j]);
            }
            break;
        }

        Sleep(1);
    }

    assert(wasRead);

    if (clientInitiatesDisconnect)
    {
        assert(egSteamNetworking_CloseConnection(client));
    }
    else
    {
        assert(egSteamNetworking_CloseConnection(clientConnection));
    }

    for (auto i = 0; i < 1000; i++)
    {
        egSteamNetworking_RunCallbacks();
        Sleep(1);
    }

    connectionCount = egSteamNetworking_GetConnectionCount(server);
    assert(connectionCount == 0);

    if (!clientInitiatesDisconnect)
    {
        assert(egSteamNetworking_CloseConnection(client));
    }
    assert(egSteamNetworking_CloseListenSocket(server));
}

int main()
{
    EgSteam_InitializeOptions options = {};
    options.flags = (EgSteam_InitializeFlags)(EgSteam_InitializeFlags::DebugOutputEnabled | EgSteam_InitializeFlags::InitializeRelayNetworkAccess);

    assert(egSteam_Initialize(options));

    auto steamID = egSteamUser_GetSteamID();
    assert(!egSteamUser_IsInvalidSteamID(steamID));

    printf("Steam ID: %lld\n\n", steamID);

    int avatarImageHandle = 0;
    assert(egSteamFriends_GetLargeFriendAvatar(steamID, &avatarImageHandle) == EgSteamFriends_AvatarLoadStatus::Loaded);

    int avatarImageWidth = 0;
    int avatarImageHeight = 0;
    assert(egSteam_GetImageSize(avatarImageHandle, &avatarImageWidth, &avatarImageHeight));

    auto avatarImageSize = 4 * avatarImageWidth * avatarImageHeight;
    unsigned char* avatarImageBuffer = (unsigned char*)malloc(avatarImageSize);
    assert(egSteam_GetImageRGBA(avatarImageHandle, avatarImageSize, avatarImageBuffer));

    auto friendCount = egSteamFriends_GetFriendCount();
    assert(friendCount > 0);

    unsigned long long ryanID = 0;
    unsigned long long tannerID = 0;
    unsigned long long ethanID = 0;
    for (int i = 0; i < friendCount; i++)
    {
        auto steamFriendID = egSteamFriends_GetFriendByIndex(i);
        auto steamFriendName = egSteamFriends_GetFriendPersonaName(steamFriendID);

        printf("Steam Friend ID: %lld\n", steamFriendID);
        printf("Steam Friend Name: %s\n", steamFriendName);

        if (strcmp(steamFriendName, "Fal") == 0)
        {
            ryanID = steamFriendID;
        }
        else if (strcmp(steamFriendName, "Beledron") == 0)
        {
            tannerID = steamFriendID;
        }
        else if (strcmp(steamFriendName, "ethan") == 0)
        {
            ethanID = steamFriendID;
        }
    }

    assert(ryanID);
    assert(tannerID);
    assert(ethanID);

    int ryanAvatarImageHandle = 0;
    egSteamFriends_GetLargeFriendAvatar(ryanID, &ryanAvatarImageHandle);
    for (auto i = 0; i < 1000; i++)
    {
        egSteam_RunCallbacks();
        egSteamNetworking_RunCallbacks();
        Sleep(1);
    }
    assert(egSteamFriends_GetLargeFriendAvatar(ryanID, &ryanAvatarImageHandle) == EgSteamFriends_AvatarLoadStatus::Loaded);

    int tannerAvatarImageHandle = 0;
    egSteamFriends_GetLargeFriendAvatar(ryanID, &tannerAvatarImageHandle);
    for (auto i = 0; i < 1000; i++)
    {
        egSteam_RunCallbacks();
        egSteamNetworking_RunCallbacks();
        Sleep(1);
    }
    assert(egSteamFriends_GetLargeFriendAvatar(ryanID, &tannerAvatarImageHandle) == EgSteamFriends_AvatarLoadStatus::Loaded);

    int ethanAvatarImageHandle = 0;
    egSteamFriends_GetLargeFriendAvatar(ryanID, &ethanAvatarImageHandle);
    for (auto i = 0; i < 1000; i++)
    {
        egSteam_RunCallbacks();
        egSteamNetworking_RunCallbacks();
        Sleep(1);
    }
    assert(egSteamFriends_GetLargeFriendAvatar(ryanID, &ethanAvatarImageHandle) == EgSteamFriends_AvatarLoadStatus::Loaded);

    test_listen_socket_ip_creation(/*clientInitiateDisconnect*/false);
    test_listen_socket_ip_creation(/*clientInitiateDisconnect*/true);
    test_listen_socket_p2p_creation(/*clientInitiateDisconnect*/false);
    test_listen_socket_p2p_creation(/*clientInitiateDisconnect*/true);

    free(avatarImageBuffer);

    egSteam_Shutdown();
}

#include <stdio.h>
#include<windows.h>

#include "../egSteam.h"

#undef NDEBUG // allow assertions in non-debug builds
#include <assert.h>

#define TEST_PORT 27015

void test_listen_socket_ip_creation(bool clientInitiatesDisconnect)
{
    EgSteamNetworking_CreateListenSocketOptions options = {};
    options.port = TEST_PORT;

    auto server = egSteamNetworking_CreateListenSocketIP(options);
    auto isInvalid = egSteamNetworking_IsListenSocketInvalid(server);
    assert(!isInvalid);

    for (auto i = 0; i < 1000; i++)
    {
        egSteam_RunCallbacks();
        egSteamNetworking_RunCallbacks();
        Sleep(1);
    }

    EgSteamNetworking_ConnectOptions connectOptions = {};
    connectOptions.address = "127.0.0.1";
    connectOptions.port = TEST_PORT;
    auto client = egSteamNetworking_ConnectIP(connectOptions);

    auto isInvalidConnection = egSteamNetworking_IsConnectionInvalid(client);
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

int main()
{
    EgSteam_InitializeOptions options = {};
    options.flags = EgSteam_InitializeFlags::DebugOutputEnabled;

    auto isSteamRunning = egSteam_Initialize(options);
    printf("Steam Running: %i\n\n", isSteamRunning);

    test_listen_socket_ip_creation(/*clientInitiateDisconnect*/false);
    test_listen_socket_ip_creation(/*clientInitiateDisconnect*/true);

    egSteam_Shutdown();
}

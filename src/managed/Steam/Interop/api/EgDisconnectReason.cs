namespace Evergreen.Steam.Interop;

public enum EgDisconnectReason
{
    ClientDisconnect = 1000 + 1,
    ServerClosed = 1000 + 2,
    ServerReject = 1000 + 3,
    ServerFull = 1000 + 4,
    ClientKicked = 1000 + 5,
}

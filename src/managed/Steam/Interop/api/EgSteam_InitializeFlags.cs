namespace Evergreen.Steam.Interop;

public enum EgSteam_InitializeFlags
{
    None = 0,
    InitializeRelayNetworkAccess = 1 << 0,
    DebugOutputEnabled = 1 << 1,
}

namespace Evergreen.Steam.Interop;

public unsafe partial struct EgSteamNetworking_ConnectOptions
{
    [NativeTypeName("const char *")]
    public sbyte* address;

    [NativeTypeName("unsigned short")]
    public ushort port;
}

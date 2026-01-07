namespace Evergreen.Physics.Backend.Jolt.Interop;

[NativeTypeName("unsigned char")]
public enum EgJolt_BodyFlags : byte
{
    None = 0,
    IsActive = 1 << 0,
    IsSensor = 1 << 1,
}

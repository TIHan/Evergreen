namespace Evergreen.Physics.Backend.Jolt.Interop;

[NativeTypeName("unsigned char")]
public enum EgJolt_BodyFlags : byte
{
    EgJolt_BodyFlags_None,
    EgJolt_BodyFlags_IsActive,
    EgJolt_BodyFlags_IsSensor,
}

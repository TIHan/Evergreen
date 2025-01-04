namespace Evergreen.Physics.Backend.Jolt.Interop;

public partial struct EgJoltBodyState
{
    [NativeTypeName("EgJoltVector3")]
    public System.Numerics.Vector3 position;

    [NativeTypeName("EgJoltQuaternion")]
    public System.Numerics.Quaternion rotation;

    [NativeTypeName("EgJoltVector3")]
    public System.Numerics.Vector3 linearVelocity;

    [NativeTypeName("EgJoltVector3")]
    public System.Numerics.Vector3 angularVelocity;

    public float gravityFactor;

    public EgJolt_BodyFlags flags;
}

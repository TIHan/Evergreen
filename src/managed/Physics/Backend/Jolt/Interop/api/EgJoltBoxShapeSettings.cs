namespace Evergreen.Physics.Backend.Jolt.Interop;

public partial struct EgJoltBoxShapeSettings
{
    [NativeTypeName("EgJoltVector3")]
    public System.Numerics.Vector3 scale;

    public float density;
}

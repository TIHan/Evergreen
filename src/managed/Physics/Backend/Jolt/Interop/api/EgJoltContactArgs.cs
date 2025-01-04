namespace Evergreen.Physics.Backend.Jolt.Interop;

public partial struct EgJoltContactArgs
{
    [NativeTypeName("unsigned int")]
    public uint bodyId1;

    [NativeTypeName("unsigned long long")]
    public ulong userData1;

    [NativeTypeName("EgJoltVector3")]
    public System.Numerics.Vector3 point1;

    [NativeTypeName("unsigned int")]
    public uint bodyId2;

    [NativeTypeName("unsigned long long")]
    public ulong userData2;

    [NativeTypeName("EgJoltVector3")]
    public System.Numerics.Vector3 point2;
}

namespace Evergreen.Physics.Backend.Jolt.Interop;

public unsafe partial struct EgJoltMesh
{
    [NativeTypeName("unsigned int")]
    public uint vertexCount;

    [NativeTypeName("EgJoltVector3 *")]
    public System.Numerics.Vector3* vertices;

    [NativeTypeName("unsigned int")]
    public uint indexCount;

    [NativeTypeName("unsigned int *")]
    public uint* indices;

    [NativeTypeName("unsigned long long")]
    public ulong userData;
}

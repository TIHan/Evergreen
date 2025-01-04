namespace Evergreen.Physics.Backend.Jolt.Interop;

public unsafe partial struct EgJoltCompoundMesh
{
    [NativeTypeName("unsigned int")]
    public uint meshCount;

    public EgJoltMesh* meshes;
}

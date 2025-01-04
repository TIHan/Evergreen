namespace Evergreen.Graphics.Asset.Backend.Interop;

public unsafe partial struct EgAssetMesh
{
    [NativeTypeName("unsigned int *")]
    public uint* indices;

    [NativeTypeName("unsigned int")]
    public uint indexCount;

    [NativeTypeName("EgAssetVector3 *")]
    public System.Numerics.Vector3* vertices;

    [NativeTypeName("unsigned int")]
    public uint vertexCount;

    [NativeTypeName("EgAssetVector3 *")]
    public System.Numerics.Vector3* normals;

    [NativeTypeName("EgAssetVector2 *")]
    public System.Numerics.Vector2* texCoords;

    public EgAssetAABB aabb;

    [NativeTypeName("unsigned int")]
    public uint materialIndex;
}

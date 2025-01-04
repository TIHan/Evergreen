namespace Evergreen.Graphics.Asset.Backend.Interop;

public partial struct EgAssetAABB
{
    [NativeTypeName("EgAssetVector3")]
    public System.Numerics.Vector3 min;

    [NativeTypeName("EgAssetVector3")]
    public System.Numerics.Vector3 max;
}

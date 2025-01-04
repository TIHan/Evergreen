namespace Evergreen.Graphics.Asset.Backend.Interop;

public unsafe partial struct EgAssetImage
{
    [NativeTypeName("unsigned char *")]
    public byte* rawData;

    public int width;

    public int height;

    public int channels;

    public int desiredChannels;
}

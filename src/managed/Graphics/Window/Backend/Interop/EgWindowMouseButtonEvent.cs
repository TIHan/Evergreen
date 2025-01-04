namespace Evergreen.Graphics.Window.Backend.Interop;

public partial struct EgWindowMouseButtonEvent
{
    [NativeTypeName("unsigned char")]
    public byte buttonIndex;

    [NativeTypeName("EgWindowVector2")]
    public System.Numerics.Vector2 position;

    public EgWindowMouseButtonEventFlags flags;
}

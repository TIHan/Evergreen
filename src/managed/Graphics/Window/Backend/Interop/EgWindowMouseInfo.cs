namespace Evergreen.Graphics.Window.Backend.Interop;

public partial struct EgWindowMouseInfo
{
    [NativeTypeName("EgWindowVector2")]
    public System.Numerics.Vector2 position;

    [NativeTypeName("EgWindowVector2")]
    public System.Numerics.Vector2 relativePosition;
}

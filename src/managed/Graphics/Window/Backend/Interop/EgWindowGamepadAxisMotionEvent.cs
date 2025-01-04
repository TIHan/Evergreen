namespace Evergreen.Graphics.Window.Backend.Interop;

public partial struct EgWindowGamepadAxisMotionEvent
{
    [NativeTypeName("unsigned int")]
    public uint gamepadId;

    [NativeTypeName("unsigned char")]
    public byte axisId;

    public short value;
}

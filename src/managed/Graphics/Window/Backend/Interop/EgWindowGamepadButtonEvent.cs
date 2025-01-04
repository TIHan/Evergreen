namespace Evergreen.Graphics.Window.Backend.Interop;

public partial struct EgWindowGamepadButtonEvent
{
    [NativeTypeName("unsigned int")]
    public uint gamepadId;

    [NativeTypeName("unsigned char")]
    public byte buttonIndex;

    public EgWindowGamepadButtonEventFlags flags;
}

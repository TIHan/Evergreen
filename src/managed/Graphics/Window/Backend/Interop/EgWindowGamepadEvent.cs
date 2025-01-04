namespace Evergreen.Graphics.Window.Backend.Interop;

public partial struct EgWindowGamepadEvent
{
    public EgWindowGamepadEventKind kind;

    [NativeTypeName("unsigned int")]
    public uint gamepadId;
}

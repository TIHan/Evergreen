namespace Evergreen.Graphics.UI.Backend.ImGui.Interop;

public enum EgImGuiChildFlags
{
    None = 0,
    Border = 1 << 0,
    AlwaysUseWindowPadding = 1 << 1,
    ResizeX = 1 << 2,
    ResizeY = 1 << 3,
    AutoResizeX = 1 << 4,
    AutoResizeY = 1 << 5,
    AlwaysAutoResize = 1 << 6,
    FrameStyle = 1 << 7,
}

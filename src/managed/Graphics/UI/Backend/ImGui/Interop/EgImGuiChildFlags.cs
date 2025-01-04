namespace Evergreen.Graphics.UI.Backend.ImGui.Interop;

public enum EgImGuiChildFlags
{
    EgImGuiChildFlags_None = 0,
    EgImGuiChildFlags_Border = 1 << 0,
    EgImGuiChildFlags_AlwaysUseWindowPadding = 1 << 1,
    EgImGuiChildFlags_ResizeX = 1 << 2,
    EgImGuiChildFlags_ResizeY = 1 << 3,
    EgImGuiChildFlags_AutoResizeX = 1 << 4,
    EgImGuiChildFlags_AutoResizeY = 1 << 5,
    EgImGuiChildFlags_AlwaysAutoResize = 1 << 6,
    EgImGuiChildFlags_FrameStyle = 1 << 7,
}

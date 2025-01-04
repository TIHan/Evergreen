namespace Evergreen.Graphics.UI.Backend.ImGui.Interop;

public enum EgImGuiInputTextFlags
{
    EgImGuiInputTextFlags_None = 0,
    EgImGuiInputTextFlags_CharsDecimal = 1 << 0,
    EgImGuiInputTextFlags_CharsHexadecimal = 1 << 1,
    EgImGuiInputTextFlags_CharsUppercase = 1 << 2,
    EgImGuiInputTextFlags_CharsNoBlank = 1 << 3,
    EgImGuiInputTextFlags_AutoSelectAll = 1 << 4,
    EgImGuiInputTextFlags_EnterReturnsTrue = 1 << 5,
    EgImGuiInputTextFlags_CallbackCompletion = 1 << 6,
    EgImGuiInputTextFlags_CallbackHistory = 1 << 7,
    EgImGuiInputTextFlags_CallbackAlways = 1 << 8,
    EgImGuiInputTextFlags_CallbackCharFilter = 1 << 9,
    EgImGuiInputTextFlags_AllowTabInput = 1 << 10,
    EgImGuiInputTextFlags_CtrlEnterForNewLine = 1 << 11,
    EgImGuiInputTextFlags_NoHorizontalScroll = 1 << 12,
    EgImGuiInputTextFlags_AlwaysOverwrite = 1 << 13,
    EgImGuiInputTextFlags_ReadOnly = 1 << 14,
    EgImGuiInputTextFlags_Password = 1 << 15,
    EgImGuiInputTextFlags_NoUndoRedo = 1 << 16,
    EgImGuiInputTextFlags_CharsScientific = 1 << 17,
    EgImGuiInputTextFlags_CallbackResize = 1 << 18,
    EgImGuiInputTextFlags_CallbackEdit = 1 << 19,
    EgImGuiInputTextFlags_EscapeClearsAll = 1 << 20,
}

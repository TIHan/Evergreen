namespace Evergreen.Graphics.UI.Backend.ImGui.Interop;

public unsafe partial struct EgImGui_InputTextCallbackData
{
    public void* Ctx;

    public EgImGuiInputTextFlags EventFlag;

    public EgImGuiInputTextFlags Flags;

    public void* UserData;

    [NativeTypeName("unsigned int")]
    public uint EventChar;

    public int EventKey;

    [NativeTypeName("char *")]
    public sbyte* Buf;

    public int BufTextLen;

    public int BufSize;

    [NativeTypeName("bool")]
    public byte BufDirty;

    public int CursorPos;

    public int SelectionStart;

    public int SelectionEnd;
}

using System.Runtime.InteropServices;

namespace Evergreen.Graphics.Window.Backend.Interop;

public static unsafe partial class Methods
{
    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern EgWindow egWindowCreateVulkan([NativeTypeName("const char *")] sbyte* name);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egWindowDestroy(EgWindow window);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void* egWindowGetWin32Handle(EgWindow window);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern EgWindowDisplayMode egWindowGetDesktopDisplayMode(EgWindow window);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern EgWindowDisplayMode egWindowGetCurrentDisplayMode(EgWindow window);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egWindowSetCurrentDisplayMode(EgWindow window, EgWindowDisplayMode displayMode);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egWindowGetDisplayModes(EgWindow window, [NativeTypeName("void (*)(EgWindowDisplayMode)")] delegate* unmanaged[Cdecl]<EgWindowDisplayMode, void> callbackDisplayMode);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egWindowShow(EgWindow window);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egWindowHide(EgWindow window);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egWindowMinimize(EgWindow window);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    [return: NativeTypeName("EgWindowBool")]
    public static extern System.Boolean egWindowIsFullscreen(EgWindow window);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egWindowSetFullscreen(EgWindow window, [NativeTypeName("EgWindowBool")] System.Boolean value);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    [return: NativeTypeName("EgWindowBool")]
    public static extern System.Boolean egWindowIsCursorVisible(EgWindow window);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egWindowSetCursorVisible(EgWindow window, [NativeTypeName("EgWindowBool")] System.Boolean value);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    [return: NativeTypeName("EgWindowBool")]
    public static extern System.Boolean egWindowIsHidden(EgWindow window);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    [return: NativeTypeName("EgWindowBool")]
    public static extern System.Boolean egWindowIsMinimized(EgWindow window);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    [return: NativeTypeName("EgWindowVector2")]
    public static extern System.Numerics.Vector2 egWindowGetSize(EgWindow window);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egWindowSetSize(EgWindow window, [NativeTypeName("EgWindowVector2")] System.Numerics.Vector2 value);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    [return: NativeTypeName("EgWindowVector2")]
    public static extern System.Numerics.Vector2 egWindowGetPosition(EgWindow window);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egWindowSetPosition(EgWindow window, [NativeTypeName("EgWindowVector2")] System.Numerics.Vector2 value);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egWindowPumpEvents(EgWindow window, [NativeTypeName("EgWindowBool")] System.Boolean hasImGuiInput, [NativeTypeName("void (*)(EgWindowKeyEvent)")] delegate* unmanaged[Cdecl]<EgWindowKeyEvent, void> callbackKeyEvent, [NativeTypeName("void (*)(EgWindowMouseInfo)")] delegate* unmanaged[Cdecl]<EgWindowMouseInfo, void> callbackMouseInfo, [NativeTypeName("void (*)(EgWindowMouseButtonEvent)")] delegate* unmanaged[Cdecl]<EgWindowMouseButtonEvent, void> callbackMouseButtonEvent, [NativeTypeName("void (*)(EgWindowMouseWheelEvent)")] delegate* unmanaged[Cdecl]<EgWindowMouseWheelEvent, void> callbackMouseWheelEvent, [NativeTypeName("void (*)(EgWindowGamepadAxisMotionEvent)")] delegate* unmanaged[Cdecl]<EgWindowGamepadAxisMotionEvent, void> callbackGamepadAxisMotionEvent, [NativeTypeName("void (*)(EgWindowGamepadButtonEvent)")] delegate* unmanaged[Cdecl]<EgWindowGamepadButtonEvent, void> callbackGamepadButtonEvent, [NativeTypeName("void (*)(EgWindowGamepadEvent)")] delegate* unmanaged[Cdecl]<EgWindowGamepadEvent, void> callbackGamepadEvent, [NativeTypeName("void (*)()")] delegate* unmanaged[Cdecl]<void> callbackQuit);
}

using System.Runtime.InteropServices;

namespace Evergreen.Graphics.Shader.Backend.Interop;

public static unsafe partial class Methods
{
    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern int egShaderInitialize();

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egShaderFinalize();

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    [return: NativeTypeName("EgShaderBool")]
    public static extern System.Boolean egShaderCompile(EgShaderKind kind, [NativeTypeName("const char *")] sbyte* text, [NativeTypeName("unsigned int")] uint textLength, [NativeTypeName("void (*)(char *, unsigned int)")] delegate* unmanaged[Cdecl]<sbyte*, uint, void> callback, [NativeTypeName("void (*)(const char *)")] delegate* unmanaged[Cdecl]<sbyte*, void> callbackError);
}

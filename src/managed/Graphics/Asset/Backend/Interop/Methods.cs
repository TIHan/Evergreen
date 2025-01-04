using System.Runtime.InteropServices;

namespace Evergreen.Graphics.Asset.Backend.Interop;

public static unsafe partial class Methods
{
    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    [return: NativeTypeName("EgAssetBool")]
    public static extern System.Boolean egAssetReadImage([NativeTypeName("unsigned char *")] byte* buffer, int bufferLength, EgAssetImage* outImage);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egAssetFreeImage(EgAssetImage image);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    [return: NativeTypeName("EgAssetBool")]
    public static extern System.Boolean egAssetReadMeshes([NativeTypeName("const char *")] sbyte* pFilePath, [NativeTypeName("void (*)(EgAssetMesh)")] delegate* unmanaged[Cdecl]<EgAssetMesh, void> callbackMesh);
}

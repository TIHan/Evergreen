using System.Runtime.InteropServices;

namespace Evergreen.Graphics.UI.Backend.ImGui.Interop;

public static unsafe partial class Methods
{
    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern EgImGuiContext egImGuiCreateContextVulkan([NativeTypeName("EgWindow")] Evergreen.Graphics.Window.Backend.Interop.EgWindow window, [NativeTypeName("VkInstance")] TerraFX.Interop.Vulkan.VkInstance instance, [NativeTypeName("VkPhysicalDevice")] TerraFX.Interop.Vulkan.VkPhysicalDevice physicalDevice, [NativeTypeName("VkDevice")] TerraFX.Interop.Vulkan.VkDevice device, [NativeTypeName("unsigned int")] uint graphicsQueueFamilyIndex, [NativeTypeName("VkQueue")] TerraFX.Interop.Vulkan.VkQueue graphicsQueue, [NativeTypeName("unsigned int")] uint minImageCount, [NativeTypeName("unsigned int")] uint imageCount, [NativeTypeName("VkRenderPass")] TerraFX.Interop.Vulkan.VkRenderPass renderPass, [NativeTypeName("void (*)(VkResult)")] delegate* unmanaged[Cdecl]<TerraFX.Interop.Vulkan.VkResult, void> callbackCheckVulkanInitialization);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egImGuiDestroyContextVulkan(EgImGuiContext context);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egImGuiSetScaleFactor(EgImGuiContext context, float scaleFactor);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern float egImGuiGetScaleFactor(EgImGuiContext context);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egImGuiSetMouseCursorChange(EgImGuiContext context, [NativeTypeName("EgImGuiBool")] System.Boolean value);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    [return: NativeTypeName("unsigned int *")]
    public static extern uint* egImGui_GetGlyphRangesAll();

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    [return: NativeTypeName("unsigned int *")]
    public static extern uint* egImGui_GetGlyphRangesDefault();

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    [return: NativeTypeName("unsigned int *")]
    public static extern uint* egImGui_GetGlyphRangesGreek();

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    [return: NativeTypeName("unsigned int *")]
    public static extern uint* egImGui_GetGlyphRangesIcon();

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    [return: NativeTypeName("unsigned int *")]
    public static extern uint* egImGui_GetGlyphRangesEmoji();

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern EgImFont egImGuiAddFontDefault(EgImGuiContext context);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern EgImFont egImGuiAddFont(EgImGuiContext context, [NativeTypeName("unsigned char *")] byte* fontData, int fontDataSize, float pixelSize, [NativeTypeName("unsigned int *")] uint* ranges);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern EgImFont egImGuiMergeFonts(EgImGuiContext context, [NativeTypeName("unsigned char **")] byte** multipleFontData, int* fontDataSizes, float* pixelSizes, [NativeTypeName("unsigned int **")] uint** multipleRanges, int length);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egImGuiPushFont(EgImGuiContext context, EgImFont font);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egImGuiPopFont(EgImGuiContext context);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egImGuiUploadFontsVulkan(EgImGuiContext context);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egImGuiSetDarkMode(EgImGuiContext context);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egImGuiSetClassicMode(EgImGuiContext context);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egImGuiNewFrameVulkan(EgImGuiContext context);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egImGuiEndFrame(EgImGuiContext context);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egImGuiDrawVulkan(EgImGuiContext context, [NativeTypeName("VkCommandBuffer")] TerraFX.Interop.Vulkan.VkCommandBuffer commandBuffer, [NativeTypeName("VkPipeline")] TerraFX.Interop.Vulkan.VkPipeline pipeline);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egImGuiSetCurrentContext(EgImGuiContext context);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egImGuiShowDemoWindow(EgImGuiContext context);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    [return: NativeTypeName("EgImGuiBool")]
    public static extern System.Boolean egImGuiIsMouseDragging(EgImGuiContext context);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    [return: NativeTypeName("EgImGuiVector2")]
    public static extern System.Numerics.Vector2 egImGuiGetMainViewportSize(EgImGuiContext context);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    [return: NativeTypeName("EgImGuiBool")]
    public static extern System.Boolean egImGuiBegin(EgImGuiContext context, [NativeTypeName("bool &")] bool* isOpen, [NativeTypeName("bool")] byte hideCloseButton, [NativeTypeName("const char *")] sbyte* title, EgImGuiWindowFlags flags);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egImGuiEnd(EgImGuiContext context);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    [return: NativeTypeName("EgImGuiBool")]
    public static extern System.Boolean egImGui_BeginPopupModal(EgImGuiContext context, [NativeTypeName("bool &")] bool* isOpen, [NativeTypeName("bool")] byte hideCloseButton, [NativeTypeName("const char *")] sbyte* title, EgImGuiWindowFlags flags);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egImGui_EndPopup(EgImGuiContext context);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egImGui_OpenPopup(EgImGuiContext context, [NativeTypeName("const char *")] sbyte* id);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egImGuiBeginDisabled(EgImGuiContext context, [NativeTypeName("bool")] byte isDisabled);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egImGuiEndDisabled(EgImGuiContext context);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    [return: NativeTypeName("EgImGuiBool")]
    public static extern System.Boolean egImGuiBeginChild(EgImGuiContext context, [NativeTypeName("unsigned int")] uint id, [NativeTypeName("EgImGuiVector2")] System.Numerics.Vector2 size, EgImGuiChildFlags childFlags);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egImGuiEndChild(EgImGuiContext context);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egImGuiPushId(EgImGuiContext context, int id);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egImGuiPopId(EgImGuiContext context);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egImGuiPushItemWidth(EgImGuiContext context, float width);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egImGuiPopItemWidth(EgImGuiContext context);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egImGuiSetCursorPositionX(EgImGuiContext context, float x);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egImGuiSetCursorPositionY(EgImGuiContext context, float y);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern float egImGuiGetCursorPositionX(EgImGuiContext context);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern float egImGuiGetCursorPositionY(EgImGuiContext context);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    [return: NativeTypeName("EgImGuiVector2")]
    public static extern System.Numerics.Vector2 egImGuiGetItemRectSize(EgImGuiContext context);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern float egImGuiCalculateItemWidth(EgImGuiContext context);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egImGuiSetNextWindowBackgroundAlpha(EgImGuiContext context, float alpha);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egImGuiSetNextWindowPosition(EgImGuiContext context, [NativeTypeName("EgImGuiVector2")] System.Numerics.Vector2 position);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egImGuiSetNextWindowPositionWithPivot(EgImGuiContext context, [NativeTypeName("EgImGuiVector2")] System.Numerics.Vector2 position, [NativeTypeName("EgImGuiVector2")] System.Numerics.Vector2 pivot);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egImGuiSetNextWindowSize(EgImGuiContext context, [NativeTypeName("EgImGuiVector2")] System.Numerics.Vector2 size);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    [return: NativeTypeName("EgImGuiVector2")]
    public static extern System.Numerics.Vector2 egImGuiGetWindowPosition(EgImGuiContext context);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    [return: NativeTypeName("EgImGuiVector2")]
    public static extern System.Numerics.Vector2 egImGuiGetWindowSize(EgImGuiContext context);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egImGuiSetWindowPosition(EgImGuiContext context, [NativeTypeName("EgImGuiVector2")] System.Numerics.Vector2 position);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egImGuiSetWindowSize(EgImGuiContext context, [NativeTypeName("EgImGuiVector2")] System.Numerics.Vector2 size);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    [return: NativeTypeName("EgImGuiVector2")]
    public static extern System.Numerics.Vector2 egImGuiCalculateWindowSize(EgImGuiContext context);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egImGuiText(EgImGuiContext context, [NativeTypeName("const char *")] sbyte* text);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egImGuiLabelText(EgImGuiContext context, [NativeTypeName("const char *")] sbyte* label, [NativeTypeName("const char *")] sbyte* text);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    [return: NativeTypeName("EgImGuiBool")]
    public static extern System.Boolean egImGuiInputText(EgImGuiContext context, [NativeTypeName("const char *")] sbyte* label, [NativeTypeName("char *")] sbyte* buffer, [NativeTypeName("size_t")] nuint bufferSize, EgImGuiInputTextFlags flags, [NativeTypeName("int (*)(EgImGui_InputTextCallbackData)")] delegate* unmanaged[Cdecl]<EgImGui_InputTextCallbackData, int> callback);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    [return: NativeTypeName("EgImGuiBool")]
    public static extern System.Boolean egImGuiInputInt(EgImGuiContext context, [NativeTypeName("const char *")] sbyte* label, [NativeTypeName("int &")] int* value);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    [return: NativeTypeName("EgImGuiBool")]
    public static extern System.Boolean egImGuiCheckbox(EgImGuiContext context, [NativeTypeName("const char *")] sbyte* label, [NativeTypeName("bool &")] bool* value);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    [return: NativeTypeName("EgImGuiBool")]
    public static extern System.Boolean egImGuiButton(EgImGuiContext context, [NativeTypeName("const char *")] sbyte* label, [NativeTypeName("EgImGuiVector2")] System.Numerics.Vector2 size);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    [return: NativeTypeName("EgImGuiBool")]
    public static extern System.Boolean egImGuiCombo(EgImGuiContext context, [NativeTypeName("const char *")] sbyte* label, [NativeTypeName("int &")] int* selectedItemIndex, [NativeTypeName("char **")] sbyte** items, int itemCount, int popupMaxHeight);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egImGuiPlotLines(EgImGuiContext context, [NativeTypeName("const char *")] sbyte* label, float* values, int valuesLength, int offset, [NativeTypeName("const char *")] sbyte* overlayText, float scaleMin, float scaleMax, [NativeTypeName("EgImGuiVector2")] System.Numerics.Vector2 size);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    [return: NativeTypeName("VkDescriptorSet")]
    public static extern TerraFX.Interop.Vulkan.VkDescriptorSet egImGuiAddTextureVulkan(EgImGuiContext context, [NativeTypeName("VkSampler")] TerraFX.Interop.Vulkan.VkSampler sampler, [NativeTypeName("VkImageView")] TerraFX.Interop.Vulkan.VkImageView imageView, [NativeTypeName("VkImageLayout")] TerraFX.Interop.Vulkan.VkImageLayout imageLayout);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egImGuiRemoveTextureVulkan(EgImGuiContext context, [NativeTypeName("VkDescriptorSet")] TerraFX.Interop.Vulkan.VkDescriptorSet descriptorSet);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egImGuiImageVulkan(EgImGuiContext context, [NativeTypeName("VkDescriptorSet")] TerraFX.Interop.Vulkan.VkDescriptorSet texture, [NativeTypeName("EgImGuiVector2")] System.Numerics.Vector2 size, [NativeTypeName("EgImGuiVector2")] System.Numerics.Vector2 uv0, [NativeTypeName("EgImGuiVector2")] System.Numerics.Vector2 uv1, [NativeTypeName("EgImGuiVector4")] System.Numerics.Vector4 borderColor);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    [return: NativeTypeName("EgImGuiBool")]
    public static extern System.Boolean egImGuiBeginTabBar(EgImGuiContext context);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    [return: NativeTypeName("unsigned int")]
    public static extern uint egImGuiGetSelectedTabId(EgImGuiContext context);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egImGuiFocusTabById(EgImGuiContext context, [NativeTypeName("unsigned int")] uint tabId);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egImGuiEndTabBar(EgImGuiContext context);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    [return: NativeTypeName("EgImGuiBool")]
    public static extern System.Boolean egImGuiBeginTabItem(EgImGuiContext context, [NativeTypeName("const char *")] sbyte* label, [NativeTypeName("bool &")] bool* isOpen);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egImGuiEndTabItem(EgImGuiContext context);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egImGuiBeginGroup(EgImGuiContext context);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egImGuiEndGroup(EgImGuiContext context);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    [return: NativeTypeName("EgImGuiBool")]
    public static extern System.Boolean egImGuiBeginListBox(EgImGuiContext context, [NativeTypeName("const char *")] sbyte* label, [NativeTypeName("EgImGuiVector2")] System.Numerics.Vector2 size);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egImGuiEndListBox(EgImGuiContext context);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    [return: NativeTypeName("EgImGuiBool")]
    public static extern System.Boolean egImGuiBeginItemTooltip(EgImGuiContext context);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egImGuiEndTooltip(EgImGuiContext context);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    [return: NativeTypeName("EgImGuiBool")]
    public static extern System.Boolean egImGuiBeginTable(EgImGuiContext context, int columnCount);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egImGuiEndTable(EgImGuiContext context);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern int egImGuiTableGetCurrentRow(EgImGuiContext context);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egImGuiTableNextRow(EgImGuiContext context);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    [return: NativeTypeName("EgImGuiBool")]
    public static extern System.Boolean egImGuiTableSetColumnIndex(EgImGuiContext context, int columnIndex);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egImGuiBeginTableCell(EgImGuiContext context, int column);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egImGuiEndTableCell(EgImGuiContext context);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egImGuiBeginClipper(EgImGuiContext context, int amount);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egImGuiEndClipper(EgImGuiContext context);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    [return: NativeTypeName("EgImGuiBool")]
    public static extern System.Boolean egImGuiClipperStep(EgImGuiContext context);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern int egImGuiClipperDisplayStart(EgImGuiContext context);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern int egImGuiClipperDisplayEnd(EgImGuiContext context);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egImGuiTableSetupColumnNoHeaderLabel(EgImGuiContext context);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    [return: NativeTypeName("EgImGuiBool")]
    public static extern System.Boolean egImGuiTableNextColumn(EgImGuiContext context);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egImGuiTextUnformatted(EgImGuiContext context, [NativeTypeName("const char *")] sbyte* text, [NativeTypeName("const char *")] sbyte* textEnd);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egImGui_ScrollbarX(EgImGuiContext context);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egImGui_ScrollbarY(EgImGuiContext context);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egImGuiSameLine(EgImGuiContext context);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egImGuiSameLineWithOffset(EgImGuiContext context, float offsetFromStartX);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egImGuiSameLineWithOffsetAndSpacing(EgImGuiContext context, float offsetFromStartX, float spacing);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    [return: NativeTypeName("EgImGuiVector2")]
    public static extern System.Numerics.Vector2 egImGuiGetContentRegionAvail(EgImGuiContext context);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    [return: NativeTypeName("EgImGuiBool")]
    public static extern System.Boolean egImGuiIsItemHovered(EgImGuiContext context);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    [return: NativeTypeName("EgImGuiBool")]
    public static extern System.Boolean egImGuiIsWindowHovered(EgImGuiContext context);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    [return: NativeTypeName("EgImGuiBool")]
    public static extern System.Boolean egImGuiIsItemClicked(EgImGuiContext context);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    [return: NativeTypeName("EgImGuiBool")]
    public static extern System.Boolean egImGuiSliderFloat(EgImGuiContext context, [NativeTypeName("const char *")] sbyte* label, float min, float max, float* value);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern float egImGui_GetScrollMaxX(EgImGuiContext context);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern float egImGui_GetScrollMaxY(EgImGuiContext context);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern float egImGui_GetScrollX(EgImGuiContext context);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern float egImGui_GetScrollY(EgImGuiContext context);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egImGui_SetScrollX(EgImGuiContext context, float value);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egImGui_SetScrollY(EgImGuiContext context, float value);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egImGui_SetScrollHereX(EgImGuiContext context, float centerRatio);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egImGui_SetScrollHereY(EgImGuiContext context, float centerRatio);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egImGui_SetNextWindowScroll(EgImGuiContext context, [NativeTypeName("EgImGuiVector2")] System.Numerics.Vector2 value);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egImGui_SetFocus(EgImGuiContext context, [NativeTypeName("unsigned int")] uint id);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    [return: NativeTypeName("EgImGuiBool")]
    public static extern System.Boolean egImGui_IsWindowFocused(EgImGuiContext context);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    [return: NativeTypeName("EgImGuiBool")]
    public static extern System.Boolean egImGui_IsItemFocused(EgImGuiContext context);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    [return: NativeTypeName("unsigned int")]
    public static extern uint egImGui_GetItemId(EgImGuiContext context);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egImGui_SetWindowFocus(EgImGuiContext context);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egImGui_SetKeyboardFocusHere(EgImGuiContext context);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egImGui_BringCurrentWindowToDisplayFront(EgImGuiContext context);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egImGui_Dummy(EgImGuiContext context, [NativeTypeName("EgImGuiVector2")] System.Numerics.Vector2 size);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    [return: NativeTypeName("EgImGuiVector2")]
    public static extern System.Numerics.Vector2 egImGui_GetCellPadding(EgImGuiContext context);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    [return: NativeTypeName("EgImGuiVector2")]
    public static extern System.Numerics.Vector2 egImGui_GetFramePadding(EgImGuiContext context);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    [return: NativeTypeName("EgImGuiVector2")]
    public static extern System.Numerics.Vector2 egImGui_GetWindowPadding(EgImGuiContext context);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    [return: NativeTypeName("EgImGuiVector2")]
    public static extern System.Numerics.Vector2 egImGui_GetItemSpacing(EgImGuiContext context);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    [return: NativeTypeName("EgImGuiVector2")]
    public static extern System.Numerics.Vector2 egImGui_GetItemInnerSpacing(EgImGuiContext context);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egImGui_SetCellPadding(EgImGuiContext context, [NativeTypeName("EgImGuiVector2")] System.Numerics.Vector2 cellPadding);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egImGui_PushStyleColor_Text(EgImGuiContext context, [NativeTypeName("EgImGuiVector4")] System.Numerics.Vector4 color);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egImGui_PushStyleColor_Button(EgImGuiContext context, [NativeTypeName("EgImGuiVector4")] System.Numerics.Vector4 color);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egImGui_PushStyleColor_ButtonHovered(EgImGuiContext context, [NativeTypeName("EgImGuiVector4")] System.Numerics.Vector4 color);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egImGui_PushStyleColor_ButtonActive(EgImGuiContext context, [NativeTypeName("EgImGuiVector4")] System.Numerics.Vector4 color);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egImGui_PushStyleColor_WindowBackground(EgImGuiContext context, [NativeTypeName("EgImGuiVector4")] System.Numerics.Vector4 color);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egImGui_PushStyleColor_ChildBackground(EgImGuiContext context, [NativeTypeName("EgImGuiVector4")] System.Numerics.Vector4 color);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egImGui_PushStyleColor_PopupBackground(EgImGuiContext context, [NativeTypeName("EgImGuiVector4")] System.Numerics.Vector4 color);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egImGui_PushStyleColor_FrameBackground(EgImGuiContext context, [NativeTypeName("EgImGuiVector4")] System.Numerics.Vector4 color);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egImGui_PushStyleColor_FrameBackgroundHovered(EgImGuiContext context, [NativeTypeName("EgImGuiVector4")] System.Numerics.Vector4 color);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egImGui_PushStyleColor_FrameBackgroundActive(EgImGuiContext context, [NativeTypeName("EgImGuiVector4")] System.Numerics.Vector4 color);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egImGui_PushStyleColor_ModalWindowDimBackground(EgImGuiContext context, [NativeTypeName("EgImGuiVector4")] System.Numerics.Vector4 color);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egImGui_PopStyleColor(EgImGuiContext context);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    [return: NativeTypeName("EgImGuiVector2")]
    public static extern System.Numerics.Vector2 egImGui_GetStyleVar_WindowPadding(EgImGuiContext context);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egImGui_PushStyleVar_WindowPadding(EgImGuiContext context, [NativeTypeName("EgImGuiVector2")] System.Numerics.Vector2 padding);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egImGui_PopStyleVar(EgImGuiContext context);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    [return: NativeTypeName("EgImGuiVector2")]
    public static extern System.Numerics.Vector2 egImGui_GetStyleVar_WindowBorderSize(EgImGuiContext context);

    [DllImport("Evergreen.Graphics.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egImGui_PushStyleVar_WindowBorderSize(EgImGuiContext context, [NativeTypeName("EgImGuiVector2")] System.Numerics.Vector2 value);
}

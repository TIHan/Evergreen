#pragma once

#include <vulkan/vulkan.h>

#include "egWindow.h"

#define EG_EXPORT __declspec(dllexport)

typedef int EgImGuiBool;

typedef struct {
	void* internal;
} EgImGuiContext;

typedef struct {
    void* internal;
} EgImFont;

typedef struct {
    float x;
    float y;
} EgImGuiVector2;

typedef struct {
    float x;
    float y;
    float z;
    float w;
} EgImGuiVector4;

// This is a 1:1 with ImGuiWindowFlags.
enum EgImGuiWindowFlags
{
    EgImGuiWindowFlags_None = 0,
    EgImGuiWindowFlags_NoTitleBar = 1 << 0,   // Disable title-bar
    EgImGuiWindowFlags_NoResize = 1 << 1,   // Disable user resizing with the lower-right grip
    EgImGuiWindowFlags_NoMove = 1 << 2,   // Disable user moving the window
    EgImGuiWindowFlags_NoScrollbar = 1 << 3,   // Disable scrollbars (window can still scroll with mouse or programmatically)
    EgImGuiWindowFlags_NoScrollWithMouse = 1 << 4,   // Disable user vertically scrolling with mouse wheel. On child window, mouse wheel will be forwarded to the parent unless NoScrollbar is also set.
    EgImGuiWindowFlags_NoCollapse = 1 << 5,   // Disable user collapsing window by double-clicking on it. Also referred to as Window Menu Button (e.g. within a docking node).
    EgImGuiWindowFlags_AlwaysAutoResize = 1 << 6,   // Resize every window to its content every frame
    EgImGuiWindowFlags_NoBackground = 1 << 7,   // Disable drawing background color (WindowBg, etc.) and outside border. Similar as using SetNextWindowBgAlpha(0.0f).
    //EgImGuiWindowFlags_NoSavedSettings = 1 << 8,   // Never load/save settings in .ini file
    EgImGuiWindowFlags_NoMouseInputs = 1 << 9,   // Disable catching mouse, hovering test with pass through.
    EgImGuiWindowFlags_MenuBar = 1 << 10,  // Has a menu-bar
    EgImGuiWindowFlags_HorizontalScrollbar = 1 << 11,  // Allow horizontal scrollbar to appear (off by default). You may use SetNextWindowContentSize(ImVec2(width,0.0f)); prior to calling Begin() to specify width. Read code in imgui_demo in the "Horizontal Scrolling" section.
    EgImGuiWindowFlags_NoFocusOnAppearing = 1 << 12,  // Disable taking focus when transitioning from hidden to visible state
    EgImGuiWindowFlags_NoBringToFrontOnFocus = 1 << 13,  // Disable bringing window to front when taking focus (e.g. clicking on it or programmatically giving it focus)
    EgImGuiWindowFlags_AlwaysVerticalScrollbar = 1 << 14,  // Always show vertical scrollbar (even if ContentSize.y < Size.y)
    EgImGuiWindowFlags_AlwaysHorizontalScrollbar = 1 << 15,  // Always show horizontal scrollbar (even if ContentSize.x < Size.x)
    EgImGuiWindowFlags_AlwaysUseWindowPadding = 1 << 16,  // Ensure child windows without border uses style.WindowPadding (ignored by default for non-bordered child windows, because more convenient)
    EgImGuiWindowFlags_NoNavInputs = 1 << 18,  // No gamepad/keyboard navigation within the window
    EgImGuiWindowFlags_NoNavFocus = 1 << 19,  // No focusing toward this window with gamepad/keyboard navigation (e.g. skipped by CTRL+TAB)
    EgImGuiWindowFlags_UnsavedDocument = 1 << 20,  // Display a dot next to the title. When used in a tab/docking context, tab is selected when clicking the X + closure is not assumed (will wait for user to stop submitting the tab). Otherwise closure is assumed when pressing the X, so if you keep submitting the tab may reappear at end of tab bar.
    EgImGuiWindowFlags_NoNav = EgImGuiWindowFlags_NoNavInputs | EgImGuiWindowFlags_NoNavFocus,
    EgImGuiWindowFlags_NoDecoration = EgImGuiWindowFlags_NoTitleBar | EgImGuiWindowFlags_NoResize | EgImGuiWindowFlags_NoScrollbar | EgImGuiWindowFlags_NoCollapse,
    EgImGuiWindowFlags_NoInputs = EgImGuiWindowFlags_NoMouseInputs | EgImGuiWindowFlags_NoNavInputs | EgImGuiWindowFlags_NoNavFocus
};

// This is a 1:1 with ImGuiChildFlags.
enum EgImGuiChildFlags
{
    EgImGuiChildFlags_None = 0,
    EgImGuiChildFlags_Border = 1 << 0,   // Show an outer border and enable WindowPadding. (IMPORTANT: this is always == 1 == true for legacy reason)
    EgImGuiChildFlags_AlwaysUseWindowPadding = 1 << 1,   // Pad with style.WindowPadding even if no border are drawn (no padding by default for non-bordered child windows because it makes more sense)
    EgImGuiChildFlags_ResizeX = 1 << 2,   // Allow resize from right border (layout direction). Enable .ini saving (unless ImGuiWindowFlags_NoSavedSettings passed to window flags)
    EgImGuiChildFlags_ResizeY = 1 << 3,   // Allow resize from bottom border (layout direction). "
    EgImGuiChildFlags_AutoResizeX = 1 << 4,   // Enable auto-resizing width. Read "IMPORTANT: Size measurement" details above.
    EgImGuiChildFlags_AutoResizeY = 1 << 5,   // Enable auto-resizing height. Read "IMPORTANT: Size measurement" details above.
    EgImGuiChildFlags_AlwaysAutoResize = 1 << 6,   // Combined with AutoResizeX/AutoResizeY. Always measure size even when child is hidden, always return true, always disable clipping optimization! NOT RECOMMENDED.
    EgImGuiChildFlags_FrameStyle = 1 << 7,   // Style the child window like a framed item: use FrameBg, FrameRounding, FrameBorderSize, FramePadding instead of ChildBg, ChildRounding, ChildBorderSize, WindowPadding.
};

// This is a 1:1 with ImGuiInputTextFlags.
enum EgImGuiInputTextFlags
{
    EgImGuiInputTextFlags_None = 0,
    EgImGuiInputTextFlags_CharsDecimal = 1 << 0,   // Allow 0123456789.+-*/
    EgImGuiInputTextFlags_CharsHexadecimal = 1 << 1,   // Allow 0123456789ABCDEFabcdef
    EgImGuiInputTextFlags_CharsUppercase = 1 << 2,   // Turn a..z into A..Z
    EgImGuiInputTextFlags_CharsNoBlank = 1 << 3,   // Filter out spaces, tabs
    EgImGuiInputTextFlags_AutoSelectAll = 1 << 4,   // Select entire text when first taking mouse focus
    EgImGuiInputTextFlags_EnterReturnsTrue = 1 << 5,   // Return 'true' when Enter is pressed (as opposed to every time the value was modified). Consider looking at the IsItemDeactivatedAfterEdit() function.
    EgImGuiInputTextFlags_CallbackCompletion = 1 << 6,   // Callback on pressing TAB (for completion handling)
    EgImGuiInputTextFlags_CallbackHistory = 1 << 7,   // Callback on pressing Up/Down arrows (for history handling)
    EgImGuiInputTextFlags_CallbackAlways = 1 << 8,   // Callback on each iteration. User code may query cursor position, modify text buffer.
    EgImGuiInputTextFlags_CallbackCharFilter = 1 << 9,   // Callback on character inputs to replace or discard them. Modify 'EventChar' to replace or discard, or return 1 in callback to discard.
    EgImGuiInputTextFlags_AllowTabInput = 1 << 10,  // Pressing TAB input a '\t' character into the text field
    EgImGuiInputTextFlags_CtrlEnterForNewLine = 1 << 11,  // In multi-line mode, unfocus with Enter, add new line with Ctrl+Enter (default is opposite: unfocus with Ctrl+Enter, add line with Enter).
    EgImGuiInputTextFlags_NoHorizontalScroll = 1 << 12,  // Disable following the cursor horizontally
    EgImGuiInputTextFlags_AlwaysOverwrite = 1 << 13,  // Overwrite mode
    EgImGuiInputTextFlags_ReadOnly = 1 << 14,  // Read-only mode
    EgImGuiInputTextFlags_Password = 1 << 15,  // Password mode, display all characters as '*'
    EgImGuiInputTextFlags_NoUndoRedo = 1 << 16,  // Disable undo/redo. Note that input text owns the text data while active, if you want to provide your own undo/redo stack you need e.g. to call ClearActiveID().
    EgImGuiInputTextFlags_CharsScientific = 1 << 17,  // Allow 0123456789.+-*/eE (Scientific notation input)
    EgImGuiInputTextFlags_CallbackResize = 1 << 18,  // Callback on buffer capacity changes request (beyond 'buf_size' parameter value), allowing the string to grow. Notify when the string wants to be resized (for string types which hold a cache of their Size). You will be provided a new BufSize in the callback and NEED to honor it. (see misc/cpp/imgui_stdlib.h for an example of using this)
    EgImGuiInputTextFlags_CallbackEdit = 1 << 19,  // Callback on any edit (note that InputText() already returns true on edit, the callback is useful mainly to manipulate the underlying buffer while focus is active)
    EgImGuiInputTextFlags_EscapeClearsAll = 1 << 20,  // Escape key clears content if not empty, and deactivate otherwise (contrast to default behavior of Escape to revert)
};

// 1:1 with ImGuiInputTextCallbackData
typedef struct {
    void* Ctx;            // Parent UI context
    EgImGuiInputTextFlags EventFlag;      // One ImGuiInputTextFlags_Callback*    // Read-only
    EgImGuiInputTextFlags Flags;          // What user passed to InputText()      // Read-only
    void* UserData;       // What user passed to InputText()      // Read-only

    // Arguments for the different callback events
    // - To modify the text buffer in a callback, prefer using the InsertChars() / DeleteChars() function. InsertChars() will take care of calling the resize callback if necessary.
    // - If you know your edits are not going to resize the underlying buffer allocation, you may modify the contents of 'Buf[]' directly. You need to update 'BufTextLen' accordingly (0 <= BufTextLen < BufSize) and set 'BufDirty'' to true so InputText can update its internal state.
    unsigned int             EventChar;      // Character input                      // Read-write   // [CharFilter] Replace character with another one, or set to zero to drop. return 1 is equivalent to setting EventChar=0;
    int            EventKey;       // Key pressed (Up/Down/TAB)            // Read-only    // [Completion,History]
    char* Buf;            // Text buffer                          // Read-write   // [Resize] Can replace pointer / [Completion,History,Always] Only write to pointed data, don't replace the actual pointer!
    int                 BufTextLen;     // Text length (in bytes)               // Read-write   // [Resize,Completion,History,Always] Exclude zero-terminator storage. In C land: == strlen(some_text), in C++ land: string.length()
    int                 BufSize;        // Buffer size (in bytes) = capacity+1  // Read-only    // [Resize,Completion,History,Always] Include zero-terminator storage. In C land == ARRAYSIZE(my_char_array), in C++ land: string.capacity()+1
    bool                BufDirty;       // Set if you modify Buf/BufTextLen!    // Write        // [Completion,History,Always]
    int                 CursorPos;      //                                      // Read-write   // [Completion,History,Always]
    int                 SelectionStart; //                                      // Read-write   // [Completion,History,Always] == to SelectionEnd when no selection)
    int                 SelectionEnd;   //                                      // Read-write   // [Completion,History,Always]
} EgImGui_InputTextCallbackData;

extern "C" {

    EG_EXPORT EgImGuiContext egImGuiCreateContextVulkan(
        EgWindow window,
        VkInstance instance,
        VkPhysicalDevice physicalDevice,
        VkDevice device,
        unsigned int graphicsQueueFamilyIndex,
        VkQueue graphicsQueue,
        unsigned int minImageCount,
        unsigned int imageCount,
        VkRenderPass renderPass,
        void(*callbackCheckVulkanInitialization)(VkResult)
    );

    EG_EXPORT void egImGuiDestroyContextVulkan(EgImGuiContext context);

    EG_EXPORT void egImGuiSetScaleFactor(EgImGuiContext context, float scaleFactor);
    EG_EXPORT float egImGuiGetScaleFactor(EgImGuiContext context);
    EG_EXPORT void egImGuiSetMouseCursorChange(EgImGuiContext context, EgImGuiBool value);
    EG_EXPORT unsigned int* egImGui_GetGlyphRangesAll();
    EG_EXPORT unsigned int* egImGui_GetGlyphRangesDefault();
    EG_EXPORT unsigned int* egImGui_GetGlyphRangesGreek();
    EG_EXPORT unsigned int* egImGui_GetGlyphRangesIcon();
    EG_EXPORT unsigned int* egImGui_GetGlyphRangesEmoji();
    EG_EXPORT EgImFont egImGuiAddFontDefault(EgImGuiContext context);
    EG_EXPORT EgImFont egImGuiAddFont(EgImGuiContext context, unsigned char* fontData, int fontDataSize, float pixelSize, unsigned int* ranges);
    EG_EXPORT EgImFont egImGuiMergeFonts(EgImGuiContext context, unsigned char** multipleFontData, int* fontDataSizes, float* pixelSizes, unsigned int** multipleRanges, int length);
    EG_EXPORT void egImGuiPushFont(EgImGuiContext context, EgImFont font);
    EG_EXPORT void egImGuiPopFont(EgImGuiContext context);
    EG_EXPORT void egImGuiUploadFontsVulkan(EgImGuiContext context);
    EG_EXPORT void egImGuiSetDarkMode(EgImGuiContext context);
    EG_EXPORT void egImGuiSetClassicMode(EgImGuiContext context);
    EG_EXPORT void egImGuiNewFrameVulkan(EgImGuiContext context);
    EG_EXPORT void egImGuiEndFrame(EgImGuiContext context);
    EG_EXPORT void egImGuiDrawVulkan(EgImGuiContext context, VkCommandBuffer commandBuffer, VkPipeline pipeline);
    EG_EXPORT void egImGuiSetCurrentContext(EgImGuiContext context);
    EG_EXPORT void egImGuiShowDemoWindow(EgImGuiContext context);

    EG_EXPORT EgImGuiBool egImGuiIsMouseDragging(EgImGuiContext context);
    EG_EXPORT EgImGuiVector2 egImGuiGetMainViewportSize(EgImGuiContext context);

    EG_EXPORT EgImGuiBool egImGuiBegin(EgImGuiContext context, bool& isOpen, bool hideCloseButton, const char* title, EgImGuiWindowFlags flags);
    EG_EXPORT void egImGuiEnd(EgImGuiContext context);
    EG_EXPORT EgImGuiBool egImGui_BeginPopupModal(EgImGuiContext context, bool& isOpen, bool hideCloseButton, const char* title, EgImGuiWindowFlags flags);
    EG_EXPORT void egImGui_EndPopup(EgImGuiContext context);
    EG_EXPORT void egImGui_OpenPopup(EgImGuiContext context, const char* id);
    EG_EXPORT void egImGuiBeginDisabled(EgImGuiContext context, bool isDisabled);
    EG_EXPORT void egImGuiEndDisabled(EgImGuiContext context);
    EG_EXPORT EgImGuiBool egImGuiBeginChild(EgImGuiContext context, unsigned int id, EgImGuiVector2 size, EgImGuiChildFlags childFlags);
    EG_EXPORT void egImGuiEndChild(EgImGuiContext context);
    EG_EXPORT void egImGuiPushId(EgImGuiContext context, int id);
    EG_EXPORT void egImGuiPopId(EgImGuiContext context);
    EG_EXPORT void egImGuiPushItemWidth(EgImGuiContext context, float width);
    EG_EXPORT void egImGuiPopItemWidth(EgImGuiContext context);
    EG_EXPORT void egImGuiSetCursorPositionX(EgImGuiContext context, float x);
    EG_EXPORT void egImGuiSetCursorPositionY(EgImGuiContext context, float y);
    EG_EXPORT float egImGuiGetCursorPositionX(EgImGuiContext context);
    EG_EXPORT float egImGuiGetCursorPositionY(EgImGuiContext context);
    EG_EXPORT EgImGuiVector2 egImGuiGetItemRectSize(EgImGuiContext context);
    EG_EXPORT float egImGuiCalculateItemWidth(EgImGuiContext context);
    EG_EXPORT void egImGuiSetNextWindowBackgroundAlpha(EgImGuiContext context, float alpha);
    EG_EXPORT void egImGuiSetNextWindowPosition(EgImGuiContext context, EgImGuiVector2 position);
    EG_EXPORT void egImGuiSetNextWindowPositionWithPivot(EgImGuiContext context, EgImGuiVector2 position, EgImGuiVector2 pivot);
    EG_EXPORT void egImGuiSetNextWindowSize(EgImGuiContext context, EgImGuiVector2 size);
    EG_EXPORT EgImGuiVector2 egImGuiGetWindowPosition(EgImGuiContext context);
    EG_EXPORT EgImGuiVector2 egImGuiGetWindowSize(EgImGuiContext context);
    EG_EXPORT void egImGuiSetWindowPosition(EgImGuiContext context, EgImGuiVector2 position);
    EG_EXPORT void egImGuiSetWindowSize(EgImGuiContext context, EgImGuiVector2 size);
    EG_EXPORT EgImGuiVector2 egImGuiCalculateWindowSize(EgImGuiContext context);
    EG_EXPORT void egImGuiText(EgImGuiContext context, const char* text);
    EG_EXPORT void egImGuiLabelText(EgImGuiContext context, const char* label, const char* text);
    EG_EXPORT EgImGuiBool egImGuiInputText(EgImGuiContext context, const char* label, char* buffer, size_t bufferSize, EgImGuiInputTextFlags flags, int(*callback)(EgImGui_InputTextCallbackData));
    EG_EXPORT EgImGuiBool egImGuiInputInt(EgImGuiContext context, const char* label, int& value);
    EG_EXPORT EgImGuiBool egImGuiCheckbox(EgImGuiContext context, const char* label, bool& value);
    EG_EXPORT EgImGuiBool egImGuiButton(EgImGuiContext context, const char* label, EgImGuiVector2 size);
    EG_EXPORT EgImGuiBool egImGuiCombo(EgImGuiContext context, const char* label, int& selectedItemIndex, char** items, int itemCount, int popupMaxHeight);
    EG_EXPORT void egImGuiPlotLines(EgImGuiContext context, const char* label, float* values, int valuesLength, int offset, const char* overlayText, float scaleMin, float scaleMax, EgImGuiVector2 size);
    EG_EXPORT VkDescriptorSet egImGuiAddTextureVulkan(EgImGuiContext context, VkSampler sampler, VkImageView imageView, VkImageLayout imageLayout);
    EG_EXPORT void egImGuiRemoveTextureVulkan(EgImGuiContext context, VkDescriptorSet descriptorSet);
    EG_EXPORT void egImGuiImageVulkan(EgImGuiContext context, VkDescriptorSet texture, EgImGuiVector2 size, EgImGuiVector2 uv0, EgImGuiVector2 uv1, EgImGuiVector4 borderColor);

    EG_EXPORT EgImGuiBool egImGuiBeginTabBar(EgImGuiContext context);
    EG_EXPORT unsigned int egImGuiGetSelectedTabId(EgImGuiContext context);
    EG_EXPORT void egImGuiFocusTabById(EgImGuiContext context, unsigned int tabId);
    EG_EXPORT void egImGuiEndTabBar(EgImGuiContext context);
    EG_EXPORT EgImGuiBool egImGuiBeginTabItem(EgImGuiContext context, const char* label, bool& isOpen);
    EG_EXPORT void egImGuiEndTabItem(EgImGuiContext context);

    EG_EXPORT void egImGuiBeginGroup(EgImGuiContext context);
    EG_EXPORT void egImGuiEndGroup(EgImGuiContext context);
    EG_EXPORT EgImGuiBool egImGuiBeginListBox(EgImGuiContext context, const char* label, EgImGuiVector2 size);
    EG_EXPORT void egImGuiEndListBox(EgImGuiContext context);
    EG_EXPORT EgImGuiBool egImGuiBeginItemTooltip(EgImGuiContext context);
    EG_EXPORT void egImGuiEndTooltip(EgImGuiContext context);

    EG_EXPORT EgImGuiBool egImGuiBeginTable(EgImGuiContext context, int columnCount);
    EG_EXPORT void egImGuiEndTable(EgImGuiContext context);
    EG_EXPORT int egImGuiTableGetCurrentRow(EgImGuiContext context);
    EG_EXPORT void egImGuiTableNextRow(EgImGuiContext context);
    EG_EXPORT EgImGuiBool egImGuiTableSetColumnIndex(EgImGuiContext context, int columnIndex);
    EG_EXPORT void egImGuiBeginTableCell(EgImGuiContext context, int column);
    EG_EXPORT void egImGuiEndTableCell(EgImGuiContext context);

    EG_EXPORT void egImGuiBeginClipper(EgImGuiContext context, int amount);
    EG_EXPORT void egImGuiEndClipper(EgImGuiContext context);
    EG_EXPORT EgImGuiBool egImGuiClipperStep(EgImGuiContext context);
    EG_EXPORT int egImGuiClipperDisplayStart(EgImGuiContext context);
    EG_EXPORT int egImGuiClipperDisplayEnd(EgImGuiContext context);

    EG_EXPORT void egImGuiTableSetupColumnNoHeaderLabel(EgImGuiContext context);
    EG_EXPORT EgImGuiBool egImGuiTableNextColumn(EgImGuiContext context);

    EG_EXPORT void egImGuiTextUnformatted(EgImGuiContext context, const char* text, const char* textEnd);
    EG_EXPORT void egImGui_ScrollbarX(EgImGuiContext context);
    EG_EXPORT void egImGui_ScrollbarY(EgImGuiContext context);

    EG_EXPORT void egImGuiSameLine(EgImGuiContext context);
    EG_EXPORT void egImGuiSameLineWithOffset(EgImGuiContext context, float offsetFromStartX);
    EG_EXPORT void egImGuiSameLineWithOffsetAndSpacing(EgImGuiContext context, float offsetFromStartX, float spacing);
    EG_EXPORT EgImGuiVector2 egImGuiGetContentRegionAvail(EgImGuiContext context);
    EG_EXPORT EgImGuiBool egImGuiIsItemHovered(EgImGuiContext context);
    EG_EXPORT EgImGuiBool egImGuiIsWindowHovered(EgImGuiContext context);
    EG_EXPORT EgImGuiBool egImGuiIsItemClicked(EgImGuiContext context);
    EG_EXPORT EgImGuiBool egImGuiSliderFloat(EgImGuiContext context, const char* label, float min, float max, float* value);

    EG_EXPORT float egImGui_GetScrollMaxX(EgImGuiContext context);
    EG_EXPORT float egImGui_GetScrollMaxY(EgImGuiContext context);
    EG_EXPORT float egImGui_GetScrollX(EgImGuiContext context);
    EG_EXPORT float egImGui_GetScrollY(EgImGuiContext context);
    EG_EXPORT void egImGui_SetScrollX(EgImGuiContext context, float value);
    EG_EXPORT void egImGui_SetScrollY(EgImGuiContext context, float value);
    EG_EXPORT void egImGui_SetScrollHereX(EgImGuiContext context, float centerRatio);
    EG_EXPORT void egImGui_SetScrollHereY(EgImGuiContext context, float centerRatio);
    EG_EXPORT void egImGui_SetNextWindowScroll(EgImGuiContext context, EgImGuiVector2 value);
    EG_EXPORT void egImGui_SetFocus(EgImGuiContext context, unsigned int id);
    EG_EXPORT EgImGuiBool egImGui_IsWindowFocused(EgImGuiContext context);
    EG_EXPORT EgImGuiBool egImGui_IsItemFocused(EgImGuiContext context);
    EG_EXPORT unsigned int egImGui_GetItemId(EgImGuiContext context);
    EG_EXPORT void egImGui_SetWindowFocus(EgImGuiContext context);
    EG_EXPORT void egImGui_SetKeyboardFocusHere(EgImGuiContext context);
    EG_EXPORT void egImGui_BringCurrentWindowToDisplayFront(EgImGuiContext context);
    EG_EXPORT void egImGui_Dummy(EgImGuiContext context, EgImGuiVector2 size);

    /* Style */

    EG_EXPORT EgImGuiVector2 egImGui_GetCellPadding(EgImGuiContext context);
    EG_EXPORT EgImGuiVector2 egImGui_GetFramePadding(EgImGuiContext context);
    EG_EXPORT EgImGuiVector2 egImGui_GetWindowPadding(EgImGuiContext context);
    EG_EXPORT EgImGuiVector2 egImGui_GetItemSpacing(EgImGuiContext context);
    EG_EXPORT EgImGuiVector2 egImGui_GetItemInnerSpacing(EgImGuiContext context);
    EG_EXPORT void egImGui_SetCellPadding(EgImGuiContext context, EgImGuiVector2 cellPadding);
    EG_EXPORT void egImGui_PushStyleColor_Text(EgImGuiContext context, EgImGuiVector4 color);
    EG_EXPORT void egImGui_PushStyleColor_Button(EgImGuiContext context, EgImGuiVector4 color);
    EG_EXPORT void egImGui_PushStyleColor_ButtonHovered(EgImGuiContext context, EgImGuiVector4 color);
    EG_EXPORT void egImGui_PushStyleColor_ButtonActive(EgImGuiContext context, EgImGuiVector4 color);
    EG_EXPORT void egImGui_PushStyleColor_WindowBackground(EgImGuiContext context, EgImGuiVector4 color);
    EG_EXPORT void egImGui_PushStyleColor_ChildBackground(EgImGuiContext context, EgImGuiVector4 color);
    EG_EXPORT void egImGui_PushStyleColor_PopupBackground(EgImGuiContext context, EgImGuiVector4 color);
    EG_EXPORT void egImGui_PushStyleColor_FrameBackground(EgImGuiContext context, EgImGuiVector4 color);
    EG_EXPORT void egImGui_PushStyleColor_FrameBackgroundHovered(EgImGuiContext context, EgImGuiVector4 color);
    EG_EXPORT void egImGui_PushStyleColor_FrameBackgroundActive(EgImGuiContext context, EgImGuiVector4 color);
    EG_EXPORT void egImGui_PushStyleColor_ModalWindowDimBackground(EgImGuiContext context, EgImGuiVector4 color);
    EG_EXPORT void egImGui_PopStyleColor(EgImGuiContext context);
    EG_EXPORT EgImGuiVector2 egImGui_GetStyleVar_WindowPadding(EgImGuiContext context);
    EG_EXPORT void egImGui_PushStyleVar_WindowPadding(EgImGuiContext context, EgImGuiVector2 padding);
    EG_EXPORT void egImGui_PopStyleVar(EgImGuiContext context);
    EG_EXPORT EgImGuiVector2 egImGui_GetStyleVar_WindowBorderSize(EgImGuiContext context);
    EG_EXPORT void egImGui_PushStyleVar_WindowBorderSize(EgImGuiContext context, EgImGuiVector2 value);
}


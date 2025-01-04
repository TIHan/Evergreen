/*

These defines:

#define IMGUI_ENABLE_FREETYPE 1
#define IMGUI_ENABLE_FREETYPE_LUNASVG 1

Need to be put in 'imgui.h' manually.

*/

#include <imgui.h>
#include <imgui_freetype.h>
#include <backends/imgui_impl_vulkan.h>
#include <backends/imgui_impl_sdl3.h>
#include <imgui_internal.h>
#include <vulkan/vulkan.h>
#include <stdexcept>
#include <stack>
#include <windows.h>
#include <SDL3/SDL.h>

using namespace std;

#include "egImGui.h"

struct EgImGuiContextInternal {
    ImGuiContext* ctx;
    ImGui_ImplVulkan_InitInfo info;
    SDL_Window* sdlWindow;
    std::stack<ImGuiListClipper*> clipperStack;
    float scaleFactor;
};

EgImGuiContextInternal* GetInternalContext(EgImGuiContext context)
{
    return (EgImGuiContextInternal*)context.internal;
}

ImFont* GetInternalFont(EgImFont font)
{
    return (ImFont*)font.internal;
}

inline EgImGuiBool ToEgBool(bool value)
{
    if (value)
        return 1;
    return 0;
}

inline EgImGuiVector2 ToEgVector2(ImVec2 value)
{
    return *(EgImGuiVector2*)&value;
}

inline ImVec2 ToImVec2(EgImGuiVector2 value)
{
    return *(ImVec2*)&value;
}

inline ImVec4 ToImVec4(EgImGuiVector4 value)
{
    return *(ImVec4*)&value;
}

VkDescriptorPoolSize createPool(VkDescriptorType descriptorType, unsigned int count)
{
    VkDescriptorPoolSize poolSize = {};
    poolSize.type = descriptorType;
    poolSize.descriptorCount = count;
    return poolSize;
}

int FilterBackQuote(ImGuiInputTextCallbackData* data)
{
    if (data->EventChar == '`')
    {
        return 1;
    }
    return 0;
}

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
    )
    {
        auto ctx = ImGui::CreateContext();

        ImGui_ImplVulkan_InitInfo info = {};
        info.Instance = instance;
        info.PhysicalDevice = physicalDevice;
        info.Device = device;
        info.QueueFamily = graphicsQueueFamilyIndex;
        info.Queue = graphicsQueue;
        info.PipelineCache = nullptr;
        info.Subpass = 0;
        info.MinImageCount = minImageCount;
        info.ImageCount = imageCount;
        info.MSAASamples = VK_SAMPLE_COUNT_1_BIT;
        info.Allocator = nullptr;
        info.CheckVkResultFn = callbackCheckVulkanInitialization;
        info.RenderPass = renderPass;

        VkDescriptorPoolSize poolSizes[] =
        {
            createPool(VK_DESCRIPTOR_TYPE_SAMPLER, 1000),
            createPool(VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 1000),
            createPool(VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE, 1000),
            createPool(VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, 1000),
            createPool(VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER, 1000),
            createPool(VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER, 1000),
            createPool(VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 1000),
            createPool(VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, 1000),
            createPool(VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC, 1000),
            createPool(VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC, 1000),
            createPool(VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT, 1000)
        };

        VkDescriptorPoolCreateInfo poolInfo = {};
        poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
        poolInfo.flags = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT;
        poolInfo.maxSets = 1000 * IM_ARRAYSIZE(poolSizes);
        poolInfo.poolSizeCount = IM_ARRAYSIZE(poolSizes);
        poolInfo.pPoolSizes = poolSizes;

        if (vkCreateDescriptorPool(device, &poolInfo, nullptr, &info.DescriptorPool) != VK_SUCCESS)
            throw std::runtime_error("Failed to create descriptor pool for ImGui.");

        ImGui::SetCurrentContext(ctx);

        SDL_Window* sdlWindow = (SDL_Window*)window.internal;

        if (!ImGui_ImplSDL3_InitForVulkan(sdlWindow))
            throw std::runtime_error("Failed to initialize ImGui for Win32.");

        if (!ImGui_ImplVulkan_Init(&info))
            throw std::runtime_error("Failed to initialize ImGui for Vulkan.");

        auto style = &ImGui::GetStyle();
        style->ScaleAllSizes(1);
        style->DisplayWindowPadding = ImVec2(0, 0);

        auto io = &ImGui::GetIO();
        io->ConfigWindowsMoveFromTitleBarOnly = true;
        io->IniFilename = nullptr;
        io->LogFilename = nullptr;

        auto internal = new EgImGuiContextInternal();
        internal->ctx = ctx;
        internal->sdlWindow = sdlWindow;
        internal->info = info;

        EgImGuiContext context = {};
        context.internal = internal;
        return context;
    }

    EG_EXPORT void egImGuiDestroyContextVulkan(EgImGuiContext context)
    {
        auto internal = GetInternalContext(context);

        ImGui_ImplVulkan_Shutdown();
        ImGui_ImplSDL3_Shutdown();
        vkDestroyDescriptorPool(internal->info.Device, internal->info.DescriptorPool, nullptr);
        ImGui::DestroyContext(internal->ctx);
        delete context.internal;
        context.internal = nullptr;
    }

    EG_EXPORT void egImGuiSetScaleFactor(EgImGuiContext context, float scaleFactor)
    {
        GetInternalContext(context)->scaleFactor = scaleFactor;
        auto style = &ImGui::GetStyle();
        style->ScaleAllSizes(scaleFactor);
    }

    EG_EXPORT float egImGuiGetScaleFactor(EgImGuiContext context)
    {
        return GetInternalContext(context)->scaleFactor;
    }

    EG_EXPORT void egImGuiSetMouseCursorChange(EgImGuiContext context, EgImGuiBool value)
    {
        auto io = &ImGui::GetIO();

        if (value)
        {
            io->ConfigFlags &= ~ImGuiConfigFlags_NoMouseCursorChange;
        }
        else
        {
            io->ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange;
        }
    }

    EG_EXPORT unsigned int* egImGui_GetGlyphRangesAll()
    {
        static ImWchar ranges[] = { 0x1, 0x1FFFF, 0 };
        return ranges;
    }

    EG_EXPORT unsigned int* egImGui_GetGlyphRangesDefault()
    {
        auto io = &ImGui::GetIO();
        return (unsigned int*)io->Fonts->GetGlyphRangesDefault();
    }

    EG_EXPORT unsigned int* egImGui_GetGlyphRangesGreek()
    {
        auto io = &ImGui::GetIO();
        return (unsigned int*)io->Fonts->GetGlyphRangesGreek();
    }

    EG_EXPORT unsigned int* egImGui_GetGlyphRangesIcon()
    {
        static ImWchar ranges[] = { 0xf000, 0xf3ff, 0 };
        return ranges;
    }

    EG_EXPORT unsigned int* egImGui_GetGlyphRangesEmoji()
    {
        static ImWchar ranges[] = { 0x10000, 0x1FFFF, 0 };
        return ranges;
    }

    EG_EXPORT EgImFont egImGuiAddFontDefault(EgImGuiContext context)
    {
        auto io = &ImGui::GetIO();
        auto font = io->Fonts->AddFontDefault();

        EgImFont egFont;
        egFont.internal = font;
        return egFont;
    }

    EG_EXPORT EgImFont egImGuiAddFont(EgImGuiContext context, unsigned char* fontData, int fontDataSize, float pixelSize, unsigned int* ranges)
    {
        auto io = &ImGui::GetIO();

        ImFontConfig fontConfig = {};

        // Do this to avoid memory corruption when destroying the context.
        fontConfig.FontDataOwnedByAtlas = false;

        fontConfig.FontBuilderFlags |= ImGuiFreeTypeBuilderFlags_LoadColor;

        auto font = io->Fonts->AddFontFromMemoryTTF(fontData, fontDataSize, pixelSize, &fontConfig, ranges);

        // We only do this to force load the ranges.
        int width, height;
        unsigned char* pixels = nullptr;
        io->Fonts->GetTexDataAsRGBA32(&pixels, &width, &height);

        EgImFont egFont;
        egFont.internal = font;
        return egFont;
    }

    EG_EXPORT EgImFont egImGuiMergeFonts(EgImGuiContext context, unsigned char** multipleFontData, int* fontDataSizes, float* pixelSizes, unsigned int** multipleRanges, int length)
    {
        auto io = &ImGui::GetIO();

        ImFontConfig fontConfig = {};

        // Do this to avoid memory corruption when destroying the context.
        fontConfig.FontDataOwnedByAtlas = false;

        fontConfig.MergeMode = (length > 1);
        fontConfig.FontBuilderFlags |= ImGuiFreeTypeBuilderFlags_LoadColor;

        ImFont* font = nullptr;
        for (int i = 0; i < length; i++)
        {
            auto fontData = multipleFontData[i];
            auto fontDataSize = fontDataSizes[i];
            auto pixelSize = pixelSizes[i];
            auto ranges = multipleRanges[i];
            if (font)
            {
                io->Fonts->AddFontFromMemoryTTF(fontData, fontDataSize, pixelSize, &fontConfig, ranges);
            }
            else
            {
                fontConfig.MergeMode = false;
                font = io->Fonts->AddFontFromMemoryTTF(fontData, fontDataSize, pixelSize, &fontConfig, ranges);
                fontConfig.MergeMode = true;
            }
        }

        if (fontConfig.MergeMode)
            io->Fonts->Build();
        
        // We only do this to force load the ranges.
        int width, height;
        unsigned char* pixels = nullptr;
        io->Fonts->GetTexDataAsRGBA32(&pixels, &width, &height);

        EgImFont egFont;
        egFont.internal = font;
        return egFont;
    }

    EG_EXPORT void egImGuiPushFont(EgImGuiContext context, EgImFont font)
    {
        ImGui::PushFont((ImFont*)font.internal);
    }

    EG_EXPORT void egImGuiPopFont(EgImGuiContext context)
    {
        ImGui::PopFont();
    }

    EG_EXPORT void egImGuiUploadFontsVulkan(EgImGuiContext context)
    {
        ImGui_ImplVulkan_CreateFontsTexture();
    }

    EG_EXPORT void egImGuiSetDarkMode(EgImGuiContext context)
    {
        ImGui::StyleColorsDark(nullptr);
    }

    EG_EXPORT void egImGuiSetClassicMode(EgImGuiContext context)
    {
        ImGui::StyleColorsClassic(nullptr);
    }

    EG_EXPORT void egImGuiNewFrameVulkan(EgImGuiContext context)
    {
        ImGui_ImplVulkan_NewFrame();
        ImGui_ImplSDL3_NewFrame();
        ImGui::NewFrame();
    }

    EG_EXPORT void egImGuiEndFrame(EgImGuiContext context)
    {
        ImGui::EndFrame();
    }

    EG_EXPORT void egImGuiDrawVulkan(EgImGuiContext context, VkCommandBuffer commandBuffer, VkPipeline pipeline)
    {
        ImGui::Render();
        auto drawData = ImGui::GetDrawData();
        ImGui_ImplVulkan_RenderDrawData(drawData, commandBuffer, pipeline);
    }

    EG_EXPORT void egImGuiSetCurrentContext(EgImGuiContext context)
    {
        ImGui::SetCurrentContext(GetInternalContext(context)->ctx);
    }

    EG_EXPORT void egImGuiShowDemoWindow(EgImGuiContext context)
    {
        auto open = true;
        ImGui::ShowDemoWindow(&open);
    }

    EG_EXPORT EgImGuiBool egImGuiIsMouseDragging(EgImGuiContext context)
    {
        return ImGui::IsMouseDragging(ImGuiMouseButton_Left);
    }

    EG_EXPORT EgImGuiVector2 egImGuiGetMainViewportSize(EgImGuiContext context)
    {
        auto size = ImGui::GetMainViewport()->Size;
        return ToEgVector2(size);
    }

    EG_EXPORT EgImGuiBool egImGuiBegin(EgImGuiContext context, bool& isOpen, bool hideCloseButton, const char* title, EgImGuiWindowFlags flags)
    {
        auto open = true;
        bool* pOpen = nullptr;
        if (!hideCloseButton)
            pOpen = &open;

        auto result = ImGui::Begin(title, pOpen, flags | ImGuiWindowFlags_NoSavedSettings);
        isOpen = open;
        return ToEgBool(result);
    }

    EG_EXPORT void egImGuiEnd(EgImGuiContext context)
    {
        ImGui::End();
    }

    EG_EXPORT EgImGuiBool egImGui_BeginPopupModal(EgImGuiContext context, bool& isOpen, bool hideCloseButton, const char* title, EgImGuiWindowFlags flags)
    {
        auto open = true;
        bool* pOpen = nullptr;
        if (!hideCloseButton)
            pOpen = &open;

        auto result = ImGui::BeginPopupModal(title, pOpen, flags | ImGuiWindowFlags_NoSavedSettings);
        isOpen = open;
        return ToEgBool(result);
    }

    EG_EXPORT void egImGui_EndPopup(EgImGuiContext context)
    {
        ImGui::EndPopup();
    }

    EG_EXPORT void egImGui_OpenPopup(EgImGuiContext context, const char* id)
    {
        ImGui::OpenPopup(id);
    }

    EG_EXPORT void egImGuiBeginDisabled(EgImGuiContext context, bool isDisabled)
    {
        ImGui::BeginDisabled(isDisabled);
    }

    EG_EXPORT void egImGuiEndDisabled(EgImGuiContext context)
    {
        ImGui::EndDisabled();
    }

    EG_EXPORT EgImGuiBool egImGuiBeginChild(EgImGuiContext context, unsigned int id, EgImGuiVector2 size, EgImGuiChildFlags childFlags)
    {
        return ToEgBool(ImGui::BeginChild(id, ToImVec2(size), childFlags));
    }

    EG_EXPORT void egImGuiEndChild(EgImGuiContext context)
    {
        ImGui::EndChild();
    }

    EG_EXPORT void egImGuiPushId(EgImGuiContext context, int id)
    {
        ImGui::PushID(id);
    }

    EG_EXPORT void egImGuiPopId(EgImGuiContext context)
    {
        ImGui::PopID();
    }

    EG_EXPORT void egImGuiPushItemWidth(EgImGuiContext context, float width)
    {
        ImGui::PushItemWidth(width);
    }

    EG_EXPORT void egImGuiPopItemWidth(EgImGuiContext context)
    {
        ImGui::PopItemWidth();
    }

    EG_EXPORT void egImGuiSetCursorPositionX(EgImGuiContext context, float x)
    {
        ImGui::SetCursorPosX(x);
    }

    EG_EXPORT void egImGuiSetCursorPositionY(EgImGuiContext context, float y)
    {
        ImGui::SetCursorPosY(y);
    }

    EG_EXPORT EgImGuiVector2 egImGuiGetItemRectSize(EgImGuiContext context)
    {
        return ToEgVector2(ImGui::GetItemRectSize());
    }

    EG_EXPORT float egImGuiGetCursorPositionX(EgImGuiContext context)
    {
        return ImGui::GetCursorPosX();
    }

    EG_EXPORT float egImGuiGetCursorPositionY(EgImGuiContext context)
    {
        return ImGui::GetCursorPosY();
    }

    EG_EXPORT float egImGuiCalculateItemWidth(EgImGuiContext context)
    {
        return ImGui::CalcItemWidth();
    }

    EG_EXPORT void egImGuiSetNextWindowBackgroundAlpha(EgImGuiContext context, float alpha)
    {
        ImGui::SetNextWindowBgAlpha(alpha);
    }

    EG_EXPORT void egImGuiSetNextWindowPosition(EgImGuiContext context, EgImGuiVector2 position)
    {
        ImGui::SetNextWindowPos(ToImVec2(position));
    }

    EG_EXPORT void egImGuiSetNextWindowPositionWithPivot(EgImGuiContext context, EgImGuiVector2 position, EgImGuiVector2 pivot)
    {
        ImGui::SetNextWindowPos(ToImVec2(position), ImGuiCond_Always, ToImVec2(pivot));
    }

    EG_EXPORT void egImGuiSetNextWindowSize(EgImGuiContext context, EgImGuiVector2 size)
    {
        ImGui::SetNextWindowSize(ToImVec2(size));
    }

    EG_EXPORT EgImGuiVector2 egImGuiGetWindowPosition(EgImGuiContext context)
    {
        auto value = ImGui::GetWindowPos();
        return ToEgVector2(value);
    }

    EG_EXPORT EgImGuiVector2 egImGuiGetWindowSize(EgImGuiContext context)
    {
        auto value = ImGui::GetWindowSize();
        return ToEgVector2(value);
    }

    EG_EXPORT void egImGuiSetWindowPosition(EgImGuiContext context, EgImGuiVector2 position)
    {
        auto window = ImGui::GetCurrentWindow();
        ImGui::SetWindowPos(window, ToImVec2(position));
    }

    EG_EXPORT void egImGuiSetWindowSize(EgImGuiContext context, EgImGuiVector2 size)
    {
        auto window = ImGui::GetCurrentWindow();
        ImGui::SetWindowSize(window, ToImVec2(size));
    }

    EG_EXPORT EgImGuiVector2 egImGuiCalculateWindowSize(EgImGuiContext context)
    {
        auto window = ImGui::GetCurrentWindow();
        auto value = ImGui::CalcWindowNextAutoFitSize(window);
        return ToEgVector2(value);
    }

    EG_EXPORT void egImGuiText(EgImGuiContext context, const char* text)
    {
        ImGui::Text(text);
    }

    EG_EXPORT void egImGuiLabelText(EgImGuiContext context, const char* label, const char* text)
    {
        ImGui::LabelText(label, text);
    }

    EG_EXPORT EgImGuiBool egImGuiInputText(EgImGuiContext context, const char* label, char* buffer, size_t bufferSize, EgImGuiInputTextFlags flags, int(*callback)(EgImGui_InputTextCallbackData))
    {
        return ToEgBool(ImGui::InputText(label, buffer, bufferSize, flags, (ImGuiInputTextCallback)(callback)));
    }

    EG_EXPORT EgImGuiBool egImGuiInputInt(EgImGuiContext context, const char* label, int& value)
    {
        return ToEgBool(ImGui::InputInt(label, &value));
    }

    EG_EXPORT EgImGuiBool egImGuiCheckbox(EgImGuiContext context, const char* label, bool& value)
    {
        return ToEgBool(ImGui::Checkbox(label, &value));
    }

    EG_EXPORT EgImGuiBool egImGuiButton(EgImGuiContext context, const char* label, EgImGuiVector2 size)
    {
        return ToEgBool(ImGui::Button(label, ToImVec2(size)));
    }

    EG_EXPORT EgImGuiBool egImGuiCombo(EgImGuiContext context, const char* label, int& selectedItemIndex, char** items, int itemCount, int popupMaxHeight)
    {
        return ToEgBool(ImGui::Combo(label, &selectedItemIndex, items, itemCount, popupMaxHeight));
    }

    EG_EXPORT void egImGuiPlotLines(EgImGuiContext context, const char* label, float* values, int valuesLength, int offset, const char* overlayText, float scaleMin, float scaleMax, EgImGuiVector2 size)
    {
        ImGui::PlotLines(label, values, valuesLength, offset, overlayText, scaleMin, scaleMax, *(ImVec2*)&size, 4);
    }

    EG_EXPORT VkDescriptorSet egImGuiAddTextureVulkan(EgImGuiContext context, VkSampler sampler, VkImageView imageView, VkImageLayout imageLayout)
    {
        return ImGui_ImplVulkan_AddTexture(sampler, imageView, imageLayout);
    }

    EG_EXPORT void egImGuiRemoveTextureVulkan(EgImGuiContext context, VkDescriptorSet descriptorSet)
    {
        ImGui_ImplVulkan_RemoveTexture(descriptorSet);
    }

    EG_EXPORT void egImGuiImageVulkan(EgImGuiContext context, VkDescriptorSet texture, EgImGuiVector2 size, EgImGuiVector2 uv0, EgImGuiVector2 uv1, EgImGuiVector4 borderColor)
    {
        ImGui::Image(texture, ToImVec2(size), ToImVec2(uv0), ToImVec2(uv1), ImVec4(255, 255, 255, 255), ImVec4(borderColor.x, borderColor.y, borderColor.z, borderColor.w));
    }

    EG_EXPORT EgImGuiBool egImGuiBeginTabBar(EgImGuiContext context)
    {
        return ToEgBool(ImGui::BeginTabBar(""));
    }

    EG_EXPORT unsigned int egImGuiGetSelectedTabId(EgImGuiContext context)
    {
        auto bar = ImGui::GetCurrentTabBar();
        if (bar)
        {
            return bar->SelectedTabId;
        }
        return 0;
    }

    EG_EXPORT void egImGuiFocusTabById(EgImGuiContext context, unsigned int tabId)
    {
        auto bar = ImGui::GetCurrentTabBar();
        if (bar)
        {         
            auto item = ImGui::TabBarFindTabByID(bar, tabId);
            if (item)
            {
                ImGui::TabBarQueueFocus(bar, item);
            }
        }
    }

    EG_EXPORT void egImGuiEndTabBar(EgImGuiContext context)
    {
        ImGui::EndTabBar();
    }

    EG_EXPORT EgImGuiBool egImGuiBeginTabItem(EgImGuiContext context, const char* label, bool& isOpen)
    {
        return ToEgBool(ImGui::BeginTabItem(label, &isOpen, ImGuiTabItemFlags_NoCloseButton | ImGuiTabItemFlags_NoCloseWithMiddleMouseButton));
    }

    EG_EXPORT void egImGuiEndTabItem(EgImGuiContext context)
    {
        ImGui::EndTabItem();
    }

    EG_EXPORT void egImGuiBeginGroup(EgImGuiContext context)
    {
        ImGui::BeginGroup();
    }

    EG_EXPORT void egImGuiEndGroup(EgImGuiContext context)
    {
        ImGui::EndGroup();
    }

    EG_EXPORT EgImGuiBool egImGuiBeginListBox(EgImGuiContext context, const char* label, EgImGuiVector2 size)
    {
        return ToEgBool(ImGui::BeginListBox(label, ToImVec2(size)));
    }

    EG_EXPORT void egImGuiEndListBox(EgImGuiContext context)
    {
        ImGui::EndListBox();
    }

    EG_EXPORT EgImGuiBool egImGuiBeginItemTooltip(EgImGuiContext context)
    {
        return ImGui::BeginItemTooltip();
    }

    EG_EXPORT void egImGuiEndTooltip(EgImGuiContext context)
    {
        ImGui::EndTooltip();
    }

    EG_EXPORT EgImGuiBool egImGuiBeginTable(EgImGuiContext context, int columnCount)
    {
        return ImGui::BeginTable("", columnCount, ImGuiTableFlags_PreciseWidths | ImGuiTableFlags_SizingFixedFit | ImGuiTableFlags_NoSavedSettings);
    }

    EG_EXPORT void egImGuiEndTable(EgImGuiContext context)
    {
        ImGui::EndTable();
    }

    EG_EXPORT int egImGuiTableGetCurrentRow(EgImGuiContext context)
    {
        return ImGui::GetCurrentTable()->CurrentRow;
    }

    EG_EXPORT void egImGuiTableNextRow(EgImGuiContext context)
    {
        ImGui::TableNextRow();
    }

    EG_EXPORT EgImGuiBool egImGuiTableSetColumnIndex(EgImGuiContext context, int columnIndex)
    {
        return ImGui::TableSetColumnIndex(columnIndex);
    }

    EG_EXPORT void egImGuiBeginTableCell(EgImGuiContext context, int column)
    {
        ImGui::TableBeginCell(ImGui::GetCurrentTable(), column);
    }

    EG_EXPORT void egImGuiEndTableCell(EgImGuiContext context)
    {
        ImGui::TableEndCell(ImGui::GetCurrentTable());
    }

    EG_EXPORT void egImGuiBeginClipper(EgImGuiContext context, int amount)
    {
        auto internal = GetInternalContext(context);
        ImGuiListClipper* clipper = new ImGuiListClipper();
        clipper->Begin(amount);
        internal->clipperStack.push(clipper);
    }

    EG_EXPORT void egImGuiEndClipper(EgImGuiContext context)
    {
        ImGuiListClipper* clipper = GetInternalContext(context)->clipperStack.top();
        GetInternalContext(context)->clipperStack.pop();
        delete clipper;
    }

    EG_EXPORT EgImGuiBool egImGuiClipperStep(EgImGuiContext context)
    {
        return GetInternalContext(context)->clipperStack.top()->Step();
    }

    EG_EXPORT int egImGuiClipperDisplayStart(EgImGuiContext context)
    {
        return GetInternalContext(context)->clipperStack.top()->DisplayStart;
    }

    EG_EXPORT int egImGuiClipperDisplayEnd(EgImGuiContext context)
    {
        return GetInternalContext(context)->clipperStack.top()->DisplayEnd;
    }

    EG_EXPORT void egImGuiTableSetupColumnNoHeaderLabel(EgImGuiContext context)
    {
        ImGui::TableSetupColumn("", ImGuiTableColumnFlags_NoHeaderLabel | ImGuiTableColumnFlags_NoHeaderWidth);
    }

    EG_EXPORT EgImGuiBool egImGuiTableNextColumn(EgImGuiContext context)
    {
        return ImGui::TableNextColumn();
    }

    EG_EXPORT void egImGuiTextUnformatted(EgImGuiContext context, const char* text, const char* textEnd)
    {
        ImGui::TextUnformatted(text, textEnd);
    }

    EG_EXPORT void egImGui_ScrollbarX(EgImGuiContext context)
    {
        ImGui::Scrollbar(ImGuiAxis_X);
    }

    EG_EXPORT void egImGui_ScrollbarY(EgImGuiContext context)
    {
        ImGui::Scrollbar(ImGuiAxis_Y);
    }

    EG_EXPORT void egImGuiSameLine(EgImGuiContext context)
    {
        ImGui::SameLine();
    }

    EG_EXPORT void egImGuiSameLineWithOffset(EgImGuiContext context, float offsetFromStartX)
    {
        ImGui::SameLine(offsetFromStartX);
    }

    EG_EXPORT void egImGuiSameLineWithOffsetAndSpacing(EgImGuiContext context, float offsetFromStartX, float spacing)
    {
        ImGui::SameLine(offsetFromStartX, spacing);
    }

    EG_EXPORT EgImGuiVector2 egImGuiGetContentRegionAvail(EgImGuiContext context)
    {
        return ToEgVector2(ImGui::GetContentRegionAvail());
    }

    EG_EXPORT EgImGuiBool egImGuiIsItemHovered(EgImGuiContext context)
    {
        return ToEgBool(ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenBlockedByActiveItem));
    }

    EG_EXPORT EgImGuiBool egImGuiIsWindowHovered(EgImGuiContext context)
    {
        return ToEgBool(ImGui::IsWindowHovered(ImGuiHoveredFlags_AllowWhenBlockedByActiveItem | ImGuiHoveredFlags_ChildWindows));
    }

    EG_EXPORT EgImGuiBool egImGuiIsItemClicked(EgImGuiContext context)
    {
        return ToEgBool(ImGui::IsItemClicked());
    }

    EG_EXPORT EgImGuiBool egImGuiSliderFloat(EgImGuiContext context, const char* label, float min, float max, float* value)
    {
        return ToEgBool(ImGui::SliderFloat(label, value, min, max));
    }

    EG_EXPORT float egImGui_GetScrollMaxX(EgImGuiContext context)
    {
        return ImGui::GetScrollMaxX();
    }

    EG_EXPORT float egImGui_GetScrollMaxY(EgImGuiContext context)
    {
        return ImGui::GetScrollMaxY();
    }

    EG_EXPORT float egImGui_GetScrollX(EgImGuiContext context)
    {
        return ImGui::GetScrollX();
    }

    EG_EXPORT float egImGui_GetScrollY(EgImGuiContext context)
    {
        return ImGui::GetScrollY();
    }

    EG_EXPORT void egImGui_SetScrollX(EgImGuiContext context, float value)
    {
        ImGui::SetScrollX(value);
    }

    EG_EXPORT void egImGui_SetScrollY(EgImGuiContext context, float value)
    {
        ImGui::SetScrollY(value);
    }
    
    EG_EXPORT void egImGui_SetScrollHereX(EgImGuiContext context, float centerRatio)
    {
        ImGui::SetScrollHereX(centerRatio);
    }

    EG_EXPORT void egImGui_SetScrollHereY(EgImGuiContext context, float centerRatio)
    {
        ImGui::SetScrollHereY(centerRatio);
    }

    EG_EXPORT void egImGui_SetNextWindowScroll(EgImGuiContext context, EgImGuiVector2 value)
    {
        ImGui::SetNextWindowScroll(ToImVec2(value));
    }

    EG_EXPORT void egImGui_SetFocus(EgImGuiContext context, unsigned int id)
    {
        ImGui::SetFocusID(id, ImGui::GetCurrentWindow());
    }

    EG_EXPORT EgImGuiBool egImGui_IsWindowFocused(EgImGuiContext context)
    {
        return ToEgBool(ImGui::IsWindowFocused());
    }

    EG_EXPORT EgImGuiBool egImGui_IsItemFocused(EgImGuiContext context)
    {
        return ToEgBool(ImGui::IsItemFocused());
    }

    EG_EXPORT unsigned int egImGui_GetItemId(EgImGuiContext context)
    {
        return ImGui::GetItemID();
    }

    EG_EXPORT void egImGui_SetWindowFocus(EgImGuiContext context)
    {
        ImGui::SetWindowFocus();
    }

    EG_EXPORT void egImGui_SetKeyboardFocusHere(EgImGuiContext context)
    {
        ImGui::SetKeyboardFocusHere(0);
    }

    EG_EXPORT void egImGui_BringCurrentWindowToDisplayFront(EgImGuiContext context)
    {
        ImGui::BringWindowToDisplayFront(ImGui::GetCurrentWindow());
    }

    EG_EXPORT void egImGui_Dummy(EgImGuiContext context, EgImGuiVector2 size)
    {
        ImGui::Dummy(ToImVec2(size));
    }

    /* Style */

    EG_EXPORT EgImGuiVector2 egImGui_GetCellPadding(EgImGuiContext context)
    {
        ImGuiStyle& style = ImGui::GetStyle();
        return ToEgVector2(style.CellPadding);
    }

    EG_EXPORT EgImGuiVector2 egImGui_GetFramePadding(EgImGuiContext context)
    {
        ImGuiStyle& style = ImGui::GetStyle();
        return ToEgVector2(style.FramePadding);
    }

    EG_EXPORT EgImGuiVector2 egImGui_GetWindowPadding(EgImGuiContext context)
    {
        ImGuiStyle& style = ImGui::GetStyle();
        return ToEgVector2(style.WindowPadding);
    }

    EG_EXPORT EgImGuiVector2 egImGui_GetItemSpacing(EgImGuiContext context)
    {
        ImGuiStyle& style = ImGui::GetStyle();
        return ToEgVector2(style.ItemSpacing);
    }

    EG_EXPORT EgImGuiVector2 egImGui_GetItemInnerSpacing(EgImGuiContext context)
    {
        ImGuiStyle& style = ImGui::GetStyle();
        return ToEgVector2(style.ItemInnerSpacing);
    }

    EG_EXPORT void egImGui_SetCellPadding(EgImGuiContext context, EgImGuiVector2 cellPadding)
    {
        ImGuiStyle& style = ImGui::GetStyle();
        style.CellPadding = ToImVec2(cellPadding);
    }

    EG_EXPORT void egImGui_PushStyleColor_Text(EgImGuiContext context, EgImGuiVector4 color)
    {
        ImGui::PushStyleColor(ImGuiCol_Text, ToImVec4(color));
    }

    EG_EXPORT void egImGui_PushStyleColor_Button(EgImGuiContext context, EgImGuiVector4 color)
    {
        ImGui::PushStyleColor(ImGuiCol_Button, ToImVec4(color));
    }

    EG_EXPORT void egImGui_PushStyleColor_ButtonHovered(EgImGuiContext context, EgImGuiVector4 color)
    {
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ToImVec4(color));
    }

    EG_EXPORT void egImGui_PushStyleColor_ButtonActive(EgImGuiContext context, EgImGuiVector4 color)
    {
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ToImVec4(color));
    }

    EG_EXPORT void egImGui_PushStyleColor_WindowBackground(EgImGuiContext context, EgImGuiVector4 color)
    {
        ImGui::PushStyleColor(ImGuiCol_WindowBg, ToImVec4(color));
    }

    EG_EXPORT void egImGui_PushStyleColor_ChildBackground(EgImGuiContext context, EgImGuiVector4 color)
    {
        ImGui::PushStyleColor(ImGuiCol_ChildBg, ToImVec4(color));
    }

    EG_EXPORT void egImGui_PushStyleColor_PopupBackground(EgImGuiContext context, EgImGuiVector4 color)
    {
        ImGui::PushStyleColor(ImGuiCol_PopupBg, ToImVec4(color));
    }

    EG_EXPORT void egImGui_PushStyleColor_FrameBackground(EgImGuiContext context, EgImGuiVector4 color)
    {
        ImGui::PushStyleColor(ImGuiCol_FrameBg, ToImVec4(color));
    }

    EG_EXPORT void egImGui_PushStyleColor_FrameBackgroundHovered(EgImGuiContext context, EgImGuiVector4 color)
    {
        ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, ToImVec4(color));
    }

    EG_EXPORT void egImGui_PushStyleColor_FrameBackgroundActive(EgImGuiContext context, EgImGuiVector4 color)
    {
        ImGui::PushStyleColor(ImGuiCol_FrameBgActive, ToImVec4(color));
    }

    EG_EXPORT void egImGui_PushStyleColor_ModalWindowDimBackground(EgImGuiContext context, EgImGuiVector4 color)
    {
        ImGui::PushStyleColor(ImGuiCol_ModalWindowDimBg, ToImVec4(color));
    }

    EG_EXPORT void egImGui_PopStyleColor(EgImGuiContext context)
    {
        ImGui::PopStyleColor();
    }

    EG_EXPORT EgImGuiVector2 egImGui_GetStyleVar_WindowPadding(EgImGuiContext context)
    {
        auto style = ImGui::GetStyle();
        auto info = ImGui::GetStyleVarInfo(ImGuiStyleVar_WindowPadding);
        auto value = (ImVec2*)info->GetVarPtr(&style);
        return ToEgVector2(*value);
    }

    EG_EXPORT void egImGui_PushStyleVar_WindowPadding(EgImGuiContext context, EgImGuiVector2 value)
    {
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ToImVec2(value));
    }

    EG_EXPORT void egImGui_PopStyleVar(EgImGuiContext context)
    {
        ImGui::PopStyleVar();
    }

    EG_EXPORT EgImGuiVector2 egImGui_GetStyleVar_WindowBorderSize(EgImGuiContext context)
    {
        auto style = ImGui::GetStyle();
        auto info = ImGui::GetStyleVarInfo(ImGuiStyleVar_WindowBorderSize);
        auto value = (ImVec2*)info->GetVarPtr(&style);
        return ToEgVector2(*value);
    }

    EG_EXPORT void egImGui_PushStyleVar_WindowBorderSize(EgImGuiContext context, EgImGuiVector2 value)
    {
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, ToImVec2(value));
    }
}

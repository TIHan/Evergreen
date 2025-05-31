import subprocess
import os
import datetime
import winreg

# Utility
def absolute_path(path):
    return os.path.abspath(path)

def get_current_working_directory():
    return os.getcwd()

def now():
    return datetime.datetime.now()

def run(args, working_directory = None):
    args = args.replace('\n', '')
    print(args)
    start_time = now()
    exit_code = subprocess.run(args, shell = True, cwd = working_directory).returncode
    if exit_code != 0:
        exit(1)
    return now() - start_time

def envUser(name):
    os.environ[name]

# Windows-only
def envSys(name):
    reg_path = r'SYSTEM\CurrentControlSet\Control\Session Manager\Environment'
    reg_key = winreg.OpenKey(winreg.HKEY_LOCAL_MACHINE, reg_path)
    return winreg.QueryValueEx(reg_key, name)[0]

vulkan_sdk_path = envSys("VULKAN_SDK")
vulkan_sdk_include_path = os.path.join(vulkan_sdk_path, "Include")

run('dotnet tool install --global ClangSharpPInvokeGenerator --version 18.1.0.3')

run('msbuild src/native/libs/Evergreen.Physics/Evergreen.Physics.sln')
run('msbuild /p:Configuration=Release src/native/libs/Evergreen.Physics/Evergreen.Physics.sln')
run("""
ClangSharpPInvokeGenerator 
    -n Evergreen.Physics.Backend.Jolt.Interop 
    -l Evergreen.Physics.Native.dll 
    --file src/native/libs/Evergreen.Physics/egJolt.h 
    -o src/managed/Physics/Backend/Jolt/Interop/api 
    -c multi-file generate-file-scoped-namespaces generate-helper-types strip-enum-member-type-name exclude-enum-operators
    -e 
        EgJoltVector3 
        EgJoltVector4 
        EgJoltQuaternion 
        EgJoltMatrix4x4 
    -r 
        EgJoltVector3=System.Numerics.Vector3 
        EgJoltVector4=System.Numerics.Vector4 
        EgJoltQuaternion=System.Numerics.Quaternion 
        EgJoltMatrix4x4=System.Numerics.Matrix4x4
""")
run('dotnet build src/managed/Physics/Backend/Jolt/Interop/Evergreen.Physics.Backend.Jolt.Interop.csproj')
run('dotnet build -c Release src/managed/Physics/Backend/Jolt/Interop/Evergreen.Physics.Backend.Jolt.Interop.csproj')


# Graphics
run('msbuild src/native/libs/Evergreen.Graphics/Evergreen.Graphics.sln')
run('msbuild /p:Configuration=Release src/native/libs/Evergreen.Graphics/Evergreen.Graphics.sln')

run(f"""
ClangSharpPInvokeGenerator 
    -I src/native/external/SDL/include
    -n Evergreen.Graphics.Window.Backend.Interop
    -l Evergreen.Graphics.Native.dll 
    --file src/native/libs/Evergreen.Graphics/egWindow.h 
    -o src/managed/Graphics/Window/Backend/Interop
    -c multi-file generate-file-scoped-namespaces generate-helper-types strip-enum-member-type-name exclude-enum-operators
    -e
        EgWindowVector2
        EgWindowBool
    -r 
        EgWindowVector2=System.Numerics.Vector2
        EgWindowBool=System.Boolean
""")
run('dotnet build src/managed/Graphics/Window/Backend/Interop/Evergreen.Graphics.Window.Backend.Interop.csproj')
run('dotnet build -c Release src/managed/Graphics/Window/Backend/Interop/Evergreen.Graphics.Window.Backend.Interop.csproj')

run(f"""
ClangSharpPInvokeGenerator 
    -I "{vulkan_sdk_include_path}"
    -I src/native/external/imgui
    -n Evergreen.Graphics.UI.Backend.ImGui.Interop 
    -l Evergreen.Graphics.Native.dll 
    --file src/native/libs/Evergreen.Graphics/egImGui.h
    -o src/managed/Graphics/UI/Backend/ImGui/Interop 
    -c multi-file generate-file-scoped-namespaces generate-helper-types strip-enum-member-type-name exclude-enum-operators
    -e
        EgImGuiVector2
        EgImGuiVector4
        EgImGuiBool
    -r 
        VkQueue=TerraFX.Interop.Vulkan.VkQueue 
        VkDevice=TerraFX.Interop.Vulkan.VkDevice 
        VkRenderPass=TerraFX.Interop.Vulkan.VkRenderPass 
        VkPhysicalDevice=TerraFX.Interop.Vulkan.VkPhysicalDevice 
        VkInstance=TerraFX.Interop.Vulkan.VkInstance
        VkDescriptorSet=TerraFX.Interop.Vulkan.VkDescriptorSet
        VkPipeline=TerraFX.Interop.Vulkan.VkPipeline
        VkImageView=TerraFX.Interop.Vulkan.VkImageView
        VkSampler=TerraFX.Interop.Vulkan.VkSampler
        VkImageLayout=TerraFX.Interop.Vulkan.VkImageLayout
        VkCommandPool=TerraFX.Interop.Vulkan.VkCommandPool
        VkCommandBuffer=TerraFX.Interop.Vulkan.VkCommandBuffer
        VkResult=TerraFX.Interop.Vulkan.VkResult
        VkDescriptorPool=TerraFX.Interop.Vulkan.VkDescriptorPool
        EgImGuiVector2=System.Numerics.Vector2
        EgImGuiVector4=System.Numerics.Vector4
        EgImGuiBool=System.Boolean
        EgWindow=Evergreen.Graphics.Window.Backend.Interop.EgWindow
        
        EgImGuiWindowFlags_NoNavInputs=NoNavInputs
        EgImGuiWindowFlags_NoNavFocus=NoNavFocus

        EgImGuiWindowFlags_NoTitleBar=NoTitleBar
        EgImGuiWindowFlags_NoResize=NoResize
        EgImGuiWindowFlags_NoScrollbar=NoScrollbar
        EgImGuiWindowFlags_NoCollapse=NoCollapse

        EgImGuiWindowFlags_NoMouseInputs=NoMouseInputs
""")
run('dotnet build src/managed/Graphics/UI/Backend/ImGui/Interop/Evergreen.Graphics.UI.Backend.ImGui.Interop.csproj')
run('dotnet build -c Release src/managed/Graphics/UI/Backend/ImGui/Interop/Evergreen.Graphics.UI.Backend.ImGui.Interop.csproj')

run(f"""
ClangSharpPInvokeGenerator 
    -n Evergreen.Graphics.Asset.Backend.Interop
    -l Evergreen.Graphics.Native.dll 
    --file src/native/libs/Evergreen.Graphics/egAsset.h 
    -o src/managed/Graphics/Asset/Backend/Interop
    -c multi-file generate-file-scoped-namespaces generate-helper-types strip-enum-member-type-name exclude-enum-operators
    -e
        EgAssetVector2
        EgAssetVector3
        EgAssetVector4
        EgAssetBool
    -r 
        EgAssetVector2=System.Numerics.Vector2
        EgAssetVector3=System.Numerics.Vector3
        EgAssetVector4=System.Numerics.Vector4
        EgAssetBool=System.Boolean
""")
run('dotnet build src/managed/Graphics/Asset/Backend/Interop/Evergreen.Graphics.Asset.Backend.Interop.csproj')
run('dotnet build -c Release src/managed/Graphics/Asset/Backend/Interop/Evergreen.Graphics.Asset.Backend.Interop.csproj')

run(f"""
ClangSharpPInvokeGenerator 
    -n Evergreen.Graphics.Shader.Backend.Interop
    -l Evergreen.Graphics.Native.dll 
    --file src/native/libs/Evergreen.Graphics/egShader.h 
    -o src/managed/Graphics/Shader/Backend/Interop
    -c multi-file generate-file-scoped-namespaces generate-helper-types strip-enum-member-type-name exclude-enum-operators
    -e
        EgShaderBool
    -r 
        EgShaderBool=System.Boolean
""")
run('dotnet build src/managed/Graphics/Shader/Backend/Interop/Evergreen.Graphics.Shader.Backend.Interop.csproj')
run('dotnet build -c Release src/managed/Graphics/Shader/Backend/Interop/Evergreen.Graphics.Shader.Backend.Interop.csproj')
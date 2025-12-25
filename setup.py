import subprocess
import os
import datetime
import shutil

# Utility
def absolute_path(path):
    return os.path.abspath(path)

def get_current_working_directory():
    return os.getcwd()

def now():
    return datetime.datetime.now()

def run(args, working_directory = None):
    start_time = now()
    exit_code = subprocess.run(args, shell = True, cwd = working_directory).returncode
    if exit_code != 0:
        exit(1)
    return now() - start_time

dashes = '----------------------------------------------------------------------'

def print_setup_started(title):
    print(dashes)
    print(title + ' - Setup Started')
    print(dashes)

def print_setup_finished(title, delta_time):
    print(dashes)
    print(title + ' - Setup Finished - Elapsed:', delta_time)
    print(dashes)

# Setup paths
root_directory = get_current_working_directory()
jolt_build_directory = absolute_path('src/native/external/JoltPhysics/Build/')
jolt_vs_directory = absolute_path('src/native/external/JoltPhysics/Build/VS2026_CL/')
vma_directory = absolute_path('src/native/external/VulkanMemoryAllocator/')
sdl_directory = absolute_path('src/native/external/SDL/')
sdl_vs_directory = absolute_path('src/native/external/SDL/VisualC/')
assimp_directory = absolute_path('src/native/external/assimp/')
glslang_directory = absolute_path('src/native/external/glslang/')
glslang_build_directory = absolute_path('src/native/external/glslang/build/')
freetype_directory = absolute_path('src/native/external/freetype/')
lunasvg_directory = absolute_path('src/native/external/lunasvg/')
lunasvg_build_directory = absolute_path('src/native/external/lunasvg/')

# Setup LunaSVG
title = 'LunaSVG'
print_setup_started(title)
delta_time = run('cmake -B build .', working_directory = lunasvg_directory)
delta_time += run('cmake --build build', working_directory = lunasvg_build_directory)
print_setup_finished(title, delta_time)

# Setup Freetype
title = 'Freetype'
print_setup_started(title)
delta_time = run('msbuild MSBuild.sln /p:Configuration=Debug', working_directory = freetype_directory)
delta_time += run('msbuild MSBuild.sln /p:Configuration=Release', working_directory = freetype_directory)
print_setup_finished(title, delta_time)

# Setup JoltPhysics
title = 'JoltPhysics'
print_setup_started(title)
delta_time = run('cmake_vs2026_cl.bat', working_directory = jolt_build_directory)
delta_time += run('msbuild JoltPhysics.slnx', working_directory = jolt_vs_directory)
delta_time += run('msbuild JoltPhysics.slnx /p:Configuration=Release', working_directory = jolt_vs_directory)
print_setup_finished(title, delta_time)

# Setup VulkanMemoryAllocator
title = 'VulkanMemoryAllocator'
print_setup_started(title)
delta_time = run('cmake -S .  -B build -D VMA_BUILD_SAMPLES=ON', working_directory = vma_directory)
delta_time += run('msbuild build\\VMA.sln', working_directory = vma_directory)
delta_time += run('msbuild build\\VMA.sln /p:Configuration=Release', working_directory = vma_directory)
print_setup_finished(title, delta_time)

# Setup SDL
title = 'SDL'
print_setup_started(title)
delta_time = run('msbuild SDL.sln /p:Platform=x64', working_directory = sdl_vs_directory)
delta_time += run('msbuild SDL.sln /p:Configuration=Release /p:Platform=x64', working_directory = sdl_vs_directory)
print_setup_finished(title, delta_time)

# Setup assimp
title = 'assimp'
print_setup_started(title)
delta_time = run('cmake CMakeLists.txt', working_directory = assimp_directory)
delta_time += run('msbuild assimp.sln', working_directory = assimp_directory)
delta_time += run('msbuild assimp.sln /p:Configuration=Release', working_directory = assimp_directory)
print_setup_finished(title, delta_time)

# Setup glslang
title = 'glslang'
print_setup_started(title)
delta_time = run('python update_glslang_sources.py', working_directory = glslang_directory)
delta_time += run('mkdir build', working_directory = glslang_directory)
delta_time += run('cmake ../', working_directory = glslang_build_directory)
delta_time += run('cmake --build . --config Debug', working_directory = glslang_build_directory)
delta_time += run('cmake --build . --config Release', working_directory = glslang_build_directory)
print_setup_finished(title, delta_time)

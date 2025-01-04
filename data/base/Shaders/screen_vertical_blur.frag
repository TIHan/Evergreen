#version 450
#extension GL_GOOGLE_include_directive : enable
#include "core.glsl"

layout(location = 0) out vec4 outColor;

layout(location = 0) in vec2 fragTexCoord;
layout(location = 1) in vec3 in_position_world;

layout(set = 1, binding = 0) uniform sampler2D texSampler;
layout(set = 3, binding = 0) uniform sampler2D depthSampler;
layout(set = 4, binding = 0) uniform sampler2D screenDepthSampler;

const int KernelSize = 5;

// Top
vec4 VerticalBlur(vec2 uv)
{
    int kernel = KernelSize;
    float pixelSize = 1.0 / (iResolution.y / 3); 
    
    vec4 accumulation = vec4(0);
    int count = 0;
    for (float i = kernel; i >= 0; i--)
    {
        vec4 value = texture(texSampler, uv + vec2(0, i * pixelSize));
        if (value.xyz == vec3(0))
        {
            value.a = 0;
        }

        accumulation += value;
        count++;  
    }

    vec4 pass1Color = accumulation / count;

    accumulation = vec4(0);
    count = 0;
    for (float i = 0; i >= -kernel; i--)
    {
        vec4 value = texture(texSampler, uv + vec2(0, i * pixelSize));
        if (value.xyz == vec3(0))
        {
            value.a = 0;
        }

        accumulation += value;
        count++;
    }

    vec4 pass2Color = accumulation / count;
    
    return max(pass1Color, pass2Color);
}

void main() 
{
    outColor = VerticalBlur(fragTexCoord);
}
#version 450
#extension GL_GOOGLE_include_directive : enable
#include "core.glsl"

layout(location = 0) out vec4 outColor;

layout(location = 0) in vec2 fragTexCoord;
layout(location = 1) in vec3 in_position_world;

layout(set = 1, binding = 0) uniform sampler2D texSampler;
layout(set = 3, binding = 0) uniform sampler2D maskSampler;
layout(set = 4, binding = 0) uniform sampler2D screenDepthSampler;

const int KernelSize = 5;

// Left
vec4 HorizontalBlur(vec2 uv)
{
    int kernel = KernelSize;
    float pixelSize = 1.0 / (iResolution.x / 3); 
    
    vec4 accumulation = vec4(0);
    int count = 0;
    for (float i = -kernel; i <= 0; i++)
    {
        vec4 value = texture(texSampler, uv + vec2(i * pixelSize, 0));
        if (value.xyz == vec3(0))
        {
            value.a = 0;
        }

        accumulation += value; //* (1 + (abs(sin(g.Time * 2))) * 0.25);
        count++;   
    }

    // Pass1
    vec4 pass1Color = accumulation / count;

    accumulation = vec4(0);
    count = 0;
    for (float i = 0; i <= kernel; i++)
    {
        vec4 value = texture(texSampler, uv + vec2(i * pixelSize, 0));
        if (value.xyz == vec3(0))
        {
            value.a = 0;
        }

        accumulation += value; //* (1 + (abs(sin(g.Time * 2))) * 0.25);
        count++;
    }

    vec4 pass2Color = accumulation / count;
    
    return max(pass1Color, pass2Color);
}

void main() 
{
    outColor = HorizontalBlur(fragTexCoord);
}
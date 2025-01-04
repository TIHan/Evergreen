#version 450
#extension GL_GOOGLE_include_directive : enable
#include "core.glsl"
#include "core_tex.frag.glsl"
#include "core_color.frag.glsl"

layout(set = 2, binding = 0) uniform sampler2D screenDepthSampler;
layout(set = 3, binding = 0) uniform sampler2D maskSampler;
layout(set = 4, binding = 0) uniform sampler2D maskBlurSampler;

struct OutlineUVs {
    vec2 center;
    vec2 right;
    vec2 left;
    vec2 top;
    vec2 topRight;
    vec2 topLeft;
    vec2 bottom;
    vec2 bottomRight;
    vec2 bottomLeft;
};

struct OutlineValues {
    float center;
    float right;
    float left;
    float top;
    float topRight;
    float topLeft;
    float bottom;
    float bottomRight;
    float bottomLeft;
};

struct OutlineDeltas {
    float right;
    float left;
    float top;
    float topRight;
    float topLeft;
    float bottom;
    float bottomRight;
    float bottomLeft;
};

#define EPSILON 0.00001
#define LINE_WEIGHT 1.0

OutlineUVs CalculateOutlineUVs(vec2 screenSize, float lineWeight, vec2 uv)
{
   // float lineTickness = LINE_WEIGHT; //* 200 * (1 - screenDepth);
    if (lineWeight < LINE_WEIGHT)
        lineWeight = LINE_WEIGHT;

    float dx = (1.0 / screenSize.x) * lineWeight;
    float dy = (1.0 / screenSize.y) * lineWeight;

    OutlineUVs result;

    result.center = uv;
    result.right = vec2(uv.x + dx, uv.y);
    result.left = vec2(uv.x - dx, uv.y);
    result.top = vec2(uv.x,      uv.y - dy);
    result.topRight = vec2(uv.x + dx, uv.y - dy);
    result.topLeft = vec2(uv.x - dx, uv.y - dy);
    result.bottom = vec2(uv.x,      uv.y + dy);
    result.bottomRight = vec2(uv.x + dx, uv.y + dy);
    result.bottomLeft = vec2(uv.x - dx, uv.y + dy);

    return result;
}

OutlineValues CalculateOutlineValues(OutlineUVs outlineUVs, sampler2D samp)
{
    OutlineValues result;

    result.center = texture(samp, outlineUVs.center).r;
    result.right = texture(samp, outlineUVs.right).r;
    result.left = texture(samp, outlineUVs.left).r;
    result.top = texture(samp, outlineUVs.top).r;
    result.topRight = texture(samp, outlineUVs.topRight).r;
    result.topLeft = texture(samp, outlineUVs.topLeft).r;
    result.bottom = texture(samp, outlineUVs.bottom).r;
    result.bottomRight = texture(samp, outlineUVs.bottomRight).r;
    result.bottomLeft = texture(samp, outlineUVs.bottomLeft).r;

    return result;
}

OutlineDeltas CalculateOutlineDeltas(OutlineValues outlineValues)
{
    OutlineDeltas result;

    float center = outlineValues.center;

    result.right        = center - outlineValues.right;
    result.left         = center - outlineValues.left;
    result.top          = center - outlineValues.top;
    result.topRight     = center - outlineValues.topRight;
    result.topLeft      = center - outlineValues.topLeft;
    result.bottom       = center - outlineValues.bottom;
    result.bottomRight  = center - outlineValues.bottomRight;
    result.bottomLeft   = center - outlineValues.bottomLeft;

    return result;
}

float CalculateOutlineDelta(OutlineDeltas outlineDeltas)
{
    float delta = 0;

    if (outlineDeltas.left > outlineDeltas.right)
    {
        delta = max(delta, abs(outlineDeltas.left));
    }
    else
    {
        delta = max(delta, abs(outlineDeltas.right));
    }

    if (outlineDeltas.bottom > outlineDeltas.top)
    {
        delta = max(delta, abs(outlineDeltas.bottom));
    }
    else
    {
        delta = max(delta, abs(outlineDeltas.top));
    }

    delta = max(delta, abs(outlineDeltas.left));
    delta = max(delta, abs(outlineDeltas.right));
    delta = max(delta, abs(outlineDeltas.bottom));
    delta = max(delta, abs(outlineDeltas.top));
    delta = max(delta, abs(outlineDeltas.topRight));
    delta = max(delta, abs(outlineDeltas.topLeft));
    delta = max(delta, abs(outlineDeltas.bottomRight));
    delta = max(delta, abs(outlineDeltas.bottomLeft));

    return delta;
}

const int RobertsCrossX[4] = 
{
    1, 0,
    0, -1
};

const int RobertsCrossY[4] = 
{
    0, 1,
    -1, 0
};

float RobertsCross(OutlineValues samples)
{
    vec2 horizontal = vec2(0);
    vec2 vertical = vec2(0);

    horizontal += samples.topLeft * RobertsCrossX[0]; // top left (factor +1)
    horizontal += samples.bottomRight * RobertsCrossX[3]; // bottom right (factor -1)

    vertical += samples.bottomLeft * RobertsCrossY[2]; // bottom left (factor -1)
    vertical += samples.topRight * RobertsCrossY[1]; // top right (factor +1)

    return sqrt(dot(horizontal, horizontal) + dot(vertical, vertical));
}

const int SobelX[9] = 
{
    1, 0, -1,
    2, 0, -2,
    1, 0, -1
};

const int SobelY[9] = 
{
    1, 2, 1,
    0, 0, 0,
    -1, -2, -1
};

float Sobel(OutlineValues samples)
{
    vec2 horizontal = vec2(0);
    vec2 vertical = vec2(0);

    horizontal += samples.topLeft * SobelX[0]; // top left (factor +1)
    horizontal += samples.topRight * SobelX[2]; // top right (factor -1)
    horizontal += samples.left * SobelX[3]; // center left (factor +2)
    horizontal += samples.right * SobelX[5]; // center right (factor -2)
    horizontal += samples.bottomLeft * SobelX[6]; // bottom left (factor +1)
    horizontal += samples.bottomRight * SobelX[8]; // bottom right (factor -1)

    vertical += samples.topLeft * SobelY[0]; // top left (factor +1)
    vertical += samples.top * SobelY[1]; // top center (factor +2)
    vertical += samples.topRight * SobelY[2]; // top right (factor +1)
    vertical += samples.bottomLeft * SobelY[6]; // bottom left (factor -1)
    vertical += samples.bottom * SobelY[7]; // bottom center (factor -2)
    vertical += samples.bottomRight * SobelY[8]; // bottom right (factor -1)

    return sqrt(dot(horizontal, horizontal) + dot(vertical, vertical));
}

vec3 greyscale(vec3 color, float str) {
    float g = dot(color, vec3(0.299, 0.587, 0.114));
    return mix(color, vec3(g), str);
}

vec3 greyscale(vec3 color) {
    return greyscale(color, 1.0);
}

vec4 blend_with_depth_check(vec4 color, float depth, vec4 color_to_blend, float depth_to_blend, float blend_factor)
{
    if (depth > depth_to_blend)
    {
      //  color_to_blend *= blend_factor;
        return color_to_blend + color * (1 - color_to_blend.a);
    }
    return color;
}

void main() 
{
    float screenDepth = texture(screenDepthSampler, in_tex_coord).r;

    float lineWeight = LINE_WEIGHT * 1;
    OutlineUVs outlineUVs = CalculateOutlineUVs(iResolution, lineWeight, in_tex_coord);
    OutlineValues outlineValues = CalculateOutlineValues(outlineUVs, maskSampler);
    OutlineDeltas outlineDeltas = CalculateOutlineDeltas(outlineValues);

    float delta = Sobel(outlineValues);

    OutlineValues outlineDepthValues = CalculateOutlineValues(outlineUVs, maskSampler);
   OutlineValues outlineScreenDepthValues = CalculateOutlineValues(outlineUVs, screenDepthSampler);

    vec4 backgroundColor = vec4(0);

    if (iSuperSamplingAmount > 1)
    {
        int super_sampling_count = iSuperSamplingAmount / 2;

        for (int x = -super_sampling_count; x < super_sampling_count; x++)
        {
            for (int y = -super_sampling_count; y < super_sampling_count; y++)
            {
                backgroundColor += texture(in_tex_sampler, in_tex_coord + vec2(0.0001 * x, 0.0001 * y));
            }
        }
        backgroundColor /= (iSuperSamplingAmount * iSuperSamplingAmount);
    }
    else
    {
        backgroundColor = get_tex_color();
    }

    vec4 outlineColor = texture(maskSampler, in_tex_coord);

    // depth test
    
    // if ((delta > 0) && (outlineColor.xyz == vec3(0)) && (outlineDepthValues.top < screenDepth || outlineDepthValues.bottom < screenDepth || outlineDepthValues.left < screenDepth || outlineDepthValues.right < screenDepth || outlineDepthValues.topRight < screenDepth || outlineDepthValues.topLeft < screenDepth || outlineDepthValues.bottomRight < screenDepth || outlineDepthValues.bottomLeft < screenDepth))
    // {
    //     backgroundColor = vec4(1, 1, 0, 1) * iBackgroundAlpha;
    // }
    // else
    // {
    //     backgroundColor = backgroundColor * iBackgroundAlpha;
    // }
    

    // blur

    vec4 maskColor = texture(maskSampler, in_tex_coord);
    vec4 blurColor = texture(maskBlurSampler, in_tex_coord);
    if (maskColor.rgb != vec3(0))
    {
        backgroundColor = backgroundColor * iBackgroundAlpha;
    }
    else
    {
        // pre-multiplied alpha
        //  backgroundColor *= backgroundColor.a;
        blurColor *= blurColor.a;
        // alpha additive blending
        backgroundColor = (blurColor + backgroundColor * (1 - blurColor.a)) * iBackgroundAlpha;
    }

    out_color = backgroundColor;
}

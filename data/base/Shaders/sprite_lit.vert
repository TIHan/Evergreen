#version 450
#extension GL_GOOGLE_include_directive : enable
#include "core.glsl"

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec2 inTexCoord;

layout(location = 0) out vec2 fragTexCoord;
layout(location = 1) out vec3 out_position_world;
layout(location = 2) out vec3 out_Normal;
layout(location = 3) out flat int out_Positions_light_space_count;
layout(location = 4) out vec4 out_Positions_light_space[8];

layout(set = 2, binding = 0) readonly buffer _Instances
{
    Instance[] Instances;
};

layout(set = 3, binding = 0) readonly buffer lights_buf
{
   Light in_lights[8];
   int  in_light_count;
};

layout(set = 1, binding = 0) uniform sampler2D texSampler;

float get_directed_angle(vec3 v1, vec3 v2)
{
    return atan(v2.y, v2.x) - atan(v1.y, v1.x);
}

// Rotation matrix around the Y axis.
mat4 rotateY(float theta) {
    float c = cos(theta);
    float s = sin(theta);
    return mat4(
        vec4(c, 0, s, 0),
        vec4(0, 1, 0, 0),
        vec4(-s, 0, c, 0),
        vec4(0, 0, 0, 1)
    );
}

void main() 
{
    vec2 texSize = textureSize(texSampler, 0) * 0.025;
    mat4 scale = CreateScaleMatrix4x4(texSize.x, texSize.y, 1);
    mat4 model = Instances[gl_InstanceIndex].transform;

    vec3 dir = normalize(iViewInverse[3].xyz - model[3].xyz);
    vec3 modelDir = GetDirectionFromModelView(model);
    mat4 rot = rotateY(get_directed_angle(dir, modelDir));

    model = model * rot * scale;
    mat4 model_view = iView * model;
    mat4 billboard_model_view = CreateBillboardModelView(false, model, iView, texSize.x, texSize.y);

    vec4 position_world = ConvertLocalToWorldSpace(inPosition, model);
    vec4 billboard_position_view_space = ConvertLocalToWorldSpace(inPosition, billboard_model_view);

    gl_Position = iProjection * billboard_position_view_space;
    fragTexCoord = inTexCoord;  
    out_position_world = position_world.xyz;

    for (int i = 0; i < in_light_count; i++)
    {
        Light light = in_lights[i];
        //mat4 light_model_view = CreateBillboardModelView(false, model, in_light_views[i], texSize.x, texSize.y);
        //vec4 light_position_view_space = ConvertLocalToWorldSpace(inPosition, light_model_view);
        out_Positions_light_space[i] = light.projection * position_world;//light_position_view_space;
    }
    out_Positions_light_space_count = in_light_count;
    out_Normal = normalize(mat3(transpose(inverse(model))) * inNormal);
}
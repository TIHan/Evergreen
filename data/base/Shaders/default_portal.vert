#version 450
#extension GL_GOOGLE_include_directive : enable
#include "core.glsl"

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec2 inTexCoord;

layout(location = 0) out vec2 fragTexCoord;
layout(location = 1) out vec4 outPosition;
layout(location = 2) out vec4 outWorldPosition;

layout(set = 2, binding = 0) readonly buffer _Instances
{
    Instance[] Instances;
};

vec3 extractScale(mat4 matrix) {
  vec3 scale;
  scale.x = length(matrix[0].xyz);
  scale.y = length(matrix[1].xyz);
  scale.z = length(matrix[2].xyz);
  return scale;
}

void main() {
    mat4 model = Instances[gl_InstanceIndex].transform;
    vec3 scale = extractScale(model);

    vec4 position_world = ConvertLocalToWorldSpace(inPosition, model);

    vec4 position_screen = ConvertViewToClipSpace(ConvertWorldToViewSpace(position_world, iView), iProjection);

    gl_Position = position_screen;
    fragTexCoord = inTexCoord;
    outPosition = position_screen;
    outWorldPosition = position_world;
}
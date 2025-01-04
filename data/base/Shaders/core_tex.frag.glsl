layout(location = 0) in vec2 in_tex_coord;

layout(set = 1, binding = 0) uniform sampler2D in_tex_sampler;

vec4 get_tex_color()
{
    return texture(in_tex_sampler, in_tex_coord);
}
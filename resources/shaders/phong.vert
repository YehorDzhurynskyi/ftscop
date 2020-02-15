#version 460

in vec4 a_position;
layout (location = 1) in vec4 a_color_tint;

out vec4 v_color_tint;

void main(void)
{
    v_color_tint = a_color_tint;
    gl_Position = a_position;
}

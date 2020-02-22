#version 400

layout(location = 0) in vec4 a_position;
layout(location = 1) in vec4 a_color_tint;

out vec4 v_color_tint;

uniform mat4 u_mvp;

void main(void)
{
    v_color_tint = a_color_tint;
    gl_Position = u_mvp * a_position;
}

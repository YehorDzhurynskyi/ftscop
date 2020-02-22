#version 400

in vec4 a_position;
in vec4 a_color_tint;

uniform mat4 u_mvp;

out vec4 v_color_tint;

void main(void)
{
    v_color_tint = a_color_tint;
    gl_Position = u_mvp * a_position;
}

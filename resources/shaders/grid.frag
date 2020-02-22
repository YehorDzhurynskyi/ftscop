#version 400

uniform vec4 u_color_tint;

out vec4 fragcolor;

void main(void)
{
    fragcolor = u_color_tint;
}

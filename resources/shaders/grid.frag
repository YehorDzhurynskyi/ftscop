#version 460

uniform vec4 u_color_tint;

void main(void)
{
    gl_FragColor = u_color_tint;
}

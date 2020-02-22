#version 400

in vec4 v_color_tint;

out vec4 fragcolor;

void main(void)
{
    fragcolor = v_color_tint;
}

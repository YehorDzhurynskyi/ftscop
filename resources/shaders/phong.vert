attribute vec4 a_position;
attribute vec4 a_color_tint;

varying vec4 v_color_tint;

uniform mat4 u_view_projection;

void main(void)
{
    v_color_tint = a_color_tint;
    gl_Position = u_view_projection * a_position;
}

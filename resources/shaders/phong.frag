#version 400

flat in vec4	color_flat;
smooth in vec4	color_smooth;
in vec2			uv;

uniform bool	u_is_smooth_mode_enabled;
uniform int		u_palette;

uniform sampler2D	u_texture;

out vec4 fragcolor;

void main(void)
{
	if (u_palette == 3)
		fragcolor = texture(u_texture, uv);
	else if (u_is_smooth_mode_enabled)
		fragcolor = color_smooth;
	else
		fragcolor = color_flat;
}

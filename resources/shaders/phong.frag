#version 400

flat in vec4	color_flat;
smooth in vec4	color_smooth;
in vec2			uv;

uniform bool	u_is_smooth_mode_enabled;
uniform bool	u_is_grayscale_mode_enabled;
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

	if (u_is_grayscale_mode_enabled)
	{
		float gray = (0.2125 * fragcolor.x + 0.7154 * fragcolor.y + 0.0721 * fragcolor.z) / 3.0f;
		fragcolor = vec4(gray, gray, gray, 1.0f);
	}
}

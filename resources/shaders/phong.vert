#version 400

in vec4	a_position;
in vec4	a_color_tint;
in vec4	a_color;

uniform mat4	u_mvp;
uniform int		u_palette;

flat out vec4	color_flat;
smooth out vec4	color_smooth;
out vec2		uv;

# define PI 3.14159265359

vec2	cylinder_mapping()
{
	float	u;
	float	v;

	u = 0.5 + atan(a_position.z, a_position.x) / PI * 0.5;
	v = a_position.y / 10.0;
	return (vec2(u, v) * 15);
}

void main(void)
{
	if (u_palette == 0)
	{
		color_smooth = a_color;
	}
	else if (u_palette == 1)
	{
		vec3 position = a_position.xyz;
		color_smooth = vec4(position * 0.4f + 0.4f, 1.0f);
	}
	else if (u_palette == 2)
	{
		color_smooth = vec4(a_position.y * 0.4f + 0.4f, a_position.z * 0.1 + a_position.y * 0.4f + 0.1f, 0.2f, 1.0f);
	}

	color_smooth *= a_color_tint;
	color_flat = color_smooth;

	uv = cylinder_mapping();

	gl_Position = u_mvp * a_position;
}

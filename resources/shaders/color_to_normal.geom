#version 400

layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

out vec4 v_color_tint;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;

void main(void)
{
    mat4 mvp = u_projection * u_view * u_model;

    vec3 a = vec3(gl_in[0].gl_Position);
    vec3 b = vec3(gl_in[1].gl_Position);
    vec3 c = vec3(gl_in[2].gl_Position);
    vec3 n = abs(normalize(cross(a - b, c - b)));

    gl_Position = mvp * gl_in[0].gl_Position;
    v_color_tint = vec4(n, 1.0);
    EmitVertex();

    gl_Position = mvp * gl_in[1].gl_Position;
    v_color_tint = vec4(n, 1.0);
    EmitVertex();

    gl_Position = mvp * gl_in[2].gl_Position;
    v_color_tint = vec4(n, 1.0);
    EmitVertex();

    EndPrimitive();
}

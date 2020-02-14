#version 460

layout (points) in;
layout (line_strip, max_vertices = 255) out;

uniform mat4 u_mvp;
uniform int u_nsegments;
uniform float u_radius;

const float PI = 3.1415926;

void main()
{
    for (int i = 0; i <= u_nsegments; i++) {
        float ang = PI * 2.0 / float(u_nsegments) * i;

        vec4 offset = u_radius * vec4(cos(ang), -sin(ang), 0.0, 0.0);
        gl_Position =  u_mvp * (gl_in[0].gl_Position + offset);

        EmitVertex();
    }

    EndPrimitive();
}

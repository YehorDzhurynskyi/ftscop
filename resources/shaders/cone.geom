#version 460

layout (points) in;
layout (triangle_strip, max_vertices = 225) out;

uniform mat4 u_mvp;

uniform float u_height;
uniform float u_radius;
uniform int u_nsegments;

const float PI_DIV180 = 3.14159265358979323846 / 180.0;

void main()
{
    vec3 c = vec3(0.0, -u_height, 0.0);
    vec3 e0 = vec3(1.0, 0.0, 0.0);
    vec3 e1 = vec3(0.0, 0.0, 1.0);
    float angInc = 360.0 / u_nsegments * PI_DIV180;

    gl_Position = u_mvp * vec4(0.0, 0.0, 0.0, 1.0);
    EmitVertex();

    vec3 position1 = c + u_radius * e0;
    gl_Position = u_mvp * vec4(position1, 1.0);
    EmitVertex();


    for (int i = 1; i < u_nsegments; ++i)
    {
        vec3 position = c + u_radius * (e0 * cos(angInc * i) + e1 * sin(angInc * i));
        gl_Position = u_mvp * vec4(position, 1.0);
        EmitVertex();

        gl_Position = u_mvp * vec4(0.0, 0.0, 0.0, 1.0);
        EmitVertex();
    }

    vec3 position2 = c + u_radius * (e0 * cos(angInc * u_nsegments) + e1 * sin(angInc * u_nsegments));
    gl_Position = u_mvp * vec4(position2, 1.0);
    EmitVertex();

    EndPrimitive();
}

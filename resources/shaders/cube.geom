#version 400

layout (points) in;
layout (triangle_strip, max_vertices = 24) out;

uniform mat4 u_mvp;

uniform float u_size;

void emit_vertex(vec3 offset)
{
    gl_Position = u_mvp * vec4(offset * u_size, 1.0);
    EmitVertex();
}

void main()
{
    emit_vertex(vec3(-1.0, 1.0, 1.0));
    emit_vertex(vec3(-1.0, -1.0, 1.0));
    emit_vertex(vec3(1.0, 1.0, 1.0));
    emit_vertex(vec3(1.0, -1.0, 1.0));

    EndPrimitive();

    emit_vertex(vec3(1.0, 1.0, 1.0));
    emit_vertex(vec3(1.0, -1.0, 1.0));
    emit_vertex(vec3(1.0, 1.0, -1.0));
    emit_vertex(vec3(1.0, -1.0, -1.0));

    EndPrimitive();

    emit_vertex(vec3(1.0, 1.0, -1.0));
    emit_vertex(vec3(1.0, -1.0, -1.0));
    emit_vertex(vec3(-1.0, 1.0, -1.0));
    emit_vertex(vec3(-1.0, -1.0, -1.0));

    EndPrimitive();

    emit_vertex(vec3(-1.0, 1.0, -1.0));
    emit_vertex(vec3(-1.0, -1.0, -1.0));
    emit_vertex(vec3(-1.0, 1.0, 1.0));
    emit_vertex(vec3(-1.0, -1.0, 1.0));

    EndPrimitive();

    emit_vertex(vec3(1.0, 1.0, 1.0));
    emit_vertex(vec3(1.0, 1.0, -1.0));
    emit_vertex(vec3(-1.0, 1.0, 1.0));
    emit_vertex(vec3(-1.0, 1.0, -1.0));

    EndPrimitive();

    emit_vertex(vec3(-1.0, -1.0, 1.0));
    emit_vertex(vec3(-1.0, -1.0, -1.0));
    emit_vertex(vec3(1.0, -1.0, 1.0));
    emit_vertex(vec3(1.0, -1.0, -1.0));

    EndPrimitive();
}

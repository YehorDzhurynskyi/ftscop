#version 460

layout (points) in;
layout (line_strip, max_vertices = 225) out;

uniform mat4 u_mvp;

uniform float u_dimension;
uniform int u_nsteps;

void main()
{
    float half_dim = u_dimension / 2.0;

    {
        float y = -half_dim;
        float x = -half_dim;
        float dy = (half_dim - y) / (u_nsteps - 1);
        float dx = dy;
        for (int r = 0; r < u_nsteps; ++r)
        {
            gl_Position = u_mvp * vec4(x, y, 0.0, 1.0);
            EmitVertex();
            x += dx * (u_nsteps - 1);
            gl_Position = u_mvp * vec4(x, y, 0.0, 1.0);
            EmitVertex();
            dx = -dx;
            y += dy;
        }
        EndPrimitive();
    }
    {
        float y = -half_dim;
        float x = -half_dim;
        float dy = (half_dim - y) / (u_nsteps - 1);
        float dx = dy;
        for (int r = 0; r < u_nsteps; ++r)
        {
            gl_Position = u_mvp * vec4(x, y, 0.0, 1.0);
            EmitVertex();
            y += dy * (u_nsteps - 1);
            gl_Position = u_mvp * vec4(x, y, 0.0, 1.0);
            EmitVertex();
            dy = -dy;
            x += dx;
        }
        EndPrimitive();
    }
}

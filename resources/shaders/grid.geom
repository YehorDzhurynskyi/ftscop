#version 460

layout (points) in;
layout (line_strip, max_vertices = 225) out;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;

uniform float u_dimension;
uniform int u_nsteps;

void main()
{
    mat4 mvp = u_projection * u_view * u_model;
    float half_dim = u_dimension / 2.0;

    {
        float y = -half_dim;
        float x = -half_dim;
        float dy = (half_dim - y) / (u_nsteps - 1);
        float dx = dy;
        for (int r = 0; r < u_nsteps; ++r)
        {
            for (int c = 0; c < u_nsteps - 1; ++c)
            {
                gl_Position = mvp * vec4(x, y, 0.0, 1.0);
                EmitVertex();
                x += dx;
            }
            gl_Position = mvp * vec4(x, y, 0.0, 1.0);
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
            for (int c = 0; c < u_nsteps - 1; ++c)
            {
                gl_Position = mvp * vec4(x, y, 0.0, 1.0);
                EmitVertex();
                y += dy;
            }
            gl_Position = mvp * vec4(x, y, 0.0, 1.0);
            EmitVertex();
            dy = -dy;
            x += dx;
        }
        EndPrimitive();
    }
}

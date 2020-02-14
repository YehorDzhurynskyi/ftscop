#version 460

layout (points) in;
layout (line_strip, max_vertices = 256) out;

void main()
{
    {
        int steps = 5;

        float y = -1.0;
        float x = -1.0;
        float dy = (1.0 - y) / (steps - 1);
        float dx = dy;
        for (int r = 0; r < steps; ++r)
        {
            for (int c = 0; c < steps - 1; ++c)
            {
                gl_Position = vec4(x, y, 0.0, 1.0);
                EmitVertex();
                x += dx;
            }
            gl_Position = vec4(x, y, 0.0, 1.0);
            EmitVertex();
            dx = -dx;
            y += dy;
        }
        EndPrimitive();
    }
    {
        int steps = 5;

        float y = -1.0;
        float x = -1.0;
        float dy = (1.0 - y) / (steps - 1);
        float dx = dy;
        for (int r = 0; r < steps; ++r)
        {
            for (int c = 0; c < steps - 1; ++c)
            {
                gl_Position = vec4(x, y, 0.0, 1.0);
                EmitVertex();
                y += dy;
            }
            gl_Position = vec4(x, y, 0.0, 1.0);
            EmitVertex();
            dy = -dy;
            x += dx;
        }
        EndPrimitive();
    }
}

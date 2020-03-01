extern "C"
{
#include "objparser/objparser.h"
}

#include "gtest/gtest.h"

class ScopTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        ft_memset(&mesh, 0x0, sizeof(t_mesh));
        mesh.vertices = (t_vec4f*)malloc(sizeof(t_vec4f) * 10000);
        mesh.color_tints = (t_vec4f*)malloc(sizeof(t_vec4f) * 10000);
        mesh.faces = (int*)malloc(sizeof(int) * 3 * 10000);
    }

	void TearDown() override
	{
        free(mesh.faces);
        free(mesh.vertices);
        free(mesh.color_tints);
	}

protected:
    t_mesh mesh;
};

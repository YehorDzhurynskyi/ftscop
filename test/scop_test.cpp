#include "scop_test.h"

TEST_F(ScopTest, Empty)
{
    const t_byte buff[] = "";
    EXPECT_EQ(false, objparser_parse_mesh(buff, 0, &mesh));
    EXPECT_EQ(mesh.nvertices, 0);
    EXPECT_EQ(mesh.nfaces, 0);
}

TEST_F(ScopTest, SimpleEmptyLineOnEnd)
{
    const t_byte buff[] =
R"(# Simple Wavefront file
v 0.0 0.0 0.0
v 0.0 1.0 0.0
v 1.0 0.0 0.0
f 1 2 3
)";
    EXPECT_EQ(true, objparser_parse_mesh(buff, sizeof(buff) - 1, &mesh));
    EXPECT_EQ(mesh.nvertices, 3);
    EXPECT_EQ(mesh.nfaces, 1);
}

TEST_F(ScopTest, SimpleNoEmptyLineOnEnd)
{
    const t_byte buff[] =
R"(# Simple Wavefront file
v 0.0 0.0 0.0
v 0.0 1.0 0.0
v 1.0 0.0 0.0
f 1 2 3)";
    EXPECT_EQ(true, objparser_parse_mesh(buff, sizeof(buff) - 1, &mesh));
    EXPECT_EQ(mesh.nvertices, 3);
    EXPECT_EQ(mesh.nfaces, 1);
}

TEST_F(ScopTest, SimpleSpaceOnEnd)
{
    const t_byte buff[] =
R"(# Simple Wavefront file
v 0.0 0.0 0.0
v 0.0 1.0 0.0
v 1.0 0.0 0.0
f 1 2 3 )";
    EXPECT_EQ(true, objparser_parse_mesh(buff, sizeof(buff) - 1, &mesh));
    EXPECT_EQ(mesh.nvertices, 3);
    EXPECT_EQ(mesh.nfaces, 1);
}

TEST_F(ScopTest, SimpleWildcardOnEnd)
{
    const t_byte buff[] =
R"(# Simple Wavefront file
v 0.0 0.0 0.0
v 0.0 1.0 0.0
v 1.0 0.0 0.0
f 1 2 3 v)";
    EXPECT_EQ(false, objparser_parse_mesh(buff, sizeof(buff) - 1, &mesh));
    EXPECT_EQ(mesh.nvertices, 0);
    EXPECT_EQ(mesh.nfaces, 0);
}

TEST_F(ScopTest, RandomSpacesAndComments)
{
    const t_byte buff[] =
R"(# Simple Wavefront file
v 0.0   0.0     +0.0  

v 0.0 1.0 -0.0
#hello
v 1.0 0.0 0.0 #tut

    
        #rock n roll    

f 1 2 3#rokc)";
    EXPECT_EQ(true, objparser_parse_mesh(buff, sizeof(buff) - 1, &mesh));
    EXPECT_EQ(mesh.nvertices, 3);
    EXPECT_EQ(mesh.nfaces, 1);
}

TEST_F(ScopTest, IncompleteVertex)
{
    const t_byte buff[] =
R"(# Simple Wavefront file
v 0.0   0.0     0.0  

v 0.0 1.0# 0.0
#hello
v 1.0 0.0 0.0 #tut

f 1 2 3#rokc)";
    EXPECT_EQ(false, objparser_parse_mesh(buff, sizeof(buff) - 1, &mesh));
    EXPECT_EQ(mesh.nvertices, 0);
    EXPECT_EQ(mesh.nfaces, 0);
}

TEST_F(ScopTest, IncompleteVertexEOS)
{
    const t_byte buff[] =
        R"(# Simple Wavefront file
v 0.0   0.0     0.0  

v 0.0)";
    EXPECT_EQ(false, objparser_parse_mesh(buff, sizeof(buff) - 1, &mesh));
    EXPECT_EQ(mesh.nvertices, 0);
    EXPECT_EQ(mesh.nfaces, 0);
}

TEST_F(ScopTest, IncompleteVertexSpaceEOS)
{
    const t_byte buff[] =
        R"(# Simple Wavefront file
v 0.0   0.0     0.0  

v 0.0 )";
    EXPECT_EQ(false, objparser_parse_mesh(buff, sizeof(buff) - 1, &mesh));
    EXPECT_EQ(mesh.nvertices, 0);
    EXPECT_EQ(mesh.nfaces, 0);
}

TEST_F(ScopTest, IncompleteFace)
{
    const t_byte buff[] =
R"(# Simple Wavefront file
v 0.0   0.0     0.0  

v 0.0 1.0 0.0
#hello
v 1.0 0.0 0.0 #tut

f 1#rokc)";
    EXPECT_EQ(false, objparser_parse_mesh(buff, sizeof(buff) - 1, &mesh));
    EXPECT_EQ(mesh.nvertices, 0);
    EXPECT_EQ(mesh.nfaces, 0);
}

TEST_F(ScopTest, BrokenNumber)
{
    const t_byte buff[] =
R"(# Simple Wavefront file
v 0.0   0 .0     0.0  

v 0.0 1.0 0.0
#hello
v 1.0 0.0 0.0 #tut

f 1#rokc)";
    EXPECT_EQ(false, objparser_parse_mesh(buff, sizeof(buff) - 1, &mesh));
    EXPECT_EQ(mesh.nvertices, 0);
    EXPECT_EQ(mesh.nfaces, 0);
}

TEST_F(ScopTest, BrokenNegativeNumber)
{
    const t_byte buff[] =
        R"(# Simple Wavefront file
v 0.0   0.0     - 0.0  

v 0.0 1.0 0.0
#hello
v 1.0 0.0 0.0 #tut

f 1#rokc)";
    EXPECT_EQ(false, objparser_parse_mesh(buff, sizeof(buff) - 1, &mesh));
    EXPECT_EQ(mesh.nvertices, 0);
    EXPECT_EQ(mesh.nfaces, 0);
}

TEST_F(ScopTest, VertexOptionalW)
{
    const t_byte buff[] =
R"(# Simple Wavefront file
v 0.0 0.0 0.0 1.0
v 0.0 1.0 0.0 
v 1.0 0.0 0.0 0.5  
f 1 2 3 )";
    EXPECT_EQ(true, objparser_parse_mesh(buff, sizeof(buff) - 1, &mesh));
    EXPECT_EQ(mesh.nvertices, 3);
    EXPECT_EQ(mesh.nfaces, 1);
}

TEST_F(ScopTest, VertexExtraCoord)
{
    const t_byte buff[] =
R"(# Simple Wavefront file
v 0.0 0.0 0.0 1.0 0.0
v 0.0 1.0 0.0 
v 1.0 0.0 0.0 0.5  
f 1 2 3 )";
    EXPECT_EQ(false, objparser_parse_mesh(buff, sizeof(buff) - 1, &mesh));
    EXPECT_EQ(mesh.nvertices, 0);
    EXPECT_EQ(mesh.nfaces, 0);
}

TEST_F(ScopTest, Face4D)
{
    const t_byte buff[] =
R"(# Simple Wavefront file
v 0.0 0.0 0.0 1.0
v -1.0 1.0 0.0 
v 0.0 1.0 0.0 
v 1.0 0.0 0.0 0.5  
f 1 2 3 4)";
    EXPECT_EQ(true, objparser_parse_mesh(buff, sizeof(buff) - 1, &mesh));
    EXPECT_EQ(mesh.nvertices, 4);
    EXPECT_EQ(mesh.nfaces, 2);
}

TEST_F(ScopTest, Face5D)
{
    const t_byte buff[] =
R"(# Simple Wavefront file
v 0.0 0.0 0.0 1.0
v 0.0 1.0 0.0 
v 0.0 0.0 0.0 0.1
v 0.0 0.0 -2.0 1.0
v 1.0 0.0 0.0 0.5  
f 1 2 3 4 5)";
    EXPECT_EQ(true, objparser_parse_mesh(buff, sizeof(buff) - 1, &mesh));
    EXPECT_EQ(mesh.nvertices, 5);
    EXPECT_EQ(mesh.nfaces, 3);
}

TEST_F(ScopTest, Face8D)
{
    const t_byte buff[] =
R"(# Simple Wavefront file
v 0.0 0.0 0.0 1.0
v 0.0 1.0 0.0 
v 1.0 0.0 0.0 0.5  
v 0.0 0.0 0.0 1.0
v 0.0 1.0 0.0 
v 1.0 0.0 0.0 0.5  
v 0.0 0.0 0.0 1.0
v 0.0 1.0 0.0 
f 1 2 7 4 5 3 7 8)";
    EXPECT_EQ(true, objparser_parse_mesh(buff, sizeof(buff) - 1, &mesh));
    EXPECT_EQ(mesh.nvertices, 8);
    EXPECT_EQ(mesh.nfaces, 6);
}

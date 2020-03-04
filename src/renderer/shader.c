/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shader.h"
#include <stdio.h> // TODO: remove

static GLuint   shader_compile(GLenum shader_type, const char* code)
{
    GLuint  shader_id;
    GLint   result;
    GLchar  log[4096];

    shader_id = glCreateShader(shader_type);
    glShaderSource(shader_id, 1, &code, NULL);
    glCompileShader(shader_id);
    result = 0;
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        glGetShaderInfoLog(shader_id, sizeof(log), NULL, log);
        printf("%s", log); // TODO: remove
        glDeleteShader(shader_id);
        return (0);
    }
    return (shader_id);
}

static GLuint   build_program(GLuint program_id,
                              GLuint vert_id,
                              GLuint frag_id,
                              GLuint geom_id)
{
    GLint   result;
    GLchar  log[4096];

    result = 0;
    glLinkProgram(program_id);
    glGetProgramiv(program_id, GL_LINK_STATUS, &result);
    if (result == GL_FALSE)
    {
        glGetProgramInfoLog(program_id, sizeof(log), NULL, log);
        printf("%s", log); // TODO: remove
        glDeleteProgram(program_id);
        program_id = 0;
    }
    else
    {
        glDetachShader(program_id, vert_id);
        glDetachShader(program_id, frag_id);
        if (geom_id)
            glDetachShader(program_id, geom_id);
    }
    glDeleteShader(vert_id);
    glDeleteShader(frag_id);
    glDeleteShader(geom_id);
    return (program_id);
}

GLuint          shader_create_program(const char* vert_code, const char* frag_code, const char* geom_code)
{
    GLuint  program_id;
    GLuint  vert_id;
    GLuint  frag_id;
    GLuint  geom_id;

    program_id = glCreateProgram();
    vert_id = shader_compile(GL_VERTEX_SHADER, vert_code);
    frag_id = shader_compile(GL_FRAGMENT_SHADER, frag_code);
    geom_id = !geom_code ? 0 : shader_compile(GL_GEOMETRY_SHADER, geom_code);
    if (!program_id || !vert_id || !frag_id || (geom_code && !geom_id))
    {
        glDeleteShader(vert_id);
        glDeleteShader(frag_id);
        glDeleteShader(geom_id);
        glDeleteProgram(program_id);
        return (0);
    }
    glAttachShader(program_id, vert_id);
    glAttachShader(program_id, frag_id);
    if (geom_id)
        glAttachShader(program_id, geom_id);
    return (build_program(program_id, vert_id, frag_id, geom_id, geom_code));
}

GLuint          shader_load(const char* vert_filename, const char* frag_filename, const char* geom_filename)
{
    GLuint      program_id;
    const char* vert_code;
    const char* frag_code;
    const char* geom_code;
    size_t		filesize;

    vert_code = ft_read_file(vert_filename, &filesize);
    frag_code = ft_read_file(frag_filename, &filesize);
    geom_code = !geom_filename ? NULL : ft_read_file(geom_filename, &filesize);
    if (!vert_code || !frag_code || (geom_filename && !geom_code))
    {
        FT_SAFE_FREE(vert_code);
        FT_SAFE_FREE(frag_code);
        FT_SAFE_FREE(geom_code);
        return (0);
    }
    program_id = shader_create_program(vert_code, frag_code, geom_code);
    FT_SAFE_FREE(vert_code);
    FT_SAFE_FREE(frag_code);
    FT_SAFE_FREE(geom_code);
    return (program_id);
}

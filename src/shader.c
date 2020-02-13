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

static GLuint  shader_compile(GLenum shader_type, const char* code)
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
        glDeleteShader(shader_id);
        return (0);
    }

    return (shader_id);
}

GLuint  shader_create_program(const char* vert_code, const char* frag_code)
{
    GLuint  program_id;
    GLuint  vert_id;
    GLuint  frag_id;
    GLint   result;
    GLchar  log[4096];

    result = 0;
    program_id = glCreateProgram();
    vert_id = shader_compile(GL_VERTEX_SHADER, vert_code);
    frag_id = shader_compile(GL_FRAGMENT_SHADER, frag_code);
    if (!program_id || !vert_id || !frag_id)
    {
        glDeleteShader(vert_id);
        glDeleteShader(frag_id);
        glDeleteProgram(program_id);
        return (0);
    }
    glAttachShader(program_id, vert_id);
    glAttachShader(program_id, frag_id);
    glLinkProgram(program_id);
    glGetProgramiv(program_id, GL_LINK_STATUS, &result);
    if (result == GL_FALSE)
    {
        glGetShaderInfoLog(program_id, sizeof(log), NULL, log);
        glDeleteShader(vert_id);
        glDeleteShader(frag_id);
        glDeleteProgram(program_id);
        return (0);
    }
    glDetachShader(program_id, vert_id);
    glDetachShader(program_id, frag_id);
    glDeleteShader(vert_id);
    glDeleteShader(frag_id);

    return (program_id);
}

GLuint  shader_load(const char *vert_filename, const char *frag_filename)
{
    GLuint      program_id;
    const char  *vert_code;
    const char  *frag_code;

    vert_code = ft_read_file(vert_filename);
    frag_code = ft_read_file(frag_filename);
    if (!vert_code || !frag_code)
    {
        FT_SAFE_FREE(vert_code);
        FT_SAFE_FREE(frag_code);
        return (0);
    }
    program_id = shader_create_program(vert_code, frag_code);
    FT_SAFE_FREE(vert_code);
    FT_SAFE_FREE(frag_code);
    return (program_id);
}

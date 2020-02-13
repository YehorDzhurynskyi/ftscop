/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERER_H
# define RENDERER_H

# include "input/input.h"

typedef struct s_gfx_program    t_gfx_program;
struct  s_gfx_program
{
    union
    {
        struct
        {
            GLint   u_location_model;
            GLint   u_location_view;
            GLint   u_location_proj;

            GLint   a_location_position;
            GLint   a_location_color_tint;
        } phong;
    };
    GLuint  id;
};

typedef struct s_gfx_program_pool   t_gfx_program_pool;
struct  s_gfx_program_pool
{
    t_gfx_program   phong;
};

typedef struct s_gfx_ctx t_gfx_ctx;
struct  s_gfx_ctx
{
    t_gfx_program_pool  program_pool;
    t_mat4f             view;
    t_mat4f             proj;
};

t_bool  renderer_init(t_gfx_ctx *ctx);
void    renderer_delete(t_gfx_ctx *ctx);

void    renderer_draw_scene(const t_gfx_ctx *ctx, const t_scene *scene);
void    renderer_draw_interactor(const t_gfx_ctx *ctx, const t_scene_interactor *interactor);

#endif

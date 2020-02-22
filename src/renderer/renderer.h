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
            GLint   u_location_mvp;

            GLint   a_location_position;
            GLint   a_location_color_tint;
        } phong;
        struct
        {
            GLint   u_location_mvp;

            GLint   a_location_position;
            GLint   a_location_color_tint;
        } noshading;
        struct
        {
            GLint   u_location_mvp;
            GLint   u_location_dimension;
            GLint   u_location_nsteps;
            GLint   u_location_color_tint;
        } grid;
        struct
        {
            GLint   u_location_mvp;
            GLint   u_location_nsegments;
            GLint   u_location_color_tint;
            GLint   u_location_radius;
        } circle;
        struct
        {
            GLint   u_location_mvp;
            GLint   u_location_height;
            GLint   u_location_radius;
            GLint   u_location_nsegments;
            GLint   u_location_color_tint;
        } cone;
        struct
        {
            GLint   u_location_mvp;
            GLint   u_location_size;
            GLint   u_location_color_tint;
        } cube;
    };
    GLuint  id;
};

typedef struct s_gfx_program_pool   t_gfx_program_pool;
struct  s_gfx_program_pool
{
    t_gfx_program   phong;
    t_gfx_program   noshading;
    t_gfx_program   grid;
    t_gfx_program   circle;
    t_gfx_program   cone;
    t_gfx_program   cube;
};

typedef struct s_gfx_ctx    t_gfx_ctx;
struct  s_gfx_ctx
{
    t_gfx_program_pool  pool;
    GLuint              vao_null;
};
extern t_gfx_ctx    g_gfx_ctx;

t_bool  renderer_init(t_gfx_ctx* ctx);
void    renderer_delete(t_gfx_ctx* ctx);

t_bool  renderer_init_gfx_mesh(t_mesh *mesh);
t_bool  renderer_init_gfx_interactor(t_scene_interactor *interactor);
void    renderer_delete_gfx_mesh(t_mesh *mesh);
void    renderer_delete_gfx_interactor(t_scene_interactor *interactor);

void    renderer_draw_scene(const t_scene *scene);
void    renderer_draw_interactor(const t_scene_interactor *interactor);
void    renderer_draw_controls_translation(const t_scene_interactor *interactor, const t_mat4f *vp);
void	renderer_draw_controls_rotation(const t_scene_interactor *interactor, const t_mat4f *vp);
void    renderer_draw_controls_scaling(const t_scene_interactor *interactor, const t_mat4f *vp);

void    renderer_draw_circle(const t_mat4f *mvp, const t_vec4f *color, const unsigned int nsegments, const float radius);
void    renderer_draw_cone(const t_mat4f *mvp, const t_vec4f *color, const unsigned int nsegments, const float radius, const float height);
void    renderer_draw_cube(const t_mat4f *mvp, const t_vec4f *color, const float size);
void    renderer_draw_actor_basis(const t_actor *actor, const t_mat4f *vp);

t_mat4f renderer_calculate_local_mvp(const t_actor* actor, const t_mat4f* vp, const t_vec3f* offset, const t_vec3f* rot);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "ft.h"
# include "mesh.h"

typedef struct s_texture    t_texture;

typedef struct s_camera t_camera;
struct s_camera
{
    t_vec3f position;
    t_mat4f orientation;
    float   far;
    float   near;
    float   ar;
    float   fov;
};

void        camera_look_at(t_camera *cam, const t_vec3f *pos, const t_vec3f *poi, const t_vec3f *up);
t_mat4f     camera_calculate_matrix_view(const t_camera *cam);
t_mat4f     camera_calculate_matrix_proj(const t_camera *cam);

typedef struct s_actor  t_actor;
struct  s_actor
{
    t_vec3f     position;
    t_mat4f     orientation;
    t_vec3f     scale;
    t_mesh      *mesh;
    t_material  material;
};

void    calculate_basis_from_rotation(const t_vec3f *rot, t_vec3f *i, t_vec3f *j, t_vec3f *k);
void    calculate_basis_from_orientation(const t_mat4f *orien, t_vec3f *i, t_vec3f *j, t_vec3f *k);
t_mat4f calculate_matrix_orientation_from_rotation(const t_vec3f *rot);
t_mat4f calculate_matrix_orientation_from_basis(const t_vec3f *i, const t_vec3f *j, const t_vec3f *k);
t_mat4f calculate_matrix_scale(const t_vec3f *scl);
t_mat4f calculate_matrix_translation(const t_vec3f *pos);

t_vec3f transform_translate(const t_mat4f *orien, const t_vec3f *dpos);
t_mat4f transform_rotate(const t_mat4f* orien, const t_vec3f *rot);
t_mat4f transform_rotate_x(const t_mat4f* orien, const float rotx);
t_mat4f transform_rotate_y(const t_mat4f* orien, const float roty);
t_mat4f transform_rotate_z(const t_mat4f* orien, const float rotz);

t_mat4f actor_calculate_matrix_model(const t_actor *actor);
t_vec3f actor_radius_get(const t_actor *actor);
float   actor_radius_max_get(const t_actor *actor);
void    actor_palette_set(t_actor* actor, const t_palette palette);
void    actor_init(t_actor* actor, const t_mesh* mesh, const t_texture* texture);
void    actor_delete(t_actor* actor);

typedef struct s_scene  t_scene;
struct  s_scene
{
    t_camera    camera;
    t_mesh      mesh;
    t_actor     actor;
};

t_bool  scene_init(t_scene* scene, const char* objfile);
void    scene_delete(t_scene *scene);
void    scene_camera_reset(t_scene* scene);

#endif

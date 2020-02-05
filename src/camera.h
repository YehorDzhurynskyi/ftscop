/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

# include "ft.h"

typedef struct s_camera t_camera;
struct s_camera
{
    t_vec3f position;
    t_vec3f look_at;
    t_vec3f up;
    float   far;
    float   near;
    float   ar;
    float   fov;
};

t_mat4f camera_calculate_view_matrix(const t_camera* cam);
t_mat4f camera_calculate_proj_matrix(const t_camera* cam);

#endif

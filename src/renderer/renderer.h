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

typedef struct s_gctx_actor    t_gctx_actor;
struct  s_gctx_actor
{
    uint32_t    program_id;
};

typedef struct s_gctx_interactor    t_gctx_interactor;
struct  s_gctx_interactor
{
    uint32_t    program_id;
};

void    renderer_draw_actor(const t_gctx_actor *ctx, const t_actor *actor);
void    renderer_draw_interactor(const t_gctx_interactor *ctx, const t_scene_interactor *interactor);

#endif

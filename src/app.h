/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef APP_H
# define APP_H

# include "ft.h"
# include "input/input.h"
# include <SDL.h>

# define WIN_SZ_X 800
# define WIN_SZ_Y 600

typedef struct s_app	t_app;
struct	s_app
{
	SDL_Window		*win;
	SDL_GLContext	*glctx;
	float			delta_time;
	t_bool			is_running;
};

t_bool	app_init(t_app *app);
void	app_delete(t_app *app);
void	app_loop(t_app *app, t_scene *scene, t_scene_interactor *interactor);
void	app_poll_events(t_app *app, t_scene_interactor *interactor);

#endif

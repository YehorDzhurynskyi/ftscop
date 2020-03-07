/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objparser.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJPARSER_H
# define OBJPARSER_H

# include "scene/scene.h"
# include <assert.h>

/*
** According to http://paulbourke.net/dataformats/obj/
*/

typedef struct s_objparser_ctx  t_objparser_ctx;
struct  s_objparser_ctx
{
	t_byte *current;
	t_byte *end;
	size_t  total_size;

	t_bool  invalid;
	t_mesh  *mesh;
};

t_bool	objparser_parse_mesh(const t_byte* buff, const size_t sz, t_mesh* out);

/*
** Common
*/
t_bool	objparser_eos(t_objparser_ctx *ctx);
t_bool	objparser_isvalid(t_objparser_ctx *ctx);

void	objparser_skip_ws(t_objparser_ctx *ctx);
void	objparser_skip_until_nl(t_objparser_ctx *ctx);
t_bool	objparser_skip_if_match(t_objparser_ctx *ctx, const char *str);
t_bool	objparser_skip_if_match_ex(t_objparser_ctx *ctx, const char *str, size_t len);

int		objparser_read_int(t_objparser_ctx *ctx);
float	objparser_read_float(t_objparser_ctx *ctx);
t_bool	objparser_next_is_float(t_objparser_ctx *ctx);

/*
** Vertex-data
*/
void	objparser_read_v(t_objparser_ctx *ctx);

/*
** Polygonal
*/
void	objparser_read_f(t_objparser_ctx *ctx);

#endif

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

# define OBJPARSER_READ(x) if (objparser_eos(&ctx) || objparser_skip_if_match(&ctx, #x)) { objparser_read_##x(&ctx); }
# define OBJPARSER_NOT_IMPLEMENTED(x) void objparser_read_##x(t_objparser_ctx *ctx) { objparser_skip_until_nl(ctx); }

typedef struct s_objparser_ctx  t_objparser_ctx;
struct  s_objparser_ctx
{
    t_byte *current;
    t_byte *end;
    size_t  total_size;

    t_bool  invalid;
    t_mesh  *mesh;
};

t_bool  objparser_parse_mesh(const t_byte* buff, const size_t sz, t_mesh* out);

/*
** Common
*/
t_bool  objparser_eos(t_objparser_ctx *ctx);
t_bool  objparser_isvalid(t_objparser_ctx *ctx);

void    objparser_skip_ws(t_objparser_ctx *ctx);
void    objparser_skip_until_nl(t_objparser_ctx *ctx);
t_bool  objparser_skip_if_match(t_objparser_ctx *ctx, const char *str);
t_bool  objparser_skip_if_match_ex(t_objparser_ctx *ctx, const char *str, size_t len);

int     objparser_read_int(t_objparser_ctx *ctx);
float   objparser_read_float(t_objparser_ctx *ctx);

/*
** Commands
*/
void    objparser_cmnd_call(t_objparser_ctx *ctx);

/*
** Grouping
*/
void    objparser_read_g(t_objparser_ctx *ctx);
void    objparser_read_s(t_objparser_ctx *ctx);
void    objparser_read_mg(t_objparser_ctx *ctx);
void    objparser_read_o(t_objparser_ctx *ctx);

/*
** Render attrs
*/
void    objparser_read_bevel(t_objparser_ctx *ctx);
void    objparser_read_c_interp(t_objparser_ctx *ctx);
void    objparser_read_d_interp(t_objparser_ctx *ctx);
void    objparser_read_lod(t_objparser_ctx *ctx);
void    objparser_read_usemtl(t_objparser_ctx *ctx);
void    objparser_read_mtllib(t_objparser_ctx *ctx);
void    objparser_read_shadow_obj(t_objparser_ctx *ctx);
void    objparser_read_trace_obj(t_objparser_ctx *ctx);
void    objparser_read_ctech(t_objparser_ctx *ctx);
void    objparser_read_stech(t_objparser_ctx *ctx);

/*
** Vertex-data
*/
void    objparser_read_v(t_objparser_ctx *ctx);
void    objparser_read_vt(t_objparser_ctx *ctx);
void    objparser_read_vn(t_objparser_ctx *ctx);

void    objparser_read_vp(t_objparser_ctx *ctx);
void    objparser_read_cstype(t_objparser_ctx *ctx);
void    objparser_read_deg(t_objparser_ctx *ctx);
void    objparser_read_bmat(t_objparser_ctx *ctx);
void    objparser_read_step(t_objparser_ctx *ctx);

/*
** Polygonal
*/
void    objparser_read_p(t_objparser_ctx *ctx);
void    objparser_read_l(t_objparser_ctx *ctx);
void    objparser_read_f(t_objparser_ctx *ctx);

/*
** Free-form
*/
void    objparser_read_curv(t_objparser_ctx *ctx);
void    objparser_read_curv2(t_objparser_ctx *ctx);
void    objparser_read_surf(t_objparser_ctx *ctx);

void    objparser_read_parm(t_objparser_ctx *ctx);
void    objparser_read_trim(t_objparser_ctx *ctx);
void    objparser_read_hole(t_objparser_ctx *ctx);
void    objparser_read_scrv(t_objparser_ctx *ctx);
void    objparser_read_sp(t_objparser_ctx *ctx);
void    objparser_read_end(t_objparser_ctx *ctx);
void    objparser_read_con(t_objparser_ctx *ctx);

#endif

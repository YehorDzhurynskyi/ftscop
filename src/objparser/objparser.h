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

# include "ft.h"

/*
** According to http://paulbourke.net/dataformats/obj/
*/

typedef struct s_material t_material;
struct s_material
{
    t_vec3f ambient;
    t_vec3f diffuse;
    t_vec3f transparency;
};

typedef struct s_mesh t_mesh;
struct s_mesh
{
    t_vec4f* vertices;
    t_vec4f* colors;
    int nvertices;
    int* faces3;
    int nfaces3;
    t_material material;
};

typedef struct s_objparser_ctx t_objparser_ctx;
struct s_objparser_ctx
{
    t_byte *current;
    t_byte *end;
    size_t  total_size;
    t_mesh  *mesh;
};

/*
** Common
*/
t_bool  objparser_is_valid(t_objparser_ctx *ctx);

void    objparser_skip_ws(t_objparser_ctx *ctx);
void    objparser_skip_until_nl(t_objparser_ctx *ctx);
t_bool  objparser_skip_if_match(t_objparser_ctx *ctx, const char *str, size_t len);

int     objparser_read_int(t_objparser_ctx *ctx);
float   objparser_read_float(t_objparser_ctx *ctx);

/*
** Grouping
*/
void    objparser_read_grp_g(t_objparser_ctx *ctx);
void    objparser_read_grp_s(t_objparser_ctx *ctx);
void    objparser_read_grp_mg(t_objparser_ctx *ctx);
void    objparser_read_grp_o(t_objparser_ctx *ctx);

/*
** Render attrs
*/
void    objparser_read_rnd_bevel(t_objparser_ctx *ctx);
void    objparser_read_rnd_c_interp(t_objparser_ctx *ctx);
void    objparser_read_rnd_d_interp(t_objparser_ctx *ctx);
void    objparser_read_rnd_lod(t_objparser_ctx *ctx);
void    objparser_read_rnd_usemtl(t_objparser_ctx *ctx);
void    objparser_read_rnd_mtllib(t_objparser_ctx *ctx);
void    objparser_read_rnd_shadow_obj(t_objparser_ctx *ctx);
void    objparser_read_rnd_trace_obj(t_objparser_ctx *ctx);
void    objparser_read_rnd_ctech(t_objparser_ctx *ctx);
void    objparser_read_rnd_stech(t_objparser_ctx *ctx);

/*
** Polygonal
*/
void    objparser_read_p(t_objparser_ctx *ctx);
void    objparser_read_l(t_objparser_ctx *ctx);
void    objparser_read_f(t_objparser_ctx *ctx);

void    objparser_read_vertex_v(t_objparser_ctx *ctx);
void    objparser_read_vertex_vt(t_objparser_ctx *ctx);
void    objparser_read_vertex_vn(t_objparser_ctx *ctx);

/*
** Free-form
*/
void    objparser_read_ff_curv(t_objparser_ctx *ctx);
void    objparser_read_ff_curv2(t_objparser_ctx *ctx);
void    objparser_read_ff_surf(t_objparser_ctx *ctx);

void    objparser_read_ff_vp(t_objparser_ctx *ctx);
void    objparser_read_ff_cstype(t_objparser_ctx *ctx);
void    objparser_read_ff_deg(t_objparser_ctx *ctx);
void    objparser_read_ff_bmat(t_objparser_ctx *ctx);
void    objparser_read_ff_step(t_objparser_ctx *ctx);

void    objparser_read_ff_parm(t_objparser_ctx *ctx);
void    objparser_read_ff_trim(t_objparser_ctx *ctx);
void    objparser_read_ff_hole(t_objparser_ctx *ctx);
void    objparser_read_ff_scrv(t_objparser_ctx *ctx);
void    objparser_read_ff_sp(t_objparser_ctx *ctx);
void    objparser_read_ff_end(t_objparser_ctx *ctx);
void    objparser_read_ff_con(t_objparser_ctx *ctx);

#endif

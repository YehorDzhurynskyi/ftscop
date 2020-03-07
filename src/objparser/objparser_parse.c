/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objparser_parse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objparser.h"

static const char *g_not_implemented[] = {
    "bevel",
    "c_interp",
    "d_interp",
    "lod",
    "usemtl",
    "mtllib",
    "shadow_obj",
    "trace_obj",
    "ctech",
    "stech",
    "curv",
    "curv2",
    "surf",
    "parm",
    "trim",
    "hole",
    "scrv",
    "sp",
    "end",
    "con",
    "cstype",
    "deg",
    "bmat",
    "step",
    "g",
    "mg",
    "o",
    "s",
    "vp",
    "vn",
    "vt",
    "p",
    "l"
};

static t_bool   objparser_not_implemented(t_objparser_ctx *ctx)
{
    int i;

    i = 0;
    while (i < sizeof(g_not_implemented) / sizeof(g_not_implemented[0]))
    {
        if (objparser_skip_if_match(ctx, g_not_implemented[i]))
        {
            ft_printf_fd(2, "[Scop][ObjParsing] unsupported option: %s", g_not_implemented[i]);
            return (TRUE);
        }
        ++i;
    }
    return (FALSE);
}

t_bool          objparser_parse_mesh(const t_byte *buff, const size_t sz, t_mesh *out)
{
    t_objparser_ctx ctx;

    ctx.current = (t_byte*)buff;
    ctx.end = (t_byte*)&buff[sz];
    ctx.total_size = sz;
    ctx.mesh = out;
    ctx.invalid = FALSE;
    while (!objparser_eos(&ctx))
    {
        objparser_skip_ws(&ctx);
        if (*ctx.current == '#')
            objparser_skip_until_nl(&ctx);
        else if (objparser_eos(&ctx) || objparser_skip_if_match(&ctx, "v"))
            objparser_read_v(&ctx);
        else if (objparser_eos(&ctx) || objparser_skip_if_match(&ctx, "f"))
            objparser_read_f(&ctx);
        else if (objparser_eos(&ctx) || objparser_not_implemented(&ctx))
            objparser_skip_until_nl(&ctx);
        else
        {
            ft_printf_fd(2, "[Scop][ObjParsing] unrecognized option: '%*.32s'", ctx.end - ctx.current, ctx.current);
            mesh_delete(out);
            return (FALSE);
        }
    }
    if (ctx.invalid || !out->nvertices || !out->nfaces)
    {
        mesh_delete(out);
        return (FALSE);
    }
    return (TRUE);
}

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

OBJPARSER_NOT_IMPLEMENTED(g)
OBJPARSER_NOT_IMPLEMENTED(o)
OBJPARSER_NOT_IMPLEMENTED(mg)
OBJPARSER_NOT_IMPLEMENTED(s)
OBJPARSER_NOT_IMPLEMENTED(lod)
OBJPARSER_NOT_IMPLEMENTED(bevel)
OBJPARSER_NOT_IMPLEMENTED(c_interp)
OBJPARSER_NOT_IMPLEMENTED(d_interp)
OBJPARSER_NOT_IMPLEMENTED(shadow_obj)
OBJPARSER_NOT_IMPLEMENTED(trace_obj)

OBJPARSER_NOT_IMPLEMENTED(usemtl)
OBJPARSER_NOT_IMPLEMENTED(mtllib)
OBJPARSER_NOT_IMPLEMENTED(ctech)
OBJPARSER_NOT_IMPLEMENTED(stech)
OBJPARSER_NOT_IMPLEMENTED(curv)
OBJPARSER_NOT_IMPLEMENTED(curv2)
OBJPARSER_NOT_IMPLEMENTED(surf)
OBJPARSER_NOT_IMPLEMENTED(parm)
OBJPARSER_NOT_IMPLEMENTED(trim)
OBJPARSER_NOT_IMPLEMENTED(hole)
OBJPARSER_NOT_IMPLEMENTED(scrv)
OBJPARSER_NOT_IMPLEMENTED(sp)
OBJPARSER_NOT_IMPLEMENTED(end)
OBJPARSER_NOT_IMPLEMENTED(con)
OBJPARSER_NOT_IMPLEMENTED(cstype)
OBJPARSER_NOT_IMPLEMENTED(deg)
OBJPARSER_NOT_IMPLEMENTED(bmat)
OBJPARSER_NOT_IMPLEMENTED(step)

t_bool objparser_parse(const t_byte *buff, const size_t sz, t_mesh *out)
{
    t_objparser_ctx ctx;

    ctx.current = buff;
    ctx.end = &buff[sz];
    ctx.total_size = sz;
    ctx.mesh = out;
    while (ctx.current < ctx.end)
    {
        objparser_skip_ws(&ctx);
        if (*ctx.current == '#')
        {
            objparser_skip_until_nl(&ctx);
        }
        else OBJPARSER_READ(bevel)
        else OBJPARSER_READ(c_interp)
        else OBJPARSER_READ(d_interp)
        else OBJPARSER_READ(lod)
        else OBJPARSER_READ(usemtl)
        else OBJPARSER_READ(mtllib)
        else OBJPARSER_READ(shadow_obj)
        else OBJPARSER_READ(trace_obj)
        else OBJPARSER_READ(ctech)
        else OBJPARSER_READ(stech)
        else OBJPARSER_READ(curv)
        else OBJPARSER_READ(curv2)
        else OBJPARSER_READ(surf)
        else OBJPARSER_READ(parm)
        else OBJPARSER_READ(trim)
        else OBJPARSER_READ(hole)
        else OBJPARSER_READ(scrv)
        else OBJPARSER_READ(sp)
        else OBJPARSER_READ(end)
        else OBJPARSER_READ(con)
        else OBJPARSER_READ(cstype)
        else OBJPARSER_READ(deg)
        else OBJPARSER_READ(bmat)
        else OBJPARSER_READ(step)
        else OBJPARSER_READ(g)
        else OBJPARSER_READ(mg)
        else OBJPARSER_READ(o)
        else OBJPARSER_READ(s)
        else OBJPARSER_READ(vp)
        else OBJPARSER_READ(vn)
        else OBJPARSER_READ(vt)
        else OBJPARSER_READ(v)
        else OBJPARSER_READ(p)
        else OBJPARSER_READ(l)
        else OBJPARSER_READ(f)
        else
        {
            assert(!"Unhandled case");
            // TODO: release mesh
            return (FALSE);
        }
    }
    return (TRUE);
}

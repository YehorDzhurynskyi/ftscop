/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objparser_vertexdata.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objparser.h"
#include <stdlib.h>

OBJPARSER_NOT_IMPLEMENTED(vp)
OBJPARSER_NOT_IMPLEMENTED(vt)
OBJPARSER_NOT_IMPLEMENTED(vn)

void objparser_read_v(t_objparser_ctx *ctx)
{
    ctx->mesh->vertices[ctx->mesh->nvertices].x = objparser_read_float(ctx);
    ctx->mesh->vertices[ctx->mesh->nvertices].y = objparser_read_float(ctx);
    ctx->mesh->vertices[ctx->mesh->nvertices].z = objparser_read_float(ctx);
#if 1
    // TODO: handle optional W coord
    ctx->mesh->vertices[ctx->mesh->nvertices].w = 1.0;
#else
    ctx->mesh->vertices[ctx->mesh->nvertices].w = objparser_read_float(ctx);
#endif
    // TODO: could be followed by a color in r, g, b [0.0 - 1.0] format
    ctx->mesh->colors[ctx->mesh->nvertices] = (t_vec4f) { rand() / (float)RAND_MAX, rand() / (float)RAND_MAX, rand() / (float)RAND_MAX, 1.0f };

    ctx->mesh->nvertices++;
}

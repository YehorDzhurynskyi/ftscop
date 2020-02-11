/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objparser_polygonal.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objparser.h"

OBJPARSER_NOT_IMPLEMENTED(p)
OBJPARSER_NOT_IMPLEMENTED(l)

void objparser_read_f(t_objparser_ctx *ctx)
{
    // TODO: test cases "f 4 3 1 {EOF}", "f 4 3 1{EOF}"
    int face[4];
    int index = 0;
    while (ctx->current < ctx->end && ft_isdigit(*ctx->current))
    {
        const int vertexid = objparser_read_int(ctx);
        assert(vertexid > 0); // TODO: handle negative values
        face[index++] = vertexid - 1;
    }

    assert(index == 3 || index == 4);
    if (index == 3)
    {
        ft_memcpy(ctx->mesh->faces3 + 3 * ctx->mesh->nfaces3++, face, sizeof(int) * 3);
    }
    else if (index == 4)
    {
        ft_memcpy(ctx->mesh->faces3 + 3 * ctx->mesh->nfaces3++, face, sizeof(int) * 3);
        int temp[] = { face[2], face[3], face[0] };
        ft_memcpy(ctx->mesh->faces3 + 3 * ctx->mesh->nfaces3++, temp, sizeof(int) * 3);
    }
    else
    {
        // NOTE: convert to triangles to handle > 4 faces
        assert(!"Unhandled case"); // TODO: handle
    }
}

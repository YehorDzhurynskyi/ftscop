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

static void form_triangle_fan(t_objparser_ctx* ctx, int *face, int count)
{
    int temp[3];
    int i;

    i = 0;
    while (i < count)
    {
        temp[0] = face[2 + i];
        temp[1] = face[3 + i];
        temp[2] = face[0];
        ft_memcpy(ctx->mesh->faces + 3 * ctx->mesh->nfaces++, temp, sizeof(int) * 3);
        ++i;
    }
}

void        objparser_read_f(t_objparser_ctx *ctx)
{
    assert(!objparser_eos(ctx));
    int face[256];
    int index;

    index = 0;
    while (ctx->current < ctx->end && ft_isdigit(*ctx->current))
    {
        face[index++] = objparser_read_int(ctx) - 1;
    }
    if (index < 3)
    {
        ctx->invalid = TRUE;
        return ;
    }
    if (index >= 3)
    {
        ft_memcpy(ctx->mesh->faces + 3 * ctx->mesh->nfaces++, face, sizeof(int) * 3);
        if (index > 3)
        {
            form_triangle_fan(ctx, face, index - 3);
        }
    }
}

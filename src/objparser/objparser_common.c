/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objparser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objparser.h"

t_bool  objparser_eos(t_objparser_ctx *ctx)
{
    return (ctx->current == ctx->end);
}

t_bool  objparser_isvalid(t_objparser_ctx *ctx)
{
    return (ctx->current <= ctx->end);
}

void    objparser_skip_ws(t_objparser_ctx *ctx)
{
    assert(objparser_isvalid(ctx));
    while (ctx->current < ctx->end && ft_isws(*ctx->current))
        ctx->current++;
}

void    objparser_skip_until_nl(t_objparser_ctx *ctx)
{
    assert(objparser_isvalid(ctx));
    while (ctx->current < ctx->end && *ctx->current != '\n')
        ctx->current++;
}

t_bool  objparser_skip_if_match(t_objparser_ctx *ctx, const char *str)
{
    return (objparser_skip_if_match_ex(ctx, str, ft_strlen(str)));
}

t_bool  objparser_skip_if_match_ex(t_objparser_ctx *ctx, const char *str, size_t len)
{
    if ( ctx->end - ctx->current < len)
    {
        return (FALSE);
    }

    if (0 != ft_strncmp((const char*)ctx->current, str, len) || !ft_isws(ctx->current[len]))
    {
        return (FALSE);
    }
    ctx->current += len;
    objparser_skip_ws(ctx);
    return (TRUE);
}

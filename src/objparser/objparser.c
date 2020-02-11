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

static t_bool objparser_is_valid(t_objparser_ctx *ctx)
{
    return ctx->current < ctx->end;
}

static void objparser_skip_ws(t_objparser_ctx *ctx)
{
    assert(objparser_is_valid(ctx));

    while (ctx->current < ctx->end && ft_isws(*ctx->current))
        ctx->current++;
}

static void objparser_skip_until_nl(t_objparser_ctx *ctx)
{
    assert(objparser_is_valid(ctx));
    while (ctx->current < ctx->end && *ctx->current != '\n')
        ctx->current++;
}

static t_bool objparser_skip_if_match(t_objparser_ctx *ctx, const char *str, size_t len)
{
    assert(objparser_is_valid(ctx));
    if (ctx->end - ctx->current < len)
    {
        return (FALSE);
    }

    if (0 != ft_strncmp(ctx->current, str, len))
    {
        return (FALSE);
    }

    ctx->current += len;
    objparser_skip_ws(ctx);

    return (TRUE);
}

static void skip_until_next_space(t_objparser_ctx *ctx)
{
    // TODO: reimplement method to return pointer right after number

    t_byte* closest;
    t_byte* next[4];
    size_t size;

    size = ctx->end - ctx->current;
    next[0] = ft_strnchr(ctx->current, ' ', size);
    next[1] = ft_strnchr(ctx->current, '\t', size);
    next[2] = ft_strnchr(ctx->current, '\n', size);
    next[3] = ft_strnchr(ctx->current, '\r', size);

    closest = next[0];
    for (int i = 1; i < 4; ++i)
    {
        if (!next[i])
        {
            continue;
        }

        if (!closest || closest > next[i])
        {
            closest = next[i];
        }
    }

    if (!closest && ctx->current + size == ctx->end)
    {
        // NOTE: eof
        ctx->current = ctx->end;
    }
    else
    {
        assert(closest);
        ctx->current = closest;
        assert(ctx->current < ctx->end);
    }
}

static int objparser_read_int(t_objparser_ctx *ctx)
{
    assert(objparser_is_valid(ctx));

    int num = ft_atoi(ctx->current);
    skip_until_next_space(ctx);
    objparser_skip_ws(ctx);

    return (num);
}

static float objparser_read_float(t_objparser_ctx *ctx)
{
    objparser_skip_ws(ctx);
    if (ctx->current >= ctx->end)
    {
        return (0.0);
    }

    float num = ft_atod(ctx->current);
    skip_until_next_space(ctx);

    return (num);
}

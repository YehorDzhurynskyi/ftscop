/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objparser_read_float.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objparser.h"

float objparser_read_float(t_objparser_ctx *ctx)
{
    assert(objparser_isvalid(ctx));
    if (objparser_eos(ctx))
        return (0.0f);

    double	nb;
    double	f;
    double	d;
    int		sign;

    sign = *ctx->current == '-' ? -1 : 1;
    nb = (float)objparser_read_int(ctx);
    if (objparser_eos(ctx))
        return (0.0f);
    if (*ctx->current != '.')
    {
        objparser_skip_ws(ctx);
        return (nb);
    }
    ctx->current++;
    f = 0.0;
    d = 10.0;
    while (*ctx->current >= '0' && *ctx->current <= '9')
    {
        f += (*ctx->current++ - '0') / d;
        d *= 10.0;
    }
    objparser_skip_ws(ctx);
    return (nb + (f * sign));
}

t_bool  objparser_next_is_float(t_objparser_ctx* ctx)
{
    t_objparser_ctx temp;

    temp = *ctx;
    objparser_read_float(&temp);
    return (!temp.invalid);
}

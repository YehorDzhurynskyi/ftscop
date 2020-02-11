/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objparser_read_int.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objparser.h"

int objparser_read_int(t_objparser_ctx *ctx)
{
    assert(objparser_isvalid(ctx));

    int     nb;
    int     sign;

    sign = 1;
    nb = 0;
    if (*ctx->current == '-')
    {
        sign = -1;
        ctx->current++;
    }
    else if (*ctx->current == '+')
        ctx->current++;
    while (*ctx->current >= '0' && *ctx->current <= '9')
        nb = nb * 10 + *ctx->current++ - '0';
    objparser_skip_ws(ctx);
    return (nb * sign);
}

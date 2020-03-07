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

static t_bool	is_power_of_two(size_t n)
{
	if (n == 0)
		return (FALSE);
	while (n != 1)
	{
		if (n % 2 != 0)
			return (FALSE);
		n = n / 2;
	}
	return (TRUE);
}

static void* ensure_capacity(void* arr, size_t size, size_t num)
{
	if (num == 0)
	{
		return (malloc(2 * size));
	}
	else if (num != 1 && is_power_of_two(num))
	{
		return (realloc(arr, 2 * size * num));
	}
	return (arr);
}

static void	form_triangle_fan(t_objparser_ctx* ctx, int *face, int count)
{
	int	temp[3];
	int	i;

	i = 0;
	while (i < count)
	{
		temp[0] = face[2 + i];
		temp[1] = face[3 + i];
		temp[2] = face[0];
		ctx->mesh->faces = ensure_capacity(ctx->mesh->faces, sizeof(int) * 3, ctx->mesh->nfaces);
		ft_memcpy(ctx->mesh->faces + 3 * ctx->mesh->nfaces++,
		temp, sizeof(int) * 3);
		++i;
	}
}

void		objparser_read_f(t_objparser_ctx *ctx)
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
		ft_printf_fd(2, "[Scop][ObjParsing] incomplete face!\n");
		ctx->invalid = TRUE;
		return ;
	}
	if (index >= 3)
	{
		ctx->mesh->faces = ensure_capacity(ctx->mesh->faces, sizeof(int) * 3, ctx->mesh->nfaces);
		ft_memcpy(ctx->mesh->faces + 3 * ctx->mesh->nfaces++,
		face, sizeof(int) * 3);
		if (index > 3)
		{
			form_triangle_fan(ctx, face, index - 3);
		}
	}
}

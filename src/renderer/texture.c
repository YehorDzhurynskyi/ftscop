/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "renderer/renderer.h"

static t_bool   parse_bmp_header(const t_byte *raw, t_texture* texture, uint32_t *offset)
{
    if (raw[0] != 0x42 || raw[1] != 0x4D)
        return (FALSE);
    texture->width = *(uint32_t*)(raw + 0x12);
    texture->height = *(uint32_t*)(raw + 0x16);
    texture->bpp = *(uint16_t*)(raw + 0x1C);
    texture->pitch = texture->width * (texture->bpp / 8);
    *offset = *(uint32_t*)(raw + 0x0A);
    return (TRUE);
}

static t_bool   parse_bmp_body(const t_byte *raw, t_texture* texture)
{
    size_t  size;

    size = texture->height * texture->pitch;
    texture->raw = (t_byte*)malloc(size);
    if (!texture->raw)
    {
        return (FALSE);
    }
    ft_memcpy(texture->raw, raw, size);
    return (TRUE);
}

t_bool          texture_load_bmp(const char *filename, t_texture *texture)
{
    t_byte      *raw;
    uint32_t    offset;
	size_t		filesize;
	t_bool		result;

    texture->raw = NULL;
    raw = (t_byte*)ft_read_file(filename, &filesize);
    if (!raw)
    {
        return (FALSE);
    }
	result = parse_bmp_header(raw, texture, &offset) && parse_bmp_body(&raw[offset], texture);
	free(raw);
    return (result);
}

void            texture_delete(t_texture* texture)
{
    FT_SAFE_FREE(texture->raw);
}

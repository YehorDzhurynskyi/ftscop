/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <fcntl.h>
#include <unistd.h>

#undef BUFF_SIZE
#define BUFF_SIZE	4096

static char	*myrealloc(char *oldptr, size_t oldsize, size_t newsize)
{
	char	*newptr;

	newptr = (char*)malloc(newsize);
	if (oldptr)
	{
		ft_memcpy(newptr, oldptr, oldsize);
		free(oldptr);
	}
	return (newptr);
}

char		*ft_read_file(const char *filename, size_t *size)
{
	char	buff[BUFF_SIZE + 1];
	int		fd;
	ssize_t	ret;
	char	*result;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	result = NULL;
	*size = 0;
	while ((ret = read(fd, buff, BUFF_SIZE)) > 0)
	{
		result = (char*)myrealloc(result, *size, *size + ret + 1);
		ft_memcpy(result + *size, buff, ret);
		*size += ret;
		result[*size] = '\0';
	}
	if (ret < 0)
	{
		free(result);
		close(fd);
		return (NULL);
	}
	close(fd);
	return (result);
}

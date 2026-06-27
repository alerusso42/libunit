/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alessandro.russo.frc@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/06 13:48:25 by alerusso          #+#    #+#             */
/*   Updated: 2026/06/28 00:20:42 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libunit.h"

#define BASE "0123456789"
#define BUFFER_SIZE 500L

void	ft_putnbr(int num)
{
	char	*base;

	base = BASE;
	if (num < 0)
	{
		num = -num;
		write(1, "-", 1);
	}
	if (num >= 10)
	{
		ft_putnbr(num / 10);
		ft_putnbr(num % 10);
	}
	else
		write(1, base + num, 1);
}

//if n is bigger than strlen, undefined behaviour
char	*ft_strndup(char *str, int n)
{
	char	*dup;

	if (!str)
		return (NULL);
	dup = malloc(n + 1);
	if (!dup)
		return (NULL);
	strncpy(dup, str, n);
	dup[n] = 0;
	return (dup);
}

char	*ft_readfile(int fd, int max_size)
{
	char	buffer[BUFFER_SIZE];
	char	*content;
	int		bytes;
	int		total;

	total = 0;
	content = NULL;
	bytes = read(fd, buffer, BUFFER_SIZE - 1);
	while (bytes > 0 && (!content || max_size < 0 || total < max_size))
	{
		buffer[bytes] = 0;
		total += bytes;
		if (!content)
			content = ft_strndup(buffer, bytes);
		else
		{
			content = realloc(content, total + 1);
			strncat(content, buffer, bytes);
		}
		content[total] = 0;
		if (max_size < 0 || total < max_size)
			bytes = read(fd, buffer, BUFFER_SIZE - 1);
	}
	return (content);
}

void	ft_close(int *fd)
{
	if (!fd)
		return ;
	if (*fd > 0)
		close(*fd);
	*fd = 0;
}

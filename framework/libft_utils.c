/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alessandro.russo.frc@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/06 13:48:25 by alerusso          #+#    #+#             */
/*   Updated: 2026/06/27 18:20:53 by alerusso         ###   ########.fr       */
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

char	*ft_readfile(int fd)
{
	char	buffer[BUFFER_SIZE];
	char	*content;
	int		bytes_read;
	int		bytes_total;

	if (fd <= 0 || BUFFER_SIZE <= 1)
		return (NULL);
	bytes_total = 0;
	content = NULL;
	bytes_read = read(fd, buffer, BUFFER_SIZE - 1);
	while (bytes_read > 0)
	{
		buffer[bytes_read] = 0;
		bytes_total += bytes_read;
		if (!content)
			content = ft_strndup(buffer, bytes_read);
		else
		{
			content = realloc(content, bytes_total);
			strncat(content, buffer, bytes_read);
		}
		content[bytes_total] = 0;
		bytes_read = read(fd, buffer, BUFFER_SIZE - 1);
	}
	return (content);
}

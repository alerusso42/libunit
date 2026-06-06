/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alessandro.russo.frc@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/06 13:48:25 by alerusso          #+#    #+#             */
/*   Updated: 2026/06/06 13:49:48 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libunit.h"

#define BASE "0123456789"

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

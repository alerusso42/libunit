/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_partial_num.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 17:22:02 by alerusso          #+#    #+#             */
/*   Updated: 2026/05/24 17:28:09 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tests.h"

int	ft_atoi_03_partial_num(void)
{
	int		n;
	char	*s;

	s = "+27eoacq; v4t 97c243rwj+-*/<iodvc sw;qap.//'\"\\w3y34ao012';p][db+>]";
	n = ft_atoi(s);
	ft_putnbr(n);
	return (-(n != 27));
}

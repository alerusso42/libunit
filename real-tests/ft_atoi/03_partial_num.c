/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_partial_num.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanni <tvanni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 17:22:02 by alerusso          #+#    #+#             */
/*   Updated: 2026/05/23 22:57:25 by tvanni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tests.h"
# include <signal.h>

int	ft_atoi_test_partial_num(void)
{
	char	*s;

	s = "+27eoacq; v4t 97c243rwj+-*/<iodvc sw;qap.//'\"\\w3y34ao012';p][db+>]";
	return (-(ft_atoi(s) != 27));
}

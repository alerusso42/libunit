/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_long_string.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanni <tvanni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 17:22:02 by alerusso          #+#    #+#             */
/*   Updated: 2026/05/23 23:04:38 by tvanni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tests.h"
# include <signal.h>

int	strlen_test_long(void)
{
	char	*s;

	s = "eoacq; v4t 97c243rwj+-*/<iodvc kasw;qap.//'\"\\w3y34ao012';p][db+>]";
	return (-(strlen(s) != 65));
}

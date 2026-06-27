/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_basic.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/14 19:21:12 by alerusso            #+#    #+#           */
/*   Updated: 2026/06/14 19:21:12 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tests.h"

int	module2_01_basic(void)
{
	char			module[LIBUNIT_BUFFER];
	char			name[LIBUNIT_BUFFER];
	t_libunit_child	data;
	int				counter;

	strcpy(module, "module2");
	strcpy(name, "basic");
	counter = 01;
	data = child_init(module, name, counter);
	child_redirect(&data, 1);
	child_redirect(&data, 2);
	if (gabibbo() != 0)
		return (-1);
	if (child_cmp(&data, LIBUNIT_FLAGS_ZERO, child_release(&data, 1)) == 1)
		return (-1);
	if (child_cmp(&data, LIBUNIT_FLAGS_EXIST, child_release(&data, 2)) == 1)
		return (-1);
	return (0);
}

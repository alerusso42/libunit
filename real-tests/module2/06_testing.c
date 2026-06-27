/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   06_testing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 18:57:10 by alerusso            #+#    #+#           */
/*   Updated: 2026/06/27 18:57:10 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tests.h"
#define OUTPUT_PATH "module2/06.output"

int	module2_06_testing(void)
{
	t_test_fds		data;

	data = child_init(OUTPUT_PATH);
	child_redirect(&data, 1);
	child_redirect(&data, 2);
	if (gabibbo() != 0)
		return (-1);
	if (child_cmp(&data, LIBUNIT_FLAGS_ZERO, 1) != 0)
		return (-1);
	if (child_cmp(&data, LIBUNIT_FLAGS_EXIST, 2) != 0)
		return (-1);
	child_cleanup(&data);
	return (0);
}

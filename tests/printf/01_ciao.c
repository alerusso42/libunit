/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_ciao.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alessandro.russo.frc@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 20:52:54 by alerusso          #+#    #+#             */
/*   Updated: 2026/06/27 23:28:53 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tests.h"
#define OUTPUT_PATH "printf/01.output"

int	printf_01_ciao(void)
{
	t_test_fds		data;

	data = child_init(OUTPUT_PATH);
	child_redirect(&data, 1);
	child_redirect(&data, 2);
	if (printf("ciao") != 4)
		return (-1);
	fflush(stdout);
	if (child_cmp(&data, LIBUNIT_FLAGS_ZERO, 1) != 0)
		return (-1);
	if (child_cmp(&data, LIBUNIT_FLAGS_EXIST, 2) != 0)
		return (-1);
	child_cleanup(&data);
	return (0);
}

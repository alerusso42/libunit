/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_null.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alessandro.russo.frc@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 20:52:54 by alerusso          #+#    #+#             */
/*   Updated: 2026/06/27 23:23:35 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tests.h"
#define OUTPUT_PATH "printf/03.output"

int	printf_03_null(void)
{
	t_test_fds	data;
	char		*null_ptr;

	data = child_init(OUTPUT_PATH);
	null_ptr = NULL;
	child_redirect(&data, 1);
	child_redirect(&data, 2);
	if (printf(null_ptr, 1) != -1)
		return (-1);
	if (child_cmp(&data, LIBUNIT_FLAGS_ZERO, 1) != 0)
		return (-1);
	if (child_cmp(&data, LIBUNIT_FLAGS_EXIST, 2) != 0)
		return (-1);
	child_cleanup(&data);
	return (0);
}

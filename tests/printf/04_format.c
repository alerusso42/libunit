/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_format.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alessandro.russo.frc@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 23:32:31 by alerusso          #+#    #+#             */
/*   Updated: 2026/06/27 23:51:35 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tests.h"
#define OUTPUT_PATH "printf/04.output"

int	printf_04_format(void)
{
	t_test_fds	data;
	char		*null_ptr;
	int			size;

	data = child_init(OUTPUT_PATH);
	null_ptr = NULL;
	child_redirect(&data, 1);
	child_redirect(&data, 2);
	size = printf("42|%*.*s|%+016d|% -10.3d|", 10, 3, null_ptr, INT_MIN, 42);
	fflush(stdout);
	if (size != 42)
		return (-1);
	if (child_cmp(&data, LIBUNIT_FLAGS_ZERO, 1) != 0)
		return (-1);
	if (child_cmp(&data, LIBUNIT_FLAGS_EXIST, 2) != 0)
		return (-1);
	child_cleanup(&data);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_launcher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alessandro.russo.frc@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 20:52:54 by alerusso          #+#    #+#             */
/*   Updated: 2026/06/27 23:41:31 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tests.h"

int	printf_launcher(void)
{
	t_test_list	list;

	list = (t_test_list){0};
	load_test(&list, "ciao", printf_01_ciao);
	load_test(&list, "ciao_ciao", printf_02_ciao_ciao);
	load_test(&list, "null", printf_03_null);
	load_test(&list, "format", printf_04_format);
	return (launch_tests(&list, "FT_PRINTF"));
}

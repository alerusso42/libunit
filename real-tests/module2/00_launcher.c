/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_launcher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 18:57:10 by alerusso            #+#    #+#           */
/*   Updated: 2026/06/27 18:57:10 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tests.h"

int	module2_launcher(void)
{
	t_test_list	list;

	list = (t_test_list){0};
	load_test(&list, "basic", module2_01_basic);
	load_test(&list, "a1", module2_02_a1);
	load_test(&list, "a2", module2_03_a2);
	load_test(&list, "a3", module2_04_a3);
	load_test(&list, "aaaa", module2_05_aaaa);
	load_test(&list, "testing", module2_06_testing);
	return (launch_tests(&list, "MODULE2"));
}

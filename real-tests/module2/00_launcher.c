/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_launcher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 23:48:22 by alerusso            #+#    #+#           */
/*   Updated: 2026/06/08 23:48:22 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tests.h"

int	module2_launcher(void)
{
	t_test_list	list;

	list = (t_test_list){0};
	load_test(&list, "basic", module2_01_basic);
	load_test(&list, "other", module2_02_other);
	load_test(&list, "null", module2_03_null);
	load_test(&list, "testing", module2_04_testing);
	return (launch_tests(&list, "MODULE2"));
}

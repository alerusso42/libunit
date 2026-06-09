/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_launcher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 02:13:54 by alerusso            #+#    #+#           */
/*   Updated: 2026/06/09 02:13:54 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tests.h"

int	module1_launcher(void)
{
	t_test_list	list;

	list = (t_test_list){0};
	load_test(&list, "basic", module1_01_basic);
	load_test(&list, "other", module1_02_other);
	load_test(&list, "null", module1_03_null);
	return (launch_tests(&list, "MODULE1"));
}

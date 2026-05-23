/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_launcher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanni <tvanni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 23:15:12 by tvanni            #+#    #+#             */
/*   Updated: 2026/05/23 23:22:54 by tvanni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tests.h"

int	strcpy_launcher(void)
{
	t_test_list	list;

	list = (t_test_list){0};
	load_test(&list, "basic_test", strcpy_test_basic);
	// load_test(&list, "null_test", strcpy_test_null);
	// load_test(&list, "partial_num_test", strcpy_test_partial_num);
	// load_test(&list, "negative_test", strcpy_test_negative);
	return (launch_tests(&list, "STRCPY"));
}

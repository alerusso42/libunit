/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_launcher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 17:22:23 by alerusso          #+#    #+#             */
/*   Updated: 2026/05/24 17:34:54 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tests.h"

int	atoi_launcher(void)
{
	t_test_list	list;

	list = (t_test_list){0};
	load_test(&list, "basic_test", atoi_test_basic);
	load_test(&list, "null_test", atoi_test_null);
	load_test(&list, "partial_num_test", atoi_test_partial_num);
	load_test(&list, "negative_test", atoi_test_negative);
	return (launch_tests(&list, "ATOI"));
}

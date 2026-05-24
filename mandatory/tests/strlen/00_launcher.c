/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_launcher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 17:22:23 by alerusso          #+#    #+#             */
/*   Updated: 2026/05/24 17:34:36 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tests.h"

int	strlen_launcher(void)
{
	t_test_list	list;

	list = (t_test_list){0};
	load_test(&list, "basic_test", strlen_test_basic);
	load_test(&list, "null_test", strlen_test_null);
	load_test(&list, "long_test", strlen_test_long);
	load_test(&list, "short_test", strlen_test_short);
	load_test(&list, "sigbus", strlen_test_sigbus);
	return (launch_tests(&list, "STRLEN"));
}

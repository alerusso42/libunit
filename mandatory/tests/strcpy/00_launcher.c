/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_launcher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 23:15:12 by tvanni            #+#    #+#             */
/*   Updated: 2026/05/24 13:18:02 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tests.h"

int	strcpy_launcher(void)
{
	t_test_list	list;

	list = (t_test_list){0};
	load_test(&list, "basic_test", strcpy_test_basic);
	return (launch_tests(&list, "STRCPY"));
}

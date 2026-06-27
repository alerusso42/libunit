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

int	ft_printf_launcher(void)
{
	t_test_list	list;

	list = (t_test_list){0};
	load_test(&list, "a", ft_printf_01_a);
	load_test(&list, "b", ft_printf_02_b);
	load_test(&list, "c", ft_printf_03_c);
	return (launch_tests(&list, "FT_PRINTF"));
}

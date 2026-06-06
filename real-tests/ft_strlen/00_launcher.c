/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_launcher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alessandro.russo.frc@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 17:22:23 by alerusso          #+#    #+#             */
/*   Updated: 2026/06/06 15:47:46 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tests.h"

int	ft_strlen_launcher(void)
{
	t_test_list	list;

	list = (t_test_list){0};
	load_test(&list, "basic_test", ft_strlen_test_basic);
	load_test(&list, "null_test", ft_strlen_test_null);
	load_test(&list, "long_test", ft_strlen_test_long);
	load_test(&list, "short_test", ft_strlen_test_short);
	return (launch_tests(&list, "FT_STRLEN"));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_launcher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 17:22:23 by alerusso          #+#    #+#             */
/*   Updated: 2026/05/24 12:53:33 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tests.h"

int	ft_atoi_launcher(void)
{
	t_test_list	list;

	list = (t_test_list){0};
	load_test(&list, "basic_test", ft_atoi_01_basic);
	load_test(&list, "null_test", ft_atoi_02_null);
	load_test(&list, "partial_num_test", ft_atoi_03_partial_num);
	load_test(&list, "negative_test", ft_atoi_04_negative);
	load_test(&list, "positive overflow", ft_atoi_05_overflow_pos);
	load_test(&list, "negative overflow", ft_atoi_06_overflow_neg);
	load_test(&list, "max int", ft_atoi_07_max_int);
	load_test(&list, "min int", ft_atoi_08_min_int);
	load_test(&list, "valid spaces", ft_atoi_09_valid_spaces);
	load_test(&list, "invalid spaces", ft_atoi_10_invalid_spaces);
	load_test(&list, "positive 1 digit", ft_atoi_11_1digit_pos);
	load_test(&list, "negative 1 digit", ft_atoi_12_1digit_neg);
	load_test(&list, "zero", ft_atoi_13_zero);
	load_test(&list, "positive 2 digit", ft_atoi_14_2digit_pos);
	load_test(&list, "negative 2 digit", ft_atoi_15_2digit_neg);
	load_test(&list, "positive 10 digit", ft_atoi_16_10digit_pos);
	load_test(&list, "negative 10 digit", ft_atoi_17_10digit_neg);
	return (launch_tests(&list, "FT_ATOI"));
}

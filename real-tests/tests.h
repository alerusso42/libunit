/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 17:24:48 by alerusso          #+#    #+#             */
/*   Updated: 2026/05/24 11:47:02 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTS_H
# define TESTS_H

#include "../framework/libunit.h"

//SECTION - ft_strlen
int	ft_strlen_launcher(void);
int	ft_strlen_test_basic(void);
int	ft_strlen_test_null(void);
int	ft_strlen_test_long(void);
int	ft_strlen_test_short(void);

//SECTION - ft_atoi
int	ft_atoi_launcher(void);
int	ft_atoi_01_basic(void);
int	ft_atoi_02_null(void);
int	ft_atoi_03_partial_num(void);
int	ft_atoi_04_negative(void);
int	ft_atoi_05_overflow_pos(void);
int	ft_atoi_06_overflow_neg(void);
int	ft_atoi_07_max_int(void);
int	ft_atoi_08_min_int(void);
int	ft_atoi_09_valid_spaces(void);
int	ft_atoi_10_invalid_spaces(void);
int	ft_atoi_11_1digit_pos(void);
int	ft_atoi_12_1digit_neg(void);
int	ft_atoi_13_zero(void);
int	ft_atoi_14_2digit_pos(void);
int	ft_atoi_15_2digit_neg(void);
int	ft_atoi_16_10digit_pos(void);
int	ft_atoi_17_10digit_neg(void);

#endif

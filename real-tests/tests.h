/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanni <tvanni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 17:24:48 by alerusso          #+#    #+#             */
/*   Updated: 2026/05/23 22:53:54 by tvanni           ###   ########.fr       */
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

//SECTION - ft_putnbr
int	ft_atoi_launcher(void);
int	ft_atoi_test_basic(void);
int	ft_atoi_test_null(void);
int	ft_atoi_test_partial_num(void);
int	ft_atoi_test_negative(void);

#endif

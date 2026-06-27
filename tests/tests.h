/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alessandro.russo.frc@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 17:24:48 by alerusso          #+#    #+#             */
/*   Updated: 2026/06/27 23:41:48 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTS_H
# define TESTS_H

# include "../framework/libunit.h"
# include <string.h>
# include <limits.h>

//SECTION - strlen
int	strlen_launcher(void);
int	strlen_test_basic(void);
int	strlen_test_null(void);
int	strlen_test_long(void);
int	strlen_test_short(void);
int	strlen_test_sigbus(void);

// SECTION - atoi
int	atoi_launcher(void);
int	atoi_test_basic(void);
int	atoi_test_null(void);
int	atoi_test_partial_num(void);
int	atoi_test_negative(void);

// SECTION - strcpy
int	strcpy_launcher(void);
int	strcpy_test_basic(void);

//SECTION - ft_printf
int	printf_launcher(void);
int	printf_01_ciao(void);
int	printf_02_ciao_ciao(void);
int	printf_03_null(void);
int	printf_04_format(void);

// SECTION - signals
int	signals_launcher(void);
int	sig_01_segv(void);
int	sig_02_bus(void);
int	sig_03_alrm(void);
int	sig_04_abrt(void);
int	sig_05_fpe(void);
int	sig_06_pipe(void);
int	sig_07_ill(void);

#endif
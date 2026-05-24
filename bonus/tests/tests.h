/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 17:24:48 by alerusso          #+#    #+#             */
/*   Updated: 2026/05/24 14:52:50 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTS_H
# define TESTS_H

# include "../framework/libunit.h"
# include <string.h>

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
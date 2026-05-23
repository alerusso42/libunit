/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanni <tvanni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 17:24:48 by alerusso          #+#    #+#             */
/*   Updated: 2026/05/23 23:24:23 by tvanni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTS_H
# define TESTS_H

#include "../framework/libunit.h"
#include <string.h>

//SECTION - strlen
int	strlen_launcher(void);
int	strlen_test_basic(void);
int	strlen_test_null(void);
int	strlen_test_long(void);
int	strlen_test_short(void);

// SECTION - atoi
int	atoi_launcher(void);
int	atoi_test_basic(void);
int	atoi_test_null(void);
int	atoi_test_partial_num(void);
int	atoi_test_negative(void);

// STRCPY - strcpy
int	strcpy_launcher(void);
int	strcpy_test_basic(void);

#endif

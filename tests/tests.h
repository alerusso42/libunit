/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 17:24:48 by alerusso          #+#    #+#             */
/*   Updated: 2026/05/23 19:46:36 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTS_H
# define TESTS_H

#include "../framework/libunit.h"

//SECTION - strlen
int	ft_strlen(char *s);
int	strlen_launcher(void);
int	strlen_test_basic(void);
int	strlen_test_null(void);

#endif 
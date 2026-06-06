/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_basic.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alessandro.russo.frc@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 23:16:29 by tvanni            #+#    #+#             */
/*   Updated: 2026/06/06 14:00:13 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tests.h"

int	strcpy_test_basic(void)
{
	char	*s1;
	char	s2[6];

	s1 = "hello";
	return (strcmp(strcpy(s2, s1), "hello"));
}

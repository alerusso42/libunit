/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alessandro.russo.frc@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 15:20:42 by alerusso          #+#    #+#             */
/*   Updated: 2026/06/06 13:52:53 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libunit.h"

void	error(t_test_list *list, char *log)
{
	cleanup(list);
	write(1, log, strlen(log));
	exit(1);
}

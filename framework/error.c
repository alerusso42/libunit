/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 15:20:42 by alerusso          #+#    #+#             */
/*   Updated: 2026/05/24 13:20:32 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libunit.h"

void	error(t_test_list *list, char *log)
{
	cleanup(list);
	write(1, log, ft_strlen(log));
	exit(1);
}

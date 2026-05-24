/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 22:26:59 by tvanni            #+#    #+#             */
/*   Updated: 2026/05/24 13:19:04 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

int	main(void)
{
	int	output;

	output = 0;
	output -= ft_strlen_launcher();
	output -= ft_atoi_launcher();
	return (-(output != 0));
}

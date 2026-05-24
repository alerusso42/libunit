/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 17:30:46 by alerusso          #+#    #+#             */
/*   Updated: 2026/05/24 14:11:53 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

int	main(void)
{
	int	output;

	output = 0;
	output -= strlen_launcher();
	output -= atoi_launcher();
	output -= strcpy_launcher();
	if (output == 0)
		write(1, "\033[1;32mTEST OK.\n\033[0m", 18);
	else
		write(1, "\033[1;31mTEST KO.\n\033[0m", 18);
	return (-(output != 0));
}

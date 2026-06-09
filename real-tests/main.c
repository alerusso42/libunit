/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 16:23:28 by alerusso            #+#    #+#           */
/*   Updated: 2026/06/09 16:23:28 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

int	main(void)
{
	int	output;

	output = 0;
	output -= module2_launcher();
	output -= module1_launcher();
	output -= ft_printf_launcher();
	if (output == 0)
		write(1, "\033[1;32mTEST OK.\n\033[0m", 18);
	else
		write(1, "\033[1;31mTEST KO.\n\033[0m", 18);
	return (-(output != 0));
}

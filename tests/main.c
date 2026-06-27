/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alessandro.russo.frc@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 17:30:46 by alerusso          #+#    #+#             */
/*   Updated: 2026/06/27 23:55:08 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

int	main(void)
{
	int	output;

	output = 0;
	write(1, "expected 3/5...\n", 16);
	output -= strlen_launcher();
	write(1, "expected 2/4...\n", 16);
	output -= atoi_launcher();
	write(1, "expected 1/1...\n", 16);
	output -= strcpy_launcher();
	write(1, "expected 4/4...\n", 16);
	output -= printf_launcher();
	write(1, "expected 0/7...\n", 16);
	output -= signals_launcher();
	write(1, "\033[1;33mTEST END.\n\033[0m", 20);
	return (-(output != 0));
}

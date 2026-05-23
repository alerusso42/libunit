/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanni <tvanni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 17:30:46 by alerusso          #+#    #+#             */
/*   Updated: 2026/05/23 23:24:35 by tvanni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

int	main()
{
	int	output;

	output = 0;
	output -= strlen_launcher();
	output -= atoi_launcher();
	output -= strcpy_launcher();
	return (-(output != 0));
}

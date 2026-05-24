/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 16:34:17 by alerusso          #+#    #+#             */
/*   Updated: 2026/05/24 18:09:43 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libunit.h"

//[test_function]: [test_name] : [status]
void	print_test(t_test_node *node, char *func_name)
{
	write(1, func_name, ft_strlen(func_name));
	write(1, ": ", 2);
	write(1, node->name, ft_strlen(node->name));
	write(1, " : ", 3);
	if (node->sig == 0)
	{
		if (node->status == 0)
			write(1, "\033[32m[OK]", 9);
		else
			write(1, "\033[31m[KO]", 9);
		write(1, "\033[0m\n", 5);
		return ;
	}
	if (node->sig == SIGSEGV)
		write(1, "\033[33m[SIGSEGV]", 14);
	else if (node->sig == SIGBUS)
		write(1, "\033[33m[SIGBUS]", 13);
	else
		write(1, "invalid signal!", 15);
	write(1, "\033[0m\n", 5);
}

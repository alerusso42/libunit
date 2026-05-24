/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 16:34:17 by alerusso          #+#    #+#             */
/*   Updated: 2026/05/24 15:02:37 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libunit.h"

void	print_signals(int sig);

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
	print_signals(node->sig);
	write(1, "\033[0m\n", 5);
}

void	print_signals(int sig)
{
	if (sig == SIGSEGV)
		write(1, "\033[33m[SIGSEGV]", 14);
	else if (sig == SIGBUS)
		write(1, "\033[33m[SIGBUS]", 13);
	else if (sig == SIGALRM)
		write(1, "\033[33mTIMEOUT!", 13);
	else if (sig == SIGABRT)
		write(1, "\033[33mABORTED!", 13);
	else if (sig == SIGFPE)
		write(1, "\033[33m[SIGFPE]", 13);
	else if (sig == SIGPIPE)
		write(1, "\033[33m[SIGPIPE]", 14);
	else if (sig == SIGILL)
		write(1, "\033[33m[SIGILL]", 13);
	else
		write(1, "invalid signal!", 15);
}

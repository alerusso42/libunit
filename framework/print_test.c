/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 16:34:17 by alerusso          #+#    #+#             */
/*   Updated: 2026/05/23 17:01:06 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libunit.h"

/*
        if (WIFEXITED(wstatus)
		WEXITSTATUS(wstatus));
       WIFSIGNALED(wstatus)) {
       WTERMSIG(wstatus));
*/

//[test_function]: [test_name] : [status]
void	print_test(t_test_node *node, char *func_name)
{
	write(1, func_name, ft_strlen(func_name));
	write(1, ": ", 2);
	write(1, node->name, ft_strlen(func_name));
	write(1, " : ", 3);
	if (node->sig == 0)
	{
		if (node->status == 0)
			write(1, "\033[32m[OK]\033[0m", 13);
		else
			write(1, "\033[31m[KO]\033[0m", 13);
		return ;
	}
	if (node->sig == SIGSEGV)
		write(1, "\033[33m[SIGSEGV]\033[0m", 18);	
	else if (node->sig == SIGBUS)
		write(1, "\033[33m[SIGBUS]\033[0m", 17);
	else
		write(1, "invalid signal!", 15);
}

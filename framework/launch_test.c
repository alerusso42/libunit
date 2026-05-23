/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 16:10:09 by alerusso          #+#    #+#             */
/*   Updated: 2026/05/23 18:09:59 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libunit.h"

int	launch_tests(t_test_list *list, char *func_name)
{
	t_test_node	*curr;
	__pid_t		pid;

	curr = list->first;
	while (curr)
	{
		pid = fork();
		if (pid == -1)
			error(list, "");
		else if (pid == 0)
		{
			list->status = curr->test_func();
			return (cleanup(list), exit(list->status), -1);
		}
		wait(&curr->status);
		if (WIFSIGNALED(curr->status))
			curr->sig = WTERMSIG(curr->status);
		if (WIFEXITED(curr->status))
			curr->status = WEXITSTATUS(curr->status);
		list->status += curr->status;
		print_test(curr, func_name);
		curr = curr->next;
	}
	return (-(list->status != 0));
}


/*
        if (WIFEXITED(wstatus)
		WEXITSTATUS(wstatus));
       WIFSIGNALED(wstatus)) {
       WTERMSIG(wstatus));
*/

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanni <tvanni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 16:10:09 by alerusso          #+#    #+#             */
/*   Updated: 2026/05/23 22:00:37 by tvanni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libunit.h"
#include <stdio.h>

int	fork_test(t_test_list *list, t_test_node *curr)
{
	int	pid;
	int	status;

	pid = fork();
	status = 0;
	if (pid == -1)
		error(list, "");
	else if (pid == 0)
	{
		status = curr->test_func();
		return (cleanup(list), exit(status), -1);
	}
	wait(&curr->status);
	return (0);
}

void	print_result(int succeded, int total)
{
	printf("succeded: %d\n", succeded);
	write(1, "\ntests succeded: ", 17);
	ft_putnbr(succeded);
	write(1, "/", 1);
	ft_putnbr(total);
	write(1, "\n", 1);
}

int	launch_tests(t_test_list *list, char *func_name)
{
	t_test_node	*curr;
	int			i;
	int			failed;

	i = 0;
	failed = 0;
	curr = list->first;
	while (curr)
	{
		i++;
		if (fork_test(list, curr) != 0)
			return (-1);
		if (WIFSIGNALED(curr->status))
			curr->sig = WTERMSIG(curr->status);
		if (WIFEXITED(curr->status))
			curr->status = WEXITSTATUS(curr->status);
		if (curr->status != 0 || curr->sig)
			failed += 1;
		print_test(curr, func_name);
		curr = curr->next;
	}
	print_result(i - failed, i);
	cleanup(list);
	return (-(failed != 0));
}


/*
        if (WIFEXITED(wstatus)
		WEXITSTATUS(wstatus));
       WIFSIGNALED(wstatus)) {
       WTERMSIG(wstatus));
*/

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 16:10:09 by alerusso          #+#    #+#             */
/*   Updated: 2026/05/24 17:45:11 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libunit.h"
#include <stdio.h>

int		fork_test(t_test_list *list, t_test_node *curr);
void	print_result(int succeded, int total);
void	print_failure(t_test_list *list, t_test_node *curr, int *failed);
void	open_log_file(t_test_list *list, char *func_name);

/**
 * @brief run all tests in a list, loaded in 00_launcher
 * 
 * @param list 
 * @param func_name name of the function to test (es: strlen)
 * @return int 0 if all tests succeed else -1 
 */
int	launch_tests(t_test_list *list, char *func_name)
{
	t_test_node	*curr;
	int			i;
	int			failed;

	open_log_file(list, func_name);
	i = 0;
	failed = 0;
	curr = list->first;
	while (curr && ++i)
	{
		if (fork_test(list, curr) != 0)
			return (-1);
		if (WIFSIGNALED(curr->status))
			curr->sig = WTERMSIG(curr->status);
		if (WIFEXITED(curr->status))
			curr->status = WEXITSTATUS(curr->status);
		if (curr->status != 0 || curr->sig)
			print_failure(list, curr, &failed);
		close(curr->fd_error);
		print_test(curr, func_name);
		curr = curr->next;
	}
	print_result(i - failed, i);
	cleanup(list);
	return (-(failed != 0));
}

/**
 * @brief create a new process that runs the test
 * 
 * @param list the list to clean up in case of error
 * @param curr the current test node
 * @return int 0
 */
int	fork_test(t_test_list *list, t_test_node *curr)
{
	int	pid;
	int	status;
	int	fds[2];

	if (pipe(fds) == -1)
		error(list, "pipe failed\n");
	pid = fork();
	status = 0;
	if (pid == -1)
		error(list, "fork failed\n");
	else if (pid == 0)
	{
		alarm(1);
		dup2(fds[1], 1);
		dup2(fds[1], 2);
		close(fds[1]);
		status = curr->test_func();
		close(fds[0]);
		return (cleanup(list), exit(status), -1);
	}
	close(fds[1]);
	curr->fd_error = fds[0];
	wait(&curr->status);
	return (0);
}

void	print_result(int succeded, int total)
{
	write(1, "\033[33m", 5);
	write(1, "\ntests succeded: ", 17);
	ft_putnbr(succeded);
	write(1, "/", 1);
	ft_putnbr(total);
	if (succeded == total)
		write(1, "\n\033[32mcongratulations! All tests succeded!", 42);
	write(1, "\033[0m\n\n", 7);
}

/**
 * @brief create the log directory and the log file
 * 
 * @param list the list that contains the fd of the log file
 * @param func_name the name of the function currently being tested
 */
void	open_log_file(t_test_list *list, char *func_name)
{
	char	path[256];

	strcpy(path, LOG_PATH);
	strncat(path, func_name, sizeof(path) - strlen(LOG_PATH) - 1);
	strncat(path, ".log", sizeof(path) - 5);
	mkdir(LOG_PATH, 0777);
	list->fd = open(path, O_CREAT | O_TRUNC | O_RDWR, 0666);
	if (list->fd == -1)
		error(list, "failed to open fd\n");
}

void	print_failure(t_test_list *list, t_test_node *curr, int *failed)
{
	char	buff[256];
	int		result;

	(*failed) += 1;
	result = 1;
	write(list->fd, curr->name, ft_strlen(curr->name));
	write(list->fd, "\n", 1);
	write(list->fd, "output: ", 8);
	while (result)
	{
		result = read(curr->fd_error, buff, 256);
		if (result == -1)
			error(list, "failed to read funtion output\n");
		write(list->fd, buff, result);
	}
	write(list->fd, "\n\n", 2);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   06_sigpipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alessandro.russo.frc@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/24 14:44:16 by alerusso          #+#    #+#             */
/*   Updated: 2026/06/28 00:02:43 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tests.h"

int	sig_06_pipe(void)
{
	int	pid;
	int	fds[2];

	if (pipe(fds) == 1)
		return (0);
	pid = fork();
	if (pid < 0)
		return (0);
	if (pid == 0)
	{
		close(fds[0]);
		close(fds[1]);
		exit(42);
	}
	wait(NULL);
	close(fds[0]);
	write(fds[1], "goodbye", 7);
	close(fds[1]);
	return (0);
}

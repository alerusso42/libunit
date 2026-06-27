/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_output.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alessandro.russo.frc@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 15:41:53 by alerusso          #+#    #+#             */
/*   Updated: 2026/06/27 22:36:49 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libunit.h"

t_test_fds	child_init(char *output_path)
{
	t_test_fds	fds;

	fds = (t_test_fds){0};
	fds.output = open(output_path, O_RDONLY);
	if (fds.output < 0)
		error(NULL, "child_init: cannot open output_path");
	return (fds);
}

void	child_cleanup(t_test_fds *fds)
{
	if (!fds)
		return ;
	ft_close(&fds->output);
	ft_close(&fds->redirect_stderr[0]);
	ft_close(&fds->redirect_stdout[0]);
	ft_close(&fds->redirect_stderr[1]);
	ft_close(&fds->redirect_stdout[1]);
	ft_close(&fds->restore_stderr);
	ft_close(&fds->restore_stdout);
	*fds = (t_test_fds){0};		
}

void	child_redirect(t_test_fds *fds, int fd_fileno)
{
	if (fd_fileno != 1 && fd_fileno != 2)
	{
		child_cleanup(fds);
		error(NULL, "child_redirect: error");
	}
	else if (fd_fileno == 1)
	{
		fds->restore_stdout = dup(STDOUT_FILENO);
		if (fds->restore_stdout < 0)
			return (child_redirect(fds, -1));
		if (pipe(fds->redirect_stdout) != 0)
			return (child_redirect(fds, -1));
		if (dup2(fds->redirect_stdout[1], STDOUT_FILENO) < 0)
			return (child_redirect(fds, -1));
	}
	else if (fd_fileno == 2)
	{
		fds->restore_stderr = dup(STDERR_FILENO);
		if (fds->restore_stderr < 0)
			return (child_redirect(fds, -1));
		if (pipe(fds->redirect_stderr) != 0)
			return (child_redirect(fds, -1));
		if (dup2(fds->redirect_stderr[1], STDERR_FILENO) < 0)
			return (child_redirect(fds, -1));
	}
}

char	*child_release(t_test_fds *fds, int fd_fileno)
{
	char	*output;
	int		fd_input;
	int		pipe_size;

	if (fd_fileno != 1 && fd_fileno != 2)
		return (child_cleanup(fds), error(NULL, "child_release: error"), NULL);
	else if (fd_fileno == 1)
	{
		ft_close(&fds->redirect_stdout[1]);
		fd_input = fds->redirect_stdout[0];
		dup2(fds->restore_stdout, STDOUT_FILENO);
	}
	else if (fd_fileno == 2)
	{
		ft_close(&fds->redirect_stderr[1]);
		fd_input = fds->redirect_stderr[0];
		dup2(fds->restore_stderr, STDERR_FILENO);
	}
	if (ioctl(fd_input, FIONREAD, &pipe_size) < 0 || pipe_size < 0)
		return (NULL);
	output = ft_readfile(fd_input, pipe_size);
	if (output)
		write(fd_fileno, output, strlen(output));
	return (output);
}

/**
 * @param {t_test_fds}:fds ptr to the child fds
 */
int	child_cmp(t_test_fds *fds, int test_flags, int fd_fileno)
{
	char	*output_real;
	char	*output_expected;
	char	output_exist_bool;
	int		cmp;

	output_real = child_release(fds, fd_fileno);
	output_exist_bool = output_real != NULL;
	if (test_flags & LIBUNIT_FLAGS_EXIST)
		return (free(output_real), output_exist_bool);
	output_expected = ft_readfile(fds->output, -1);
	if (fds->output > 0)
		lseek(fds->output, 0, SEEK_SET);
	if (!output_expected && !output_real)
		return (free(output_real), free(output_expected), 0);
	else if (output_expected && !output_real)
		return (free(output_expected), 1);
	else if (!output_expected && output_real)
		return (free(output_real), -1);
	cmp = strcmp(output_expected, output_real);
	return (free(output_real), free(output_expected), cmp);
}

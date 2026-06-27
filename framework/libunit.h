/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libunit.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alessandro.russo.frc@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 18:10:34 by alerusso          #+#    #+#             */
/*   Updated: 2026/06/27 22:35:29 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBUNIT_H
# define LIBUNIT_H

//allow to check a pipe buffer size
#include <sys/ioctl.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <stdlib.h>
# include <signal.h>
# include <stdio.h>
# include <sys/stat.h>
# include <sys/wait.h>

# define LOG_PATH "../log/"
# define LIBUNIT_BUFFER 256
# define LIBUNIT_PIPE_ENDMARK "LIBUNIT_PIPE_ENDMARK"

enum	e_status
{
	STATUS_NO_RUN = -2,
	STATUS_KO = -1,
	STATUS_OK = 0,
};

enum	e_test_flags
{
	LIBUNIT_FLAGS_ZERO = 0,
	LIBUNIT_FLAGS_EXIST = 1 << 0
};

typedef struct s_test_list	t_test_list;
typedef struct s_test_node	t_test_node;
typedef struct s_test_fds	t_test_fds;

struct s_test_list
{
	t_test_node	*first;
	t_test_node	*last;
	int			status;
	int			fd;
};

struct s_test_node
{
	t_test_node	*next;
	char		*name;
	int			(*test_func)(void);
	int			sig;
	int			fd_error;
	int			status;
};

struct s_test_fds
{
	int	output;
	int	restore_stdout;
	int	restore_stderr;
	int	redirect_stdout[2];
	int	redirect_stderr[2];
};


void		cleanup(t_test_list *list);
void		error(t_test_list *list, char *log);
int			launch_tests(t_test_list *list, char *func_name);
void		load_test(t_test_list *list, char *test_type, int (*test)(void));
void		print_test(t_test_node *node, char *func_name);
void		ft_putnbr(int num);
char		*ft_strndup(char *str, int n);
char		*ft_readfile(int fd, int max_size);
void		ft_close(int *fd);
t_test_fds	child_init(char *output_path);
void		child_cleanup(t_test_fds *fds);
void		child_redirect(t_test_fds *fds, int fd_fileno);
char		*child_release(t_test_fds *fds, int fd_fileno);
int			child_cmp(t_test_fds *fds, int test_flags, int fd_fileno);

#endif
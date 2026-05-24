/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libunit.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 18:10:34 by alerusso          #+#    #+#             */
/*   Updated: 2026/05/24 14:36:21 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBUNIT_H
# define LIBUNIT_H

# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <sys/wait.h>
# include "../libft/libft.h"

enum	e_status
{
	STATUS_NO_RUN = -2,
	STATUS_KO = -1,
	STATUS_OK = 0,
};

typedef struct s_test_list	t_test_list;
typedef struct s_test_node	t_test_node;

struct s_test_list
{
	t_test_node	*first;
	t_test_node	*last;
	int			status;
};

struct s_test_node
{
	t_test_node	*next;
	char		*name;
	int			(*test_func)(void);
	int			sig;
	int			status;
};

void	cleanup(t_test_list *list);
void	error(t_test_list *list, char *log);
int		launch_tests(t_test_list *list, char *func_name);
void	load_test(t_test_list *list, char *test_type, int (*test)(void));
void	print_test(t_test_node *node, char *func_name);

#endif
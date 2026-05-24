/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 15:20:45 by alerusso          #+#    #+#             */
/*   Updated: 2026/05/24 15:20:53 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libunit.h"

void	load_test(t_test_list *list, char *test_type, int (*test)(void))
{
	t_test_node	*last;
	t_test_node	*new_node;

	last = list->last;
	new_node = malloc(sizeof(t_test_node));
	if (!new_node)
		error(list, "malloc failed during test initialization");
	new_node->next = NULL;
	new_node->name = test_type;
	new_node->test_func = test;
	new_node->sig = 0;
	new_node->status = STATUS_NO_RUN;
	if (!list->first)
		list->first = new_node;
	if (!list->last)
	{
		list->last = new_node;
		return ;
	}
	last->next = new_node;
	list->last = new_node;
}

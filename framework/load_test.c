/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 15:20:45 by alerusso          #+#    #+#             */
/*   Updated: 2026/05/24 17:47:22 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libunit.h"

/**
 * @brief initialize the next test node
 * 
 * @param list the list of nodes to append the created node to
 * @param test_type the type of test function saved in the node
 * @param test the function to load in the node
 */
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

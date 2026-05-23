/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 15:20:39 by alerusso          #+#    #+#             */
/*   Updated: 2026/05/23 15:40:25 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libunit.h"

void	cleanup(t_test_list *list)
{
	t_test_node	*curr;
	t_test_node	*next;

	if (!list)
		return ;
	curr = list->first;
	while (curr)
	{
		next = curr->next;
		free(curr);
		curr = next;
	}
	list->first = NULL;
	list->last = NULL;
}
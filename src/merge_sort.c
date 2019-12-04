/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 15:45:33 by thallot           #+#    #+#             */
/*   Updated: 2019/10/30 16:19:38 by thallot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

void		mergesort_elem(t_args *args, t_elem **headref, int time)
{
	t_elem	*head;
	t_elem	*a;
	t_elem	*b;

	head = *headref;
	if ((head == NULL) || (head->next == NULL))
		return ;
	frontbacksplit(head, &a, &b);
	mergesort_elem(args, &a, time);
	mergesort_elem(args, &b, time);
	if (time == 0)
		*headref = sortedmerge(args, a, b);
	else
		*headref = sortedmerge_time(args, a, b);
}

t_elem		*sortedmerge(t_args *args, t_elem *a, t_elem *b)
{
	t_elem	*result;

	result = NULL;
	if (a == NULL)
		return (b);
	else if (b == NULL)
		return (a);
	if ((!args->r && ft_strcmp(a->file->d_name, b->file->d_name) < 0)
			|| (args->r && ft_strcmp(a->file->d_name, b->file->d_name) > 0))
	{
		result = a;
		result->next = sortedmerge(args, a->next, b);
	}
	else
	{
		result = b;
		result->next = sortedmerge(args, a, b->next);
	}
	return (result);
}

t_elem		*sortedmerge_time(t_args *args, t_elem *a, t_elem *b)
{
	t_elem	*result;

	result = NULL;
	if (a == NULL)
		return (b);
	else if (b == NULL)
		return (a);
	if (sort_time_condition(args, a, b))
	{
		result = a;
		result->next = sortedmerge_time(args, a->next, b);
	}
	else
	{
		result = b;
		result->next = sortedmerge_time(args, a, b->next);
	}
	return (result);
}

void		frontbacksplit(t_elem *source, t_elem **frontref, t_elem **backref)
{
	t_elem *fast;
	t_elem *slow;

	slow = source;
	fast = source->next;
	while (fast != NULL)
	{
		fast = fast->next;
		if (fast != NULL)
		{
			slow = slow->next;
			fast = fast->next;
		}
	}
	*frontref = source;
	*backref = slow->next;
	slow->next = NULL;
}

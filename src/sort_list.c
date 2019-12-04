/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_listing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 11:45:34 by thallot           #+#    #+#             */
/*   Updated: 2019/10/24 16:40:58 by thallot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

t_elem	*swap_elem(t_elem *ptr1, t_elem *ptr2)
{
	t_elem *tmp;

	tmp = ptr2->next;
	ptr2->next = ptr1;
	ptr1->next = tmp;
	return (ptr2);
}

t_lst	*swap_args(t_lst *ptr1, t_lst *ptr2)
{
	t_lst *tmp;

	tmp = ptr2->next;
	ptr2->next = ptr1;
	ptr1->next = tmp;
	return (ptr2);
}

void	sort_list(t_args *args, t_elem **elem, int count)
{
	t_elem	**h;
	int		i;
	int		j;
	t_elem	*p1;
	t_elem	*p2;

	i = -1;
	while (++i <= count)
	{
		h = elem;
		j = -1;
		while (++j < count - i - 1)
		{
			p1 = *h;
			p2 = p1->next;
			if ((!args->r && ft_strcmp(p1->file->d_name, p2->file->d_name) > 0)
			|| (args->r && ft_strcmp(p1->file->d_name, p2->file->d_name) < 0))
			{
				*h = swap_elem(p1, p2);
				i = 0;
			}
			h = &(*h)->next;
		}
	}
}

void	sort_time(t_args *args, t_elem **elem, int count)
{
	t_elem	**h;
	int		i;
	int		j;
	t_elem	*p1;
	t_elem	*p2;

	i = -1;
	while (++i <= count)
	{
		h = elem;
		j = -1;
		while (++j < count - i - 1)
		{
			p1 = *h;
			p2 = p1->next;
			if (sort_time_condition(args, p1, p2))
			{
				*h = swap_elem(p1, p2);
				i = 0;
			}
			h = &(*h)->next;
		}
	}
}

void	sort_args(t_lst **list, int count)
{
	t_lst	**h;
	int		i;
	int		j;
	t_lst	*p1;
	t_lst	*p2;

	i = -1;
	while (++i <= count)
	{
		h = list;
		j = -1;
		while (++j < count - i - 1)
		{
			p1 = *h;
			p2 = p1->next;
			if (ft_strcmp(p1->name, p2->name) > 0)
			{
				*h = swap_args(p1, p2);
				i = 0;
			}
			h = &(*h)->next;
		}
	}
}

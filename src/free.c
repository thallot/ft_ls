/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 10:00:04 by thallot           #+#    #+#             */
/*   Updated: 2019/10/24 16:36:40 by thallot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

void	go_next(t_args *args)
{
	t_lst *lst;

	lst = args->list;
	args->list = args->list->next;
	ft_strdel(&(lst)->name);
	ft_memdel((void **)&lst);
}

void	free_tab(char **tab, int size)
{
	int i;

	i = 0;
	while (i < size)
	{
		ft_strdel(&(tab[i]));
		i++;
	}
	ft_memdel((void **)&tab);
}

int		list_delete(t_args *args, t_elem **elem)
{
	if (!(*elem))
		return (0);
	while ((*elem)->next)
		list_delete(args, &((*elem)->next));
	elem_delete(args, elem);
	return (1);
}

void	elem_delete(t_args *args, t_elem **elem)
{
	if (!elem)
		return ;
	ft_memdel((void **)&((*elem)->path));
	ft_memdel((void **)&((*elem)->file));
	ft_memdel((void **)&((*elem)->next));
	ft_memdel((void **)&((*elem)->filestat));
	ft_memdel((void **)&((*elem)->user));
	ft_memdel((void **)&((*elem)->group));
	ft_memdel((void **)&((*elem)->name));
	ft_memdel((void **)&((*elem)->min));
	ft_memdel((void **)&((*elem)->max));
	ft_memdel((void **)elem);
	(void)args;
	(*elem) = NULL;
}

char	*strjoinfree(char *s1, char *s2, int opt)
{
	char *tmp;

	tmp = s1;
	s1 = ft_strjoin(s1, s2);
	if (opt >= 1)
		ft_strdel(&tmp);
	if (opt >= 2)
		ft_strdel(&s2);
	return (s1);
}

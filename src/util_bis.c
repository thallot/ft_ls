/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setter_elem.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 10:29:25 by thallot           #+#    #+#             */
/*   Updated: 2019/10/30 12:01:38 by thallot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

int		sort_time_condition(t_args *args, t_elem *p1, t_elem *p2)
{
	if ((!args->r && ((p1->filestat->st_mtime > p2->filestat->st_mtime)
	|| (p1->filestat->st_mtime == p2->filestat->st_mtime
	&& ft_strcmp(p1->file->d_name, p2->file->d_name) < 0)))
	|| (args->r && ((p1->filestat->st_mtime < p2->filestat->st_mtime)
	|| (p1->filestat->st_mtime == p2->filestat->st_mtime
	&& ft_strcmp(p1->file->d_name, p2->file->d_name) > 0))))
		return (1);
	return (0);
}

void	set_elem(t_elem **head, t_elem *elem, t_len *len, char *path)
{
	if (len->nbr_elem == 0)
	{
		*head = elem;
		(*head)->len = len;
	}
	*head = len->nbr_elem == 0 ? elem : *head;
	elem->head = len->nbr_elem > 0 ? *head : elem->head;
	elem->hidden = elem->file->d_name[0] == '.' ? 1 : 0;
	elem->type = elem->file->d_type;
	if (!elem->path)
		elem->path = ft_strdup(path);
	if (elem->path[ft_strlen(elem->path) - 1] != '/')
		elem->path = strjoinfree(elem->path, "/", 1);
	elem->path = strjoinfree(elem->path, elem->file->d_name, 1);
}

t_lst	*add_list(t_lst **list, char *name)
{
	t_lst *new;
	t_lst **head;

	head = list;
	if (!(new = (t_lst *)ft_memalloc((sizeof(t_lst)))))
		return (NULL);
	new->name = ft_strdup(name);
	new->next = NULL;
	if (!(*list))
		*list = new;
	else
	{
		while ((*list)->next)
			list = &(*list)->next;
		(*list)->next = new;
	}
	list = head;
	return (*head);
}

int		is_link(t_elem *elem)
{
	int ret;

	if ((ret = readlink(elem->path, elem->readlink, 1023)) < 0)
	{
		elem->readlink[0] = '\0';
		return (0);
	}
	else
	{
		elem->readlink[ret] = '\0';
		return (1);
	}
}

int		recusiv_condition(t_args *args, t_elem *elem)
{
	if (elem->type == DIRECTORY && args->rec)
	{
		if (!elem->hidden || (args->a && elem->hidden))
		{
			if (ft_strcmp(elem->file->d_name, ".")
				&& ft_strcmp(elem->file->d_name, ".."))
				return (1);
		}
	}
	return (0);
}

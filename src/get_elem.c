/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_elem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 10:10:06 by thallot           #+#    #+#             */
/*   Updated: 2019/10/30 11:37:06 by thallot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

t_elem	*add_elem(t_args *args, t_elem *elem, struct dirent *ptr)
{
	t_elem *new;

	if (!(new = (t_elem *)ft_memalloc(sizeof(t_elem))))
		return (NULL);
	if (ptr)
	{
		if (!(new->file = (struct dirent *)malloc(sizeof(struct dirent))))
			return (NULL);
		if (!(new->file = ft_memcpy(new->file, ptr, sizeof(struct dirent))))
			return (NULL);
	}
	if (args->l || args->g || args->file || args->t)
	{
		if (!(new->filestat = (struct stat *)malloc(sizeof(struct stat))))
			return (NULL);
		new->is_stat = 1;
	}
	new->next = elem;
	return (new);
}

t_len	*init_len(DIR *rep)
{
	t_len *len;

	if (!rep)
		return (NULL);
	if (!(len = (t_len *)ft_memalloc(sizeof(t_len))))
		return (NULL);
	return (len);
}

t_elem	*end_list(t_len *len, t_args *args, t_elem *elem)
{
	if (len->name)
		len->nbr_column = args->w_len / (len->name + 1);
	if (args->t)
		mergesort_elem(args, &elem, 1);
	else
		mergesort_elem(args, &elem, 0);
	if (len->nbr_elem == 0)
		ft_memdel((void **)&len);
	return (elem);
}

t_elem	*get_elem(t_args *args, t_elem *elem, DIR *rep, char *path)
{
	struct dirent	*file;
	t_elem			*head;
	t_len			*len;

	if (!(len = init_len(rep)))
		return (NULL);
	while ((file = readdir(rep)) != NULL)
	{
		if (file->d_name[0] != '.' || (file->d_name[0] == '.' && args->a))
		{
			if (!(elem = add_elem(args, elem, file)))
				return (NULL);
			set_elem(&head, elem, len, path);
			set_len(args, elem, head, len);
			if (recusiv_condition(args, elem))
			{
				elem->dir = opendir(elem->path);
				elem->rep = get_elem(args, elem->rep, elem->dir, elem->path);
				elem->dir ? closedir(elem->dir) : 0;
			}
			len->nbr_elem++;
		}
	}
	elem = end_list(len, args, elem);
	return (elem);
}

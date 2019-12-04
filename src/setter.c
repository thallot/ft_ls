/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 13:06:53 by thallot           #+#    #+#             */
/*   Updated: 2019/10/30 12:10:05 by thallot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

void	set_stat(t_args *args, t_elem *elem, t_elem *head)
{
	acl_t			acl;
	int				link;

	acl = NULL;
	if (args->l || args->g || args->t)
	{
		link = is_link(elem);
		if ((link && lstat(elem->path, elem->filestat) < 0)
				|| (!link && stat(elem->path, elem->filestat) < 0))
			elem->is_stat = 0;
		if ((S_ISLNK(elem->filestat->st_mode) ||
				S_ISREG(elem->filestat->st_mode)) && elem->filestat->st_size)
			elem->attr = listxattr(elem->path, NULL, 0, XATTR_NOFOLLOW);
		if (acl_get_link_np(elem->path, ACL_TYPE_EXTENDED))
		{
			free(acl);
			elem->acl = 1;
		}
		if (elem->is_stat == 1)
		{
			elem->user = ft_strdup(getpwuid(elem->filestat->st_uid)->pw_name);
			elem->group = ft_strdup(getgrgid(elem->filestat->st_gid)->gr_name);
		}
		head->len->total += elem->filestat->st_blocks;
	}
}

void	set_len(t_args *args, t_elem *elem, t_elem *head, t_len *len)
{
	mode_t mode;

	set_stat(args, elem, head);
	if (elem->is_stat)
		mode = elem->filestat->st_mode;
	if ((args->l || args->t || args->g) && (S_ISBLK(mode) || S_ISCHR(mode)))
	{
		if (minor(elem->filestat->st_rdev) > 255)
			elem->min = ft_itoa_base_int(16, minor(elem->filestat->st_rdev));
		else
			elem->min = ft_itoa(minor(elem->filestat->st_rdev));
		if (major(elem->filestat->st_rdev) > 255)
			elem->max = ft_itoa_base_int(16, major(elem->filestat->st_rdev));
		else
			elem->max = ft_itoa(major(elem->filestat->st_rdev));
		len->chars = 1;
	}
	if (head->len->name == 0 || ft_strlen(elem->file->d_name) > head->len->name)
		head->len->name = ft_strlen(elem->file->d_name);
	len->nbr_elem_hidden += elem->hidden ? 1 : 0;
	if (elem->is_stat)
	{
		set_len_size(args, elem, head);
		set_len_char(args, elem, head);
	}
}

void	set_len_char(t_args *args, t_elem *elem, t_elem *head)
{
	size_t	size;
	int		tmp;

	if (((args->a && elem->hidden) || !elem->hidden) && elem->user)
	{
		size = ft_strlen(elem->user);
		if (size > head->len->user)
			head->len->user = size;
		size = ft_strlen(elem->group);
		if (size > head->len->group)
			head->len->group = size;
	}
	size = 0;
	tmp = elem->filestat->st_nlink;
	while (tmp)
	{
		tmp /= 10;
		size++;
	}
	if (elem->is_stat == 1 && head->len->link < size)
		head->len->link = size;
}

void	set_len_minor(t_args *args, t_elem *elem, t_elem *head)
{
	int		tmp;
	size_t	size;

	if ((args->l || args->g)
	&& (S_ISBLK(elem->filestat->st_mode) || S_ISCHR(elem->filestat->st_mode)))
	{
		size = 1;
		tmp = minor(elem->filestat->st_rdev);
		while (tmp /= 10)
			size++;
		if (elem->is_stat == 1 && head->len->size < size)
			head->len->size = size;
		size = 1;
		tmp = major(elem->filestat->st_rdev);
		while (tmp /= 10)
			size++;
		if (elem->is_stat == 1 && head->len->size < size)
			head->len->size = size;
	}
}

void	set_len_size(t_args *args, t_elem *elem, t_elem *head)
{
	int		tmp;
	size_t	size;

	if ((args->a && elem->hidden) || !elem->hidden)
	{
		size = 1;
		tmp = elem->filestat->st_size;
		while (tmp /= 10)
			size++;
		if (elem->is_stat == 1 && head->len->size < size)
			head->len->size = size;
	}
	set_len_minor(args, elem, head);
}

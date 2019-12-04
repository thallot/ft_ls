/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 11:14:00 by thallot           #+#    #+#             */
/*   Updated: 2019/10/24 16:32:03 by thallot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

int		ft_ls_file_core(t_args *args, t_elem *elem, int ret)
{
	struct passwd	*usr;
	struct group	*grp;
	t_len			*len;

	if (!(len = (t_len *)ft_memalloc(sizeof(t_len))))
		return (-2);
	if (ret < 0)
		get_name(args, elem);
	else
		elem->name = ft_strdup(args->path);
	usr = getpwuid(elem->filestat->st_uid);
	elem->user = ft_strdup(usr->pw_name);
	grp = getgrgid(elem->filestat->st_gid);
	elem->group = ft_strdup(grp->gr_name);
	if (args->g || args->l)
		print_info(args, elem, len);
	else if (ret < 0)
		ft_putendl(elem->name);
	else
		ft_putendl(args->path);
	list_delete(args, &elem);
	ft_memdel((void **)&len);
	return (1);
}

int		ft_ls_file(t_args *args, t_elem *elem)
{
	int ret;

	args->file = 1;
	elem = add_elem(args, elem, NULL);
	elem->path = ft_strdup(args->path);
	ret = is_link(elem);
	if (((ret > 0 && lstat(args->path, elem->filestat) >= 0 && args->l)
			|| (stat(args->path, elem->filestat) >= 0))
			&& !S_ISDIR(elem->filestat->st_mode))
		return (ft_ls_file_core(args, elem, ret));
	else if (S_ISDIR(elem->filestat->st_mode))
		return (0);
	list_delete(args, &elem);
	return (-1);
}

void	ft_ls_loop_core(t_args *args, t_elem *elem, DIR *rep)
{
	char buffer[2];

	if (readlink(args->path, buffer, 1) > 0 && args->l)
		ft_ls_file(args, elem);
	else
	{
		if (args->len > 1)
			ft_printf("%s:\n", args->list->name);
		elem = get_elem(args, elem, rep, args->path);
		if (elem)
			print_elem(args, elem);
	}
	closedir(rep);
}

void	ft_ls_loop(t_args *args)
{
	t_elem	*elem;
	int		file;
	DIR		*rep;

	while (args->list)
	{
		elem = NULL;
		rep = NULL;
		args->path = args->list->name;
		if (!(rep = opendir(args->path)))
		{
			if ((file = ft_ls_file(args, elem)) == -1)
				ft_printf("ls : %s: No such file or directory\n", args->path);
			else if (file == 0)
			{
				if (args->len > 1)
					ft_printf("%s:\n", args->list->name);
				ft_printf("ls: %s: Permission denied\n", args->path);
			}
		}
		else
			ft_ls_loop_core(args, elem, rep);
		args->list->next ? ft_putchar('\n') : 0;
		go_next(args);
	}
}

int		main(int argc, char **argv)
{
	t_args args;

	init_args(&args);
	if (parsing(&args, argv, argc) == 0)
	{
		ft_printf("ls: illegal option\nusage: ls [-%s] [file...]\n", OPTIONS);
		ft_memdel((void **)&(args).list);
		return (0);
	}
	else
		ft_ls_loop(&args);
	ft_memdel((void **)&(args).list);
	return (1);
}

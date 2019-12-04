/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 14:34:36 by thallot           #+#    #+#             */
/*   Updated: 2019/10/30 13:49:01 by thallot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

void	print_right(t_elem *elem)
{
	ft_putchar((elem->filestat->st_mode & S_IRUSR) ? 'r' : '-');
	ft_putchar((elem->filestat->st_mode & S_IWUSR) ? 'w' : '-');
	ft_putchar((elem->filestat->st_mode & S_IXUSR) ? 'x' : '-');
	ft_putchar((elem->filestat->st_mode & S_IRGRP) ? 'r' : '-');
	ft_putchar((elem->filestat->st_mode & S_IWGRP) ? 'w' : '-');
	ft_putchar((elem->filestat->st_mode & S_IXGRP) ? 'x' : '-');
	ft_putchar((elem->filestat->st_mode & S_IROTH) ? 'r' : '-');
	ft_putchar((elem->filestat->st_mode & S_IWOTH) ? 'w' : '-');
	ft_putchar((elem->filestat->st_mode & S_IXOTH) ? 'x' : '-');
}

void	print_access(t_elem *elem)
{
	if (S_ISLNK(elem->filestat->st_mode))
		ft_putchar('l');
	else if (S_ISSOCK(elem->filestat->st_mode))
		ft_putchar('s');
	else if (S_ISDIR(elem->filestat->st_mode))
		ft_putchar('d');
	else if (S_ISBLK(elem->filestat->st_mode))
		ft_putchar('b');
	else if (S_ISCHR(elem->filestat->st_mode))
		ft_putchar('c');
	else if (S_ISFIFO(elem->filestat->st_mode))
		ft_putchar('p');
	else
		ft_putchar('-');
	print_right(elem);
	if (elem->attr > 0)
		ft_putchar('@');
	else if (elem->acl)
		ft_putchar('+');
	else
		ft_putchar(' ');
}

void	print_info(t_args *args, t_elem *elem, t_len *len)
{
	print_access(elem);
	ft_printf(" %*d", len->link, elem->filestat->st_nlink);
	if (!args->g)
		ft_printf(" %*-s ", len->user, elem->user);
	ft_printf(" %*-s", len->group, elem->group);
	if (S_ISBLK(elem->filestat->st_mode) || S_ISCHR(elem->filestat->st_mode))
	{
		ft_printf("   %*s,", len->size / 2, elem->max);
		ft_printf(" %*s", (len->size / 2) + 1, elem->min);
	}
	else if (len->chars)
		ft_printf("  %*lld", (len->size * 2) - 1, elem->filestat->st_size);
	else
		ft_printf("  %*lld", len->size, elem->filestat->st_size);
	ft_putnstr(ctime(&(elem->filestat)->st_mtime) + 3, 13);
	if (elem->name)
		ft_printf(" %s", elem->name);
	else
		ft_printf(" %s", elem->file->d_name);
	if (elem->readlink[0] != '\0')
		ft_printf(" -> %s\n", elem->readlink);
	else
		ft_putchar('\n');
}

void	print_classic(t_args *args, t_elem *list, t_len *len)
{
	t_elem *elem;

	elem = list;
	if (args->rec && !args->l && args->deep)
		ft_putchar('\n');
	while (elem)
	{
		if (args->l || args->g)
			print_info(args, elem, len);
		else
			ft_printf("%*-s ", len->name, elem->file->d_name);
		if (args->one && ((elem->hidden && args->a) || !elem->hidden))
			ft_putchar('\n');
		elem = elem->next;
	}
}

void	print_elem(t_args *args, t_elem *list)
{
	t_elem	*elem;
	t_len	*len;

	elem = list;
	len = elem->len ? elem->len : elem->head->len;
	if ((args->l || args->g) && len->nbr_elem != 0)
		ft_printf("total %u\n", len->total);
	if ((!args->l && !args->g)
	&& args->w_len < (len->nbr_elem) * (len->name + 1) && !args->one)
		print_recursive(args, elem, len);
	else
		print_classic(args, elem, len);
	elem = list;
	if ((!args->one && !args->l && !args->g) || len->nbr_elem == 0)
		ft_putchar('\n');
	print_elem_recursive(elem, args);
	ft_memdel((void **)&len);
	list_delete(args, &list);
}

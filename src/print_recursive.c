/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_bis.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 12:12:50 by thallot           #+#    #+#             */
/*   Updated: 2019/10/30 15:01:39 by thallot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

void	print_recursive(t_args *args, t_elem *list, t_len *len)
{
	char	**tab;
	t_elem	*elem;

	elem = list;
	len = set_column(args, len);
	tab = create_tab(elem, args, len->elem);
	args->deep ? ft_putchar('\n') : 0;
	print_tab(len, tab, elem, 0);
	free_tab(tab, len->elem);
}

char	**create_tab(t_elem *elem, t_args *args, int elem_size)
{
	int		size;
	char	**tab;

	tab = NULL;
	size = 0;
	tab = (char **)malloc(sizeof(char *) * elem_size);
	while (elem)
	{
		if ((elem->hidden && args->a) || !elem->hidden)
		{
			tab[size] = ft_strdup(elem->file->d_name);
			size++;
		}
		elem = elem->next;
	}
	return (tab);
}

t_len	*set_column(t_args *args, t_len *len)
{
	len->elem = args->a ? len->nbr_elem : len->nbr_elem - len->nbr_elem_hidden;
	if (len->nbr_column > len->nbr_elem / 2)
		len->nbr_column = (len->nbr_elem / 2) + (len->nbr_elem % 2);
	len->nbr_column = len->nbr_column == 0 ? 1 : len->nbr_column;
	len->mod = len->elem % len->nbr_column;
	len->mod = len->mod > 1 ? 1 : 0;
	return (len);
}

void	print_tab(t_len *len, char **tab, t_elem *elem, size_t i)
{
	size_t	column;
	size_t	save;
	int		print;

	while (i < (len->elem / len->nbr_column) + len->mod && elem)
	{
		column = 0;
		save = i;
		while (column++ < len->nbr_column)
		{
			if (i < len->elem && ++print)
				ft_printf("%*-s", len->name + 1, tab[i]);
			i = i + (len->elem / len->nbr_column) + len->mod;
		}
		if (print && save + 1 < (len->elem / len->nbr_column) + len->mod)
		{
			ft_putchar('\n');
			print = 0;
		}
		i = save;
		i++;
		elem = elem->next;
	}
}

void	print_elem_recursive(t_elem *elem, t_args *args)
{
	while (args->rec && elem)
	{
		if (recusiv_condition(args, elem))
		{
			ft_printf("\n%s:", elem->path);
			args->l || args->g ? ft_putchar('\n') : 0;
			args->deep++;
			if (elem->rep)
				print_elem(args, elem->rep);
			else
			{
				ft_putchar('\n');
			}
		}
		elem = elem->next;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 11:20:48 by thallot           #+#    #+#             */
/*   Updated: 2019/07/16 14:52:24 by thallot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	free_tab(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
	{
		ft_memdel((void **)&tab[i]);
		i++;
	}
	ft_memdel((void **)&tab);
}

void	free_tab_int(int **tab, int size)
{
	int i;

	i = 0;
	while (i < size)
	{
		ft_memdel((void **)&tab[i]);
		i++;
	}
	ft_memdel((void **)&tab);
}

int		check_file(char **argv)
{
	int fd;

	fd = open(argv[1], O_RDONLY);
	if (fd <= 0)
		return (0);
	if (read(fd, 0, 0) == -1)
		return (0);
	return (1);
}

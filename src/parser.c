/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 12:27:04 by thallot           #+#    #+#             */
/*   Updated: 2019/07/10 14:13:49 by thallot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int		check_line(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]) && str[i] != ' ' && str[i] != '-')
			return (0);
		i++;
	}
	return (1);
}

char	*make_str(char **av)
{
	int		fd;
	char	*str;
	char	*tmp;
	char	*line;

	fd = open(av[1], O_RDONLY);
	if (fd <= 0)
		return (NULL);
	str = ft_strnew(1);
	line = NULL;
	while (get_next_line(fd, &line))
	{
		tmp = str;
		str = ft_strjoin(str, line);
		ft_strdel(&tmp);
		if (check_line(line) == 0)
			ft_strdel(&str);
		tmp = str;
		str = ft_strjoin(str, "\n");
		ft_strdel(&tmp);
		ft_strdel(&line);
	}
	ft_strdel(&line);
	return (str);
}

char	**make_tab(char *str)
{
	char **tab;

	if (!str)
		return (NULL);
	if (!(tab = ft_strsplit(str, '\n')))
		return (NULL);
	ft_strdel(&str);
	return (tab);
}

t_fdf	*make_map(char **tab, t_fdf *fdf, int i, int j)
{
	char	**tab_nb;

	if (!tab)
		return (NULL);
	if (!(fdf = init_fdf(tab, fdf, 0, 0)))
		return (NULL);
	while (tab[i])
	{
		j = -1;
		if (!(tab_nb = ft_strsplit(tab[i], ' ')))
			return (NULL);
		while (tab_nb[++j])
		{
			if (atoli(tab_nb[j]) <= INT_MAX && atoli(tab_nb[j]) >= INT_MIN)
				fdf->map[i][j] = atoli(tab_nb[j]);
			else
				fdf->error = 1;
		}
		if (j != fdf->width)
			fdf->error = 1;
		free_tab(tab_nb);
		i++;
	}
	free_tab(tab);
	return (fdf);
}

t_fdf	*init_fdf(char **tab, t_fdf *fdf, int i, int j)
{
	int		len;
	int		**map;
	char	**tab_nb;

	len = 0;
	while (tab[len])
		len++;
	if (!(fdf = (t_fdf *)ft_memalloc(sizeof(t_fdf))))
		return (NULL);
	fdf->height = len;
	if (!(map = (int **)ft_memalloc(sizeof(int *) * (len))))
		return (NULL);
	if (!(tab_nb = ft_strsplit(tab[0], ' ')))
		return (NULL);
	while (tab_nb[i])
		i++;
	fdf->width = i;
	while (j < len)
	{
		if (!(map[j++] = (int *)ft_memalloc(sizeof(int) * (i))))
			return (NULL);
	}
	fdf->map = map;
	free_tab(tab_nb);
	return (fdf);
}

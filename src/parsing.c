/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 13:00:19 by thallot           #+#    #+#             */
/*   Updated: 2019/10/30 11:51:19 by thallot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

int		is_option(char *str)
{
	int i;

	i = 1;
	while (str[i])
	{
		if (!is_valid_option(str[i], OPTIONS))
			return (0);
		i++;
	}
	return (1);
}

void	set_option_bis(char c, t_args *args)
{
	if (c == 'f')
	{
		args->t = 0;
		args->f = 1;
		args->r = 0;
		args->g = 0;
	}
	if (c == 'g')
	{
		args->g = 1;
		args->f = 0;
		args->one = 0;
	}
	args->rec = c == 'R' ? 1 : args->rec;
	args->r = c == 'r' && !args->f ? 1 : args->r;
	args->a = c == 'a' ? 1 : args->a;
	args->t = c == 't' ? 1 : args->t;
	args->g = c == 'g' ? 1 : args->g;
}

void	set_option(char c, t_args *args)
{
	if (c == 'l')
	{
		args->l = 1;
		args->one = 0;
	}
	if (c == '1')
	{
		args->l = 0;
		args->one = 1;
		args->g = 0;
	}
	if (c == 't' && args->one)
	{
		args->r = 0;
		args->t = 1;
		args->f = 0;
	}
	set_option_bis(c, args);
}

void	close_parsing(t_args *args)
{
	if (!args->list)
		add_list(&(args)->list, "./");
	if (args->l)
		args->f = 0;
	if (args->f)
		args->a = 1;
	if (args->one)
		args->l = 0;
}

int		parsing(t_args *args, char **av, int ac)
{
	int i;
	int j;

	i = 0;
	while (++i < ac)
	{
		j = 0;
		if (av[i][j] == '-')
		{
			if (args->path || !is_option(av[i]))
				return (0);
			while (av[i][j])
			{
				set_option(av[i][j], args);
				j++;
			}
			if (j == 1)
				return (0);
		}
		else if (++args->len)
			args->list = add_list(&(args)->list, av[i]);
	}
	sort_args(&(args)->list, args->len);
	close_parsing(args);
	return (1);
}

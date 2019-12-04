/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 15:59:37 by thallot           #+#    #+#             */
/*   Updated: 2019/10/30 11:52:46 by thallot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

int		is_valid_option(char c, char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void	get_name(t_args *args, t_elem *elem)
{
	char	*rev;
	int		len;
	int		i;

	len = ft_strlen(args->path);
	rev = ft_strdup(ft_strrev(args->path));
	i = 0;
	while (rev[i] && rev[i] != '/')
		i++;
	elem->name = ft_strndup(args->path, len - (len - i));
	elem->name = ft_strrev(elem->name);
	ft_strrev(args->path);
	ft_strdel(&rev);
}

void	init_args(t_args *args)
{
	struct winsize w;

	ioctl(0, TIOCGWINSZ, &w);
	args->list = NULL;
	args->w_len = w.ws_col;
	args->deep = 0;
	args->path = NULL;
	args->rec = 0;
	args->r = 0;
	args->l = 0;
	args->a = 0;
	args->t = 0;
	args->g = 0;
	args->len = 0;
	args->file = 0;
}

int		ft_pow_int(int nb, int pow)
{
	if (pow == 0)
		return (1);
	else
		return (nb * ft_pow(nb, pow - 1));
}

char	*ft_itoa_base_int(int base, int value)
{
	int				i;
	char			*nbr;
	char			letters;
	char			*tmp;

	letters = 'a';
	i = 8;
	nbr = (char*)ft_memalloc(9);
	nbr[i] = '\0';
	while (i-- > 0)
	{
		nbr[i] = (value % base) + (value % base > 9 ? letters - 10 : '0');
		value = value / base;
	}
	tmp = nbr;
	nbr = ft_strjoin("0x", nbr);
	ft_strdel(&tmp);
	return (nbr);
}

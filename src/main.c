/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 16:42:18 by thallot           #+#    #+#             */
/*   Updated: 2019/07/02 14:13:30 by thallot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int			main(int argc, char **argv)
{
	t_fdf *fdf;

	if (argc == 2 && check_file(argv))
	{
		if ((fdf = make_map(make_tab(make_str(argv)), fdf, 0, 0)))
		{
			if (fdf->error == 1 || fdf->height < 2 || fdf->width < 2)
			{
				free_tab_int(fdf->map, fdf->height);
				ft_memdel((void **)&fdf);
				ft_putendl("Map Error");
				return (0);
			}
			else
				ft_draw_all(fdf);
		}
	}
	else
		ft_putendl("usage : ./fdf source_file");
	return (0);
}

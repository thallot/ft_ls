/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 10:53:37 by thallot           #+#    #+#             */
/*   Updated: 2019/07/11 16:02:19 by thallot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int			mod_color(int keycode, t_fdf *f)
{
	if (keycode == 83)
		f->color_save = 0xFFFFFF;
	else if (keycode == 84)
		f->color_save = 0xFF0000;
	else if (keycode == 85)
		f->color_save = 0x2B87E8;
	else if (keycode == 86)
		f->color_save = 0xE82BCB;
	else if (keycode == 87)
		f->color_save = 0x1CE550;
	else if (keycode == 88)
		f->color_save = 0xEBF20E;
	else if (keycode == 89)
		f->color_save = 0xF2800E;
	else if (keycode == 91)
		f->color_save = 0x0EF2DA;
	else if (keycode == 92)
		f->color_save = 0x771BF5;
	else
		return (0);
	mlx_clear_window(f->mlx, f->win);
	ft_redraw(f);
	return (1);
}

int			mod_graph(int keycode, t_fdf *f)
{
	if (keycode == 116)
		f->deep += f->deep < INT_MAX ? 0.5 : 0;
	else if (keycode == 121)
		f->deep -= f->deep > INT_MIN ? 0.5 : 0;
	else if (keycode == 126)
		f->move_y -= f->move_y > INT_MIN ? 30 : 0;
	else if (keycode == 125)
		f->move_y += f->move_y < INT_MAX ? 30 : 0;
	else if (keycode == 123)
		f->move_x -= f->move_x > INT_MIN ? 30 : 0;
	else if (keycode == 124)
		f->move_x += f->move_x < INT_MAX ? 30 : 0;
	else if (keycode == 69)
		f->zoom += f->zoom < INT_MAX ? 1 : 0;
	else if (keycode == 78)
		f->zoom -= f->zoom > INT_MIN ? 1 : 0;
	else if (keycode == 82)
		f->rot = 3.1;
	else if (keycode == 65)
		f->rot = 0;
	else if (keycode == 34)
		f->iso = f->iso == 1 ? 0 : 1;
	else
		return (0);
	return (1);
}

int			mod_img(int keycode, t_fdf *f)
{
	if (mod_color(keycode, f))
		return (1);
	else if (mod_graph(keycode, f))
	{
		mlx_clear_window(f->mlx, f->win);
		ft_redraw(f);
		return (1);
	}
	else if (keycode == 53)
	{
		free_tab_int(f->map, f->height);
		ft_memdel((void **)&f);
		exit(0);
	}
	else
		return (0);
	mlx_clear_window(f->mlx, f->win);
	ft_redraw(f);
	return (1);
}

int			ft_redraw(t_fdf *f)
{
	mlx_string_put(f->mlx, f->win, 20, 15, 0xFFFFFF, "Quit = [ESC]");
	mlx_string_put(f->mlx, f->win, 20, 35, 0xFFFFFF, "Zoom = [+] [-]");
	mlx_string_put(f->mlx, f->win, 20, 55, 0xFFFFFF,
	"Depth = [Page Up] [Page Down]");
	mlx_string_put(f->mlx, f->win, 20, 75, 0xFFFFFF, "Rotation = [0] [.]");
	mlx_string_put(f->mlx, f->win, 20, 95, 0xFFFFFF, "Move = Arrow");
	mlx_string_put(f->mlx, f->win, 20, 115, 0xFFFFFF, "Color = Pav Num");
	mlx_string_put(f->mlx, f->win, 20, 135, 0xFFFFFF, "View = i");
	ft_draw(f);
	return (0);
}

long int	atoli(const char *str)
{
	unsigned int		i;
	long int			nb;
	int					sign;

	i = 0;
	nb = 0;
	sign = 1;
	while (str[i] == '\f' || str[i] == '\t' || str[i] == '\n'
			|| str[i] == '\r' || str[i] == '\v' || str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10 + (str[i] - '0');
		i++;
	}
	return (nb * sign);
}

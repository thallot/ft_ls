/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 14:40:40 by thallot           #+#    #+#             */
/*   Updated: 2019/07/22 10:48:36 by thallot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	ft_draw_line(t_fdf *f)
{
	double	tx;
	double	dx;
	double	dy;

	tx = 0;
	dx = f->x2 - f->x1;
	dy = f->y2 - f->y1;
	while (tx <= 1)
	{
		f->x = f->x1 + (dx * tx);
		f->y = f->y1 + (dy * tx);
		mlx_pixel_put(f->mlx, f->win, f->x + f->move_x,
		f->y + f->move_y, f->color);
		tx += 1 / ft_sqrt((dx * dx) + (dy * dy));
	}
}

void	draw_line_par(t_fdf *f, int j, int i)
{
	if (j < f->height - 1)
	{
		f->color = f->map[j][i] > 0 || f->map[j + 1][i] > 0
		? 0x08FEDD : f->color_save;
		f->y2 = f->win_h + (j * f->zoom)
		- (f->deep * f->map[j][i]) * cos(f->rot);
		f->y1 = f->win_h + ((j + 1) * f->zoom)
		- (f->deep * f->map[j + 1][i]) * cos(f->rot);
		f->x2 = f->win_w + (i * f->zoom) * cos(f->rot);
		f->x1 = f->win_w + (i * f->zoom) * cos(f->rot);
		ft_draw_line(f);
	}
	if (i < f->width - 1)
	{
		f->color = f->map[j][i + 1] > 0 || f->map[j][i] > 0
		? 0x08FEDD : f->color_save;
		f->y2 = f->win_h + (j * f->zoom)
		- (f->deep * f->map[j][i]) * cos(f->rot);
		f->y1 = (f->win_h + j * f->zoom)
		- (f->deep * f->map[j][i + 1]) * cos(f->rot);
		f->x2 = f->win_w + (i * f->zoom) * cos(f->rot);
		f->x1 = f->win_w + ((i + 1) * f->zoom) * cos(f->rot);
		ft_draw_line(f);
	}
}

void	draw_line_iso(t_fdf *f, int j, int i)
{
	if (j < f->height - 1)
	{
		f->color = f->map[j][i] > 0 || f->map[j + 1][i] > 0
		? 0x08FEDD : f->color_save;
		f->x1 = f->win_w + (i * f->zoom) + (j * f->zoom);
		f->x2 = f->win_w + (i * f->zoom) + ((j + 1) * f->zoom);
		f->y1 = f->win_h + (((j * f->zoom))) - (((i * f->zoom)
					+ (f->deep * f->map[j][i])));
		f->y2 = f->win_h + ((j + 1) * f->zoom) - (((i * f->zoom)
					+ (f->deep * f->map[j + 1][i])));
		ft_draw_line(f);
	}
	if (i < f->width - 1)
	{
		f->color = f->map[j][i + 1] > 0 || f->map[j][i] > 0
		? 0x08FEDD : f->color_save;
		f->x1 = f->win_w + (i * f->zoom) + (j * f->zoom);
		f->x2 = f->win_w + ((i + 1) * f->zoom) + (j * f->zoom);
		f->y1 = f->win_h + (((j * f->zoom))) - (((i * f->zoom)
					+ (f->deep * f->map[j][i])));
		f->y2 = f->win_h + (j * f->zoom) - ((((i + 1) * f->zoom)
					+ (f->deep * f->map[j][i + 1])));
		ft_draw_line(f);
	}
}

int		ft_draw(t_fdf *f)
{
	int	i;
	int	j;

	j = 0;
	while (j < f->height)
	{
		i = 0;
		while (i < f->width)
			f->iso == 1 ? draw_line_iso(f, j, i++) : draw_line_par(f, j, i++);
		j++;
	}
	return (0);
}

int		ft_draw_all(t_fdf *f)
{
	f->deep = 1;
	f->move_x = 0;
	f->move_y = 0;
	f->rot = 0;
	f->iso = 0;
	f->color = 0xFFFFFF;
	f->color_save = 0xFFFFFF;
	f->zoom = f->width > 50 ? 4 : 15;
	f->win_width = f->width * 50 > 1000 ? 1000 : f->width * 50;
	f->win_height = f->height * 50 > 1000 ? 1000 : f->height * 50;
	f->win_width = f->win_width < 400 ? 400 : f->win_width;
	f->win_height = f->win_height < 450 ? 450 : f->win_height;
	f->win_w = f->win_width / 2 - (f->width * f->zoom) / 2;
	f->win_h = f->win_height / 2 - (f->height * f->zoom) / 2;
	f->mlx = mlx_init();
	f->win = mlx_new_window(f->mlx, f->win_width, f->win_height, "fdf");
	mlx_expose_hook(f->win, &ft_redraw, f);
	mlx_key_hook(f->win, &mod_img, f);
	mlx_loop(f->mlx);
	return (0);
}

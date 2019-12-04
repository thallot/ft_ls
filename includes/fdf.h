/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 14:15:57 by thallot           #+#    #+#             */
/*   Updated: 2019/07/16 14:52:01 by thallot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../libft/libft.h"
# include "../libft/get_next_line.h"
# include <math.h>
# include <fcntl.h>
# include <errno.h>
# include <mlx.h>

typedef struct	s_fdf
{
	int			error;
	int			color;
	int			color_save;
	int			**map;
	int			win_h;
	int			win_w;
	int			height;
	int			width;
	int			win_height;
	int			win_width;
	int			zoom;
	int			move_x;
	int			move_y;
	int			iso;
	double		rot;
	double		deep;
	double		x;
	double		y;
	double		x1;
	double		x2;
	double		y1;
	double		y2;
	void		*mlx;
	void		*win;
}				t_fdf;

/*
********************************* Parser ***************************************
*/
int				check_line(char *str);
char			*make_str(char **av);
char			**make_tab(char *str);
t_fdf			*make_map(char **tab, t_fdf *fdf, int i, int j);
t_fdf			*init_fdf(char **tab, t_fdf *fdf, int i, int j);
/*
********************************* Draw *****************************************
*/
int				ft_draw(t_fdf *f);
int				ft_draw_all(t_fdf *fdf);
void			draw_line_iso(t_fdf *f, int j, int i);
void			draw_line_par(t_fdf *f, int j, int i);
void			ft_draw_line(t_fdf *f);
/*
******************************* Keyboard ***************************************
*/
int				mod_img(int keycode, t_fdf *f);
int				mod_color(int keycode, t_fdf *fdf);
int				mod_graph(int keycode, t_fdf *f);
int				ft_redraw(t_fdf *f);
long int		atoli(const char *str);
/*
******************************* Free *******************************************
*/
void			free_tab(char **tab);
void			free_tab_int(int **tab, int size);
int				check_file(char **argv);

#endif

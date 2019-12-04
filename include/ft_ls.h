/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 11:11:18 by thallot           #+#    #+#             */
/*   Updated: 2019/10/30 16:26:09 by thallot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H
# include <string.h>
# include <stdlib.h>
# include <sys/types.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>
# include <sys/xattr.h>
# include <sys/acl.h>
# include <sys/ioctl.h>
# include "../lib/libft/libft.h"
# include "../lib/printf/includes/ft_printf.h"
# define DIRECTORY 4
# define FILE 8
# define OPTIONS "Ralrtgf1"

/*
******************************** Structures ************************************
*/

typedef struct				s_elem
{
	struct s_elem		*next;
	struct s_elem		*head;
	struct s_elem		*rep;
	struct stat			*filestat;
	struct dirent		*file;
	struct s_len		*len;
	int					acl;
	char				readlink[1024];
	char				*user;
	char				*group;
	char				*name;
	char				*path;
	DIR					*dir;
	int					type;
	int					is_stat;
	int					hidden;
	size_t				attr;
	char				*min;
	char				*max;
}							t_elem;

typedef struct				s_lst
{
	char			*name;
	struct s_lst	*next;
}							t_lst;

typedef struct				s_args
{
	struct s_lst		*list;
	size_t				w_len;
	size_t				deep;
	char				*path;
	short int			file;
	short int			error;
	short int			rec;
	short int			r;
	short int			l;
	short int			a;
	short int			t;
	short int			g;
	short int			f;
	short int			one;
	short int			len;
}							t_args;

typedef struct				s_len
{
	size_t				nbr_column;
	size_t				nbr_elem;
	size_t				nbr_elem_hidden;
	size_t				name;
	size_t				link;
	size_t				user;
	size_t				group;
	size_t				size;
	size_t				total;
	size_t				chars;
	size_t				mod;
	size_t				elem;
}							t_len;

/*
******************************** Functions *************************************
*/

t_elem						*get_elem(t_args *args, t_elem *elem,
							DIR *rep, char *path);
int							is_link(t_elem *elem);
t_elem						*add_elem(t_args *args, t_elem *elem,
							struct dirent *ptr);
char						*strjoinfree(char *s1, char *s2, int opt);
int							parsing(t_args *args, char **av, int ac);
void						set_option(char c, t_args *args);
void						close_parsing(t_args *args);
int							is_option(char *str);
void						print_elem(t_args *args, t_elem *list);
t_elem						*swap_elem(t_elem *ptr1, t_elem *ptr2);
void						sort_list(t_args *args, t_elem **elem, int count);
void						sort_time(t_args *args, t_elem **elem, int count);
void						sort_args(t_lst **list, int count);
t_lst						*swap_args(t_lst *ptr1, t_lst *ptr2);
void						set_len(t_args *args, t_elem *elem,
							t_elem *head, t_len *len);
void						set_stat(t_args *args, t_elem *elem, t_elem *head);
void						set_len_char(t_args *args, t_elem *elem,
							t_elem *head);
void						set_len_size(t_args *args, t_elem *elem,
							t_elem *head);
void						set_elem(t_elem **head, t_elem *elem,
							t_len *len, char *path);
void						set_len_minor(t_args *args, t_elem *elem,
							t_elem *head);
int							recusiv_condition(t_args *args, t_elem *elem);
void						print_access(t_elem *elem);
void						print_info(t_args *args, t_elem *elem,
							t_len *len);
void						free_tab(char **tab, int size);
void						free_all(t_args *args, t_elem *elem);
int							list_delete(t_args *args, t_elem **elem);
void						elem_delete(t_args *args, t_elem **elem);
void						free_exit(t_args *args);
char						*strjoinfree(char *s1, char *s2, int opt);
void						go_next(t_args *args);
int							is_valid_option(char c, char *str);
t_lst						*add_list(t_lst **list, char *name);
int							sort_time_condition(t_args *args,
							t_elem *p1, t_elem *p2);
char						**create_tab(t_elem *elem, t_args *args,
							int elem_size);
t_len						*set_column(t_args *args, t_len *len);
void						print_tab(t_len *len, char **tab,
							t_elem *elem, size_t i);
void						print_recursive(t_args *args, t_elem *list,
							t_len *len);
void						print_elem_recursive(t_elem *elem,
							t_args *args);
void						get_name(t_args *args, t_elem *elem);
void						init_args(t_args *args);
int							ft_pow_int(int nb, int pow);
char						*ft_itoa_base_int(int base, int value);

void						mergesort_elem(t_args *args, t_elem **headref,
							int time);
t_elem						*sortedmerge(t_args *args, t_elem *a, t_elem *b);
void						frontbacksplit(t_elem *source,
							t_elem **frontref, t_elem **backref);
t_elem						*sortedmerge_time(t_args *args, t_elem *a,
							t_elem *b);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 17:42:58 by thallot           #+#    #+#             */
/*   Updated: 2019/04/17 16:40:02 by thallot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <limits.h>
# define BUFF_SIZE 32

typedef struct			s_gnl
{
	char				*str;
	int					fd;
}						t_file;

int						get_next_line(const int fd, char **line);

#endif

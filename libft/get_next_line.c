/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 17:42:19 by thallot           #+#    #+#             */
/*   Updated: 2019/04/22 10:37:48 by thallot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char		*ft_read_line(int fd, char *str)
{
	char		buffer[BUFF_SIZE + 1];
	char		*tmp;
	int			cursor;

	cursor = 1;
	while (cursor > 0)
	{
		if ((cursor = read(fd, buffer, BUFF_SIZE)) == -1)
			return (NULL);
		buffer[cursor] = '\0';
		tmp = str;
		str = ft_strjoin(str, buffer);
		ft_memdel((void **)&tmp);
		if ((cursor == 0 && ft_strlen(buffer) == 0) || ft_strchr(buffer, '\n'))
			break ;
	}
	return (str);
}

static char		*ft_cut_line(char *str, char *tmp)
{
	char		*ptr;

	ptr = str;
	str = ft_strsub(str, ft_strlen(tmp) + 1, ft_strlen(str) - ft_strlen(tmp));
	ft_memdel((void **)&ptr);
	return (str);
}

static int		ft_create_save(t_file **file, int index)
{
	if (!file[index])
	{
		if (!(file[index] = (t_file *)malloc(sizeof(t_file))))
			return (-1);
		file[index]->str = ft_strnew(0);
		file[index]->fd = index;
	}
	return (1);
}

int				get_next_line(const int fd, char **line)
{
	static t_file	*file[OPEN_MAX];
	size_t			size;

	size = 0;
	if (fd < 0 || line == NULL || fd > OPEN_MAX)
		return (-1);
	if (ft_create_save(file, fd) == -1)
		return (-1);
	if (!file[fd]->str)
		file[fd]->str = ft_strnew(0);
	if ((file[fd]->str = ft_read_line(fd, file[fd]->str)) == NULL)
		return (-1);
	while (file[fd]->str[size] != '\n' && file[fd]->str[size] != '\0')
		size++;
	*line = ft_strsub(file[fd]->str, 0, size);
	if (file[fd]->str[0] == '\0' && *line[0] == '\0')
		return (0);
	file[fd]->str = ft_cut_line(file[fd]->str, *line);
	return (1);
}

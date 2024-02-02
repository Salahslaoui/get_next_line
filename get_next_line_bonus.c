/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sslaoui <sslaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 22:45:00 by sslaoui           #+#    #+#             */
/*   Updated: 2024/02/02 01:30:43 by sslaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_get_line(char **static_var)
{
	char	*tmp;
	char	*line;
	int		i;

	i = ft_strchr(*static_var, '\n') - *static_var;
	line = malloc(i + 2);
	if (!line)
	{
		if (*static_var)
			return (free(*static_var), *static_var = NULL, NULL);
		return (NULL);
	}
	i = 0;
	while ((*static_var)[i] != '\n')
	{
		line[i] = (*static_var)[i];
		i++;
	}
	line[i] = '\n';
	line[i + 1] = '\0';
	tmp = *static_var;
	i = ft_strchr(*static_var, '\n') - *static_var;
	*static_var = ft_substr(*static_var, i + 1, ft_strlen(*static_var) - i + 1);
	return (free(tmp), line);
}

int	read_function(int fd, char **static_var)
{
	char	*buffer;
	char	*tmp;
	ssize_t	buffersize;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (free(*static_var), *static_var = NULL, 0);
	buffersize = read(fd, buffer, BUFFER_SIZE);
	buffer[buffersize] = '\0';
	tmp = *static_var;
	*static_var = ft_strjoin(*static_var, buffer);
	free(tmp);
	free(buffer);
	return (buffersize);
}

char	*get_next_line(int fd)
{
	static char	*str[OPEN_MAX];
	char		*buffer;
	char		*t;
	int			count;

	count = 0;
	buffer = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= OPEN_MAX || read(fd, buffer, 0) < 0)
	{
		if (str[fd])
			return (free(str[fd]), str[fd] = NULL);
		return (NULL);
	}
	if (str[fd] && ft_strchr(str[fd], '\n'))
		return (ft_get_line(&str[fd]));
	while (read_function(fd, &str[fd]) && !ft_strchr(str[fd], '\n'))
		count++;
	if (str[fd] && ft_strchr(str[fd], '\n'))
		return (ft_get_line(&str[fd]));
	if (str[fd] && *str[fd])
		return (t = ft_strjoin(str[fd], ""), free(str[fd]), str[fd] = NULL, t);
	t = str[fd];
	str[fd] = NULL;
	return (free(t), str[fd]);
}

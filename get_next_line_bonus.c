/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vflorez <vflorez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 16:43:42 by vflorez           #+#    #+#             */
/*   Updated: 2023/06/28 16:04:34 by vflorez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	static char		*storage[MAX_OPEN];
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (read(fd, 0, 0) < 0)
	{
		if (storage[fd] != NULL)
			return (free(storage[fd]), storage[fd] = NULL, NULL);
		return (NULL);
	}
	storage[fd] = read_join_file(fd, storage[fd]);
	if (!storage[fd])
		return (free(storage[fd]), storage[fd] = NULL, NULL);
	line = get_line_storage(storage[fd]);
	if (!line)
		return (free(storage[fd]), storage[fd] = NULL, NULL);
	storage[fd] = rest_storage(storage[fd]);
	if (!storage[fd])
		return (free(storage[fd]), storage[fd] = NULL, line);
	return (line);
}

char	*read_join_file(int fd, char *storage)
{
	char	*temp_storage;
	int		bytes_read;

	temp_storage = (char *)ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!temp_storage)
		return (free(storage), storage = NULL, NULL);
	bytes_read = 1;
	while (bytes_read && !ft_strchr(storage, '\n'))
	{
		bytes_read = read(fd, temp_storage, BUFFER_SIZE);
		if (bytes_read < 0)
			return (free(storage), storage = NULL,
				free(temp_storage), temp_storage = NULL, NULL);
		temp_storage[bytes_read] = '\0';
		storage = ft_strjoin(storage, temp_storage);
		if (!storage)
			return (free(storage), storage = NULL,
				free(temp_storage), temp_storage = NULL, NULL);
	}
	free(temp_storage);
	temp_storage = NULL;
	return (storage);
}

char	*get_line_storage(char *storage)
{
	char	*line;
	int		i;

	i = 0;
	while (storage[i] && storage[i] != '\n')
		i++;
	if (storage[0] == '\0')
		return (NULL);
	line = (char *)ft_calloc((i + 1 + (storage[i] == '\n')), sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (storage[i] && storage[i] != '\n')
	{
		line[i] = storage[i];
		i++;
	}
	if (storage[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*rest_storage(char *storage)
{
	char	*temp_storage;
	int		i;
	int		j;

	i = 0;
	while (storage[i] && storage[i] != '\n')
		i++;
	if (storage[i] == '\0')
		return (free(storage), storage = NULL, NULL);
	temp_storage = ft_calloc(ft_strlen(storage) - i + 1, sizeof(char));
	if (!temp_storage)
		return (free(storage), storage = NULL, NULL);
	j = 0;
	while (storage[++i])
	{
		temp_storage[j] = storage[i];
		j++;
	}
	temp_storage[j] = '\0';
	free(storage);
	storage = NULL;
	return (temp_storage);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vflorez <vflorez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 15:39:10 by vflorez           #+#    #+#             */
/*   Updated: 2023/07/04 11:21:46 by vflorez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char		*storage;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (read(fd, 0, 0) < 0)
	{
		if (storage != NULL)
			return (free(storage), storage = NULL, NULL);
		return (NULL);
	}
	storage = read_join_file(fd, storage);
	if (!storage)
		return (free(storage), storage = NULL, NULL);
	line = get_line_storage(storage);
	if (!line)
		return (free(storage), storage = NULL, NULL);
	storage = rest_storage(storage);
	if (!storage)
		return (free(storage), storage = NULL, line);
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

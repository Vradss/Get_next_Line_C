/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vflorez <vflorez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 16:43:36 by vflorez           #+#    #+#             */
/*   Updated: 2023/06/28 16:36:57 by vflorez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# ifndef MAX_OPEN
#  define MAX_OPEN 1024
# endif

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <limits.h>

//Get_next_line_bonus_required
char	*get_next_line(int fd);
char	*get_line_storage(char *storage);
char	*read_join_file(int fd, char *storage);
char	*rest_storage(char *storage);

//utils_bonus_required
int		ft_strchr(const char *str, int c);
void	*ft_calloc(size_t num_elements, size_t size);
char	*ft_strjoin(char *s1, char *s2);
size_t	ft_strlen(const char *str);

#endif
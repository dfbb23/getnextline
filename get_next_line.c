/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmoudni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 23:54:03 by abmoudni          #+#    #+#             */
/*   Updated: 2024/12/18 23:54:06 by abmoudni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*extract_line(char **str)
{
	char	*line;
	char	*temp;
	ssize_t	line_pos;

	temp = NULL;
	line_pos = ft_indexchr(*str, '\n');
	if (line_pos >= 0)
	{
		line = ft_substr(*str, 0, line_pos + 1);
		temp = ft_substr(*str, line_pos + 1, ft_strlen(*str) - line_pos - 1);
		free(*str);
		*str = temp;
	}
	else
	{
		line = ft_strdup(*str);
		free(*str);
		*str = NULL;
	}
	return (line);
}

char	*read_line(int fd, char *new, char *buff)
{
	char	*temp;
	ssize_t	n;

	buff[0] = '\0';
	while (!ft_strchr(buff, '\n'))
	{
		n = read(fd, buff, BUFFER_SIZE);
		if (n == -1)
			return (free(buff), free(new), NULL);
		if (n == 0)
			break ;
		buff[n] = '\0';
		if (!new)
			new = ft_strdup(buff);
		else
		{
			temp = ft_strjoin(new, buff);
			free(new);
			new = temp;
		}
	}
	return (free(buff), new);
}

char	*get_next_line(int fd)
{
	static char	*new = NULL;
	char		*line;
	char		*buff;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buff = malloc((size_t)BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	new = read_line(fd, new, buff);
	if (!new || *new == '\0')
	{
		free(new);
		return (NULL);
	}
	line = extract_line(&new);
	if (!line)
	{
		return (NULL);
	}
	return (line);
}
// int	main(void)
// {
// 	char	*line;
// 	int		fd;

// 	fd = open("abde.txt", O_RDONLY);
// 	if (fd < 0)
// 		return (1);
// 	while ((line = get_next_line(fd)))
// 	{
// 		printf("%s", line);
// 		free(line);
// 	}
// 	close(fd);
// 	return (0);
// }
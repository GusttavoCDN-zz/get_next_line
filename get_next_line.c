/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guda-sil@student.42sp.org.br <guda-sil@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 14:02:24 by guda-sil@st       #+#    #+#             */
/*   Updated: 2022/05/09 11:23:39 by guda-sil@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static	void	read_and_store(int fd, char **accumulator, char *buffer);
static	char	*create_line(char **accumulator);
static	void	update_accumulator(char **accumulator, char *new_buffer);

static	size_t	find_nl(const char *str, int c)
{
	size_t	size;

	size = 0;
	while (str[size])
	{
		if ((unsigned char) str[size] == (unsigned char) c)
			return (size);
		size++;
	}
	return (size);
}

char	*get_next_line(int fd)
{
	static char	*accumulator[1024];
	char		*buffer;
	char		*line;

	if (fd < 0 || fd > 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *) malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (buffer == NULL)
		return (NULL);
	read_and_store(fd, &accumulator[fd], buffer);
	line = create_line(&accumulator[fd]);
	free(buffer);
	return (line);
}

static	void	read_and_store(int fd, char **accumulator, char *buffer)
{
	int		readed;

	readed = read(fd, buffer, BUFFER_SIZE);
	if (readed > 0)
	{
		if (*accumulator == NULL)
			*accumulator = ft_strdup("");
		buffer[readed] = '\0';
		update_accumulator(accumulator, ft_strjoin(*accumulator, buffer));
		while (readed > 0 && ft_strchr(buffer, '\n') == NULL)
		{
			readed = read(fd, buffer, BUFFER_SIZE);
			buffer[readed] = '\0';
			update_accumulator(accumulator, ft_strjoin(*accumulator, buffer));
		}
	}
}

static	char	*create_line(char **acc)
{
	char		*str;
	size_t		str_len;

	if (*acc == NULL)
		return (NULL);
	str_len = find_nl(*acc, '\n') + 1;
	str = ft_substr(*acc, 0, str_len);
	update_accumulator(acc, ft_substr(*acc, str_len, ft_strlen(*acc)));
	if (*acc[0] == '\0')
		update_accumulator(acc, NULL);
	return (str);
}

static	void	update_accumulator(char **accumulator, char *new_buffer)
{
	char	*temp;

	temp = *accumulator;
	*accumulator = new_buffer;
	free(temp);
}

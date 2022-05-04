/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guda-sil@student.42sp.org.br <guda-sil@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 14:02:24 by guda-sil@st       #+#    #+#             */
/*   Updated: 2022/05/04 15:46:38 by guda-sil@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static	void	read_and_store(int fd, t_list **acc, char *buffer);
static	void	update_acummulator(char **acc, char *new_value);
static	char	*create_line(t_list **acc);
static	size_t	find_len(const char *string);

char	*get_next_line(int fd)
{
	static t_list	*accumulator = NULL;
	char	*buffer;
	char	*line;

	if (fd < 0 || fd > 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = calloc(BUFFER_SIZE + 1, 1);
	if (buffer == NULL)
		return (NULL);
	read_and_store(fd, &accumulator, buffer);
	free(buffer);
	line = create_line(&accumulator);
	return (line);

}

static	void	read_and_store(int fd, t_list **acc, char *buffer)
{
	int readed;
	t_list *node;

	node = *acc;
	readed = read(fd, buffer, BUFFER_SIZE);
	if (readed > 0)
	{
		if (node == NULL)
		{
			node = (t_list *)malloc(sizeof(t_list));
			ft_lstadd_back(acc, node);
			node->content = ft_strdup("");
		}
		buffer[readed] = '\0';
		update_acummulator(&node->content, ft_strjoin(node->content, buffer));
		while (readed > 0 && !ft_strchr(node->content, '\n'))
		{
			readed = read(fd, buffer, BUFFER_SIZE);
			buffer[readed] = '\0';
			update_acummulator(&node->content, ft_strjoin(node->content, buffer));
		}
	}
}

static	char	*create_line(t_list **acc)
{
	t_list	*node;
	char	*line;
	size_t	len;

	node = *acc;
	if (node->content[0] == '\0')
	{
		free(node->content);
		free(node);
		return (NULL);
	}
	len = find_len(node->content) + 1;
	line = ft_substr(node->content, 0, len);
	node->content = ft_substr(node->content, len, ft_strlen(node->content));

	return (line);
}

static	void	update_acummulator(char **acc, char *new_value)
{
	char *temp;

	temp = *acc;
	*acc = new_value;
	free(temp);
}

static	size_t	find_len(const char *string)
{
	size_t i;

	i = 0;
	while (string[i] != '\0')
	{
		if ((unsigned char)string[i] == (unsigned char) '\n')
			return (i);
		i++;
	}
	return (0);
}

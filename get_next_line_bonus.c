/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guda-sil@student.42sp.org.br <guda-sil@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 14:02:24 by guda-sil@st       #+#    #+#             */
/*   Updated: 2022/05/04 21:52:24 by guda-sil@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static	void	ft_lstadd_back(t_list **lst, t_list *new);
static	void	read_and_store(int fd, t_list **acc, char *buffer);
static	char	*create_line(t_list **acc);

static	size_t	find_len(const char *string)
{
	size_t	i;

	i = 0;
	while (string[i] != '\0')
	{
		if ((unsigned char)string[i] == (unsigned char) '\n')
			return (i);
		i++;
	}
	return (0);
}

char	*get_next_line(int fd)
{
	static t_list	*accumulator = NULL;
	char			*buffer;
	char			*line;

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
	int		readed;
	char	*temp;
	t_list	*node;

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
		temp = node->content;
		node->content = ft_strjoin(node->content, buffer);
		free(temp);
		while (readed > 0 && !ft_strchr(node->content, '\n'))
		{
			readed = read(fd, buffer, BUFFER_SIZE);
			buffer[readed] = '\0';
			temp = node->content;
			node->content = ft_strjoin(node->content, buffer);
			free(temp);
		}
	}
}

static	char	*create_line(t_list **acc)
{
	t_list	*node;
	char	*line;
	size_t	len;
	char	*temp_substring;

	node = *acc;
	if (node->content[0] == '\0')
		return (NULL);
	len = find_len(node->content) + 1;
	line = ft_substr(node->content, 0, len);
	temp_substring = node->content;
	node->content = ft_substr(node->content, len, ft_strlen(node->content));
	free(temp_substring);
	return (line);
}

static	void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*node;

	if ((*lst) == NULL)
		(*lst) = new;
	else
	{
		node = *lst;
		while (node->next != NULL)
			node = node->next;
		node->next = new;
	}
}

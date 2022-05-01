#include "get_next_line.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

#define BUFFER_SIZE 40

int main(void)
{
	int fd;
	char *line;
	int i = 1;
	fd = open("./naruto_speech.txt", O_RDONLY);

	while ((line = get_next_line(fd)) != NULL)
	{
		printf("Line %i >>> %s", i++, line);
		free(line);
	}

	close(fd);
	return (0);
}

char *get_next_line(int fd)
{
	static t_list *storage = NULL;
	char *line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = NULL;
	read_and_store(&storage, fd);
	line = create_line(line, &storage);
	if (line[0] == '\0')
	{
		clean_storage(&storage);
		storage = NULL;
		free(line);
		return (NULL);
	}
	clean_storage(&storage);
	return (line);
}

void clean_storage(t_list **storage)
{
	t_list *last_node;
	t_list *new_storage;
	int j;
	int i;

	i = 0;
	last_node = ft_lst_get_last(*storage);
	while (last_node->content[i] && last_node->content[i] != '\n')
		i++;
	if (last_node->content[i] && last_node->content[i] == '\n')
		i++;
	new_storage = ft_lstnew(ft_strdup(&last_node->content[i]));
	ft_lstclear(storage);
	*storage = new_storage;
}

char *create_line(char *line, t_list **storage)
{
	int length;
	t_list *current_node;
	int i;
	int j;

	j = 0;
	current_node = *storage;
	length = get_line_length(storage);
	line = malloc((length + 1) * sizeof(char));
	if (!line)
		return (NULL);
	while (current_node)
	{
		i = 0;
		while (current_node->content[i] && current_node->content[i] != '\n')
			line[j++] = current_node->content[i++];
		current_node = current_node->next;
	}
	if (length > 0)
		line[j++] = '\n';
	line[j] = '\0';
	return (line);
}

int get_line_length(t_list **storage)
{
	t_list *current_node;
	int i;
	int length;

	length = 0;
	current_node = *storage;
	while (current_node)
	{
		i = 0;
		while (current_node->content[i])
		{
			if (current_node->content[i] == '\n')
			{
				length++;
				return (length);
			}
			i++;
			length++;
		}
		current_node = current_node->next;
	}

	return (length);
}

void read_and_store(t_list **storage, int fd)
{
	int chars_readed;
	char *buffer;

	chars_readed = BUFFER_SIZE;
	while (chars_readed == BUFFER_SIZE && !has_nl((*storage)))
	{
		buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
		if (buffer == NULL)
			return;
		chars_readed = read(fd, buffer, BUFFER_SIZE);
		buffer[chars_readed] = '\0';
		add_content_to_storage(buffer, storage);
		free(buffer);
	}
}

void add_content_to_storage(char *buffer, t_list **storage)
{
	t_list *new_node;
	t_list *current_node;

	new_node = ft_lstnew(ft_strdup(buffer));
	ft_lstadd_back(storage, new_node);
}

int has_nl(t_list *storage)
{
	int i;
	t_list *current_node;

	if (storage == NULL)
		return (0);
	current_node = ft_lst_get_last(storage);
	i = 0;
	while (current_node->content[i])
	{
		if (current_node->content[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

t_list *ft_lst_get_last(t_list *storage)
{
	t_list *node;

	node = storage;
	if (!node)
		return (NULL);
	while (node->next != NULL)
		node = node->next;
	return (node);
}

t_list *ft_lstnew(void *content)
{
	t_list *new_node;

	new_node = (t_list *)malloc(sizeof(t_list));
	if (!new_node)
		return (NULL);
	new_node->content = content;
	new_node->next = NULL;
	return (new_node);
}

char *ft_strdup(const char *s)
{
	size_t i;
	char *string;

	string = (char *)malloc(strlen(s) + sizeof(char));
	if (!string)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		string[i] = s[i];
		i++;
	}
	string[i] = '\0';
	return (string);
}

void ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list *node;

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

void ft_lstclear(t_list **lst)
{
	t_list *node;
	t_list *next_node;

	if (!(*lst))
		return;
	node = (*lst);
	while (node != NULL)
	{
		next_node = node->next;
		free(node->content);
		free(node);
		node = next_node;
	}
	*lst = NULL;
}

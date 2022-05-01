/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guda-sil@student.42sp.org.br <guda-sil@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 10:54:35 by guda-sil@st       #+#    #+#             */
/*   Updated: 2022/05/01 12:51:02 by guda-sil@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

	string = (char *)malloc(ft_strlen(s) + sizeof(char));
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

size_t	ft_strlen(const char *s)
{
	size_t	length;

	length = 0;
	while (s[length] != '\0')
		length++;
	return (length);
}

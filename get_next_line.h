/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guda-sil@student.42sp.org.br <guda-sil@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 10:54:19 by guda-sil@st       #+#    #+#             */
/*   Updated: 2022/05/01 12:19:15 by guda-sil@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# include <unistd.h>

typedef struct s_list
{
	char	*content;
	struct s_list *next;
}	t_list;

/**
 * @brief This functions can read a line from a file descriptor.
 *
 * @param fd The file descriptor to read from.
 * @return The line read. NULL if there is nothing
 * else to read, or an error occured.
 */
char	*get_next_line(int	fd);
void	read_and_store(t_list **storage, int fd);
size_t	ft_strlen(const char *s);
int		has_nl(t_list *storage);
void	add_content_to_storage(char *buffer, t_list **storage);
t_list	*ft_lst_get_last(t_list *storage);
void	ft_lstadd_back(t_list **lst, t_list *new);
t_list	*ft_lstnew(void *content);
char	*ft_strdup(const char *s);
char	*create_line(char *line, t_list **storage);
int		get_line_length(t_list **storage);
void	clean_storage(t_list **storage);
void	ft_lstclear(t_list **lst);

#endif

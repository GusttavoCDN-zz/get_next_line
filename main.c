#include "get_next_line.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

#define BUFFER_SIZE 20

static	void	read_and_store(int fd, char **accumulator, char *buffer);
static	void	update_acummulator(char **acumulator, char *buffer);
static	char* create_line(char **accumulator);

char	*ft_strdup(const char *s)
{
	size_t	i;
	char	*string;

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
size_t	ft_strlen(const char *s)
{
	size_t	length;

	length = 0;
	while (s[length] != '\0')
		length++;
	return (length);
}
char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	str_len;
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	str_len = ft_strlen(s1) + ft_strlen(s2) + 1;
	str = malloc(str_len * sizeof(char));
	if (!str)
		return (NULL);
	ft_strlcat(str, s1, ft_strlen(s1) + 1);
	ft_strlcat(str, s2, str_len);
	return (str);
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	f_len;

	f_len = ft_strlen(dst) + ft_strlen(src);
	i = ft_strlen(dst);
	j = 0;
	if (size > i)
	{
		while (src[j] && i < size - 1)
			dst[i++] = src[j++];
		dst[i] = '\0';
		return (f_len);
	}
	return (ft_strlen(src) + size);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	s_len;
	size_t	substr_len;
	char	*substr;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	substr_len = s_len - (size_t) start;
	if (start > s_len)
		return ((char *) malloc(1 * sizeof(char)));
	if (substr_len > len)
		substr = (char *) malloc((len + 1) * sizeof(char));
	else
		substr = (char *) malloc((substr_len + 1) * sizeof(char));
	if (!substr)
		return (NULL);
	i = 0;
	while (s[start] && len--)
		substr[i++] = s[start++];
	substr[i] = '\0';
	return (substr);
}


static int	ft_find_nl(const char *str)
{
	int	size;

	size = 0;
	while (str[size])
	{
		if ((unsigned char) str[size] == '\n')
			return (size);
		size++;
	}
	return (0);
}


int main(void)
{
	int fd;
	char *line;
	int i = 1;
	fd = open("./test.txt", O_RDONLY);

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
	static char *accumulator = NULL;
	char *buffer;
	char *line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *) malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buffer == NULL)
		return (NULL);
	read_and_store(fd, &accumulator, buffer);
	line = create_line(&accumulator);
	free(buffer);
	return (line);
}

static	void	read_and_store(int fd, char **accumulator, char *buffer)
{
	int readed_bytes;

	readed_bytes = read(fd, buffer, BUFFER_SIZE);
	if (readed_bytes > 0)
	{
		if (*accumulator == NULL)
			*accumulator = ft_strdup("");
		buffer[readed_bytes] = '\0';
		update_acummulator(accumulator, ft_strjoin(*accumulator, buffer));
		while (readed_bytes > 0 && ft_find_nl(buffer) == 0)
		{

			readed_bytes = read(fd, buffer, BUFFER_SIZE);
			buffer[readed_bytes] = '\0';
			update_acummulator(accumulator, ft_strjoin(*accumulator, buffer));
		}
	}
}

static	char* create_line(char **accumulator)
{
	char *new_line;
	int line_len;

	if (*accumulator == NULL)
		return (NULL);
	line_len = ft_find_nl(*accumulator) + 1;
	new_line = ft_substr(*accumulator, 0, line_len);
	update_acummulator(accumulator, ft_substr(*accumulator, line_len, ft_strlen(*accumulator)));
	if (*accumulator[0] == '\0')
		update_acummulator(accumulator, NULL);
	return (new_line);
}

static	void	update_acummulator(char **accumulator, char *new_buffer)
{
	char *temp;
	temp = *accumulator;
	*accumulator = new_buffer;
	free(temp);
}

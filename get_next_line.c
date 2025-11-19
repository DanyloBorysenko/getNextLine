/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danborys <borysenkodanyl@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 17:20:57 by danborys          #+#    #+#             */
/*   Updated: 2025/11/19 16:31:38 by danborys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>
#include <string.h>

char	*read_fd(int fd, char *rem)
{
	ssize_t	bytes_read;
	char	*buff;
	char	*temp;
	
	buff = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	bytes_read = 1;
	while (bytes_read > 0 && ft_strchr(rem, '\n') == NULL)
	{
		bytes_read = read(fd, buff, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buff);
			free(rem);
			return (NULL);
		}
		buff[bytes_read] = '\0';
		temp = rem;
		rem = ft_strjoin(temp, buff);
		free(temp);
	}
	free(buff);
	return (rem);
}

char	*extract_line(char *rem)
{
	size_t	i;
	size_t	j;
	char	*ptr;

	if (*rem == '\0')
		return (NULL);
	i = 0;
	while (rem[i] && rem[i] != '\n')
		i++;
	ptr = malloc(sizeof(char) * (i + 2));
	j = 0;
	while (j < i + 1)
	{
		ptr[j] = rem[j];
		j++;
	}
	ptr[j] = '\0';
	return (ptr);
}

char	*get_next_line(int fd)
{
	static char	*rem = NULL;
	char	*line;
	
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (rem == NULL)
		rem = ft_calloc(1, sizeof(char));
	rem = read_fd(fd, rem);
	if (!rem)
		return (NULL);
	line = extract_line(rem);
	return (line);
}

int	main(void)
{
	char *file = "file.txt";
	char str[100] = "hello";
	size_t len = strlen(str);
	int fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0644);
	write(fd, str, len);
	lseek(fd, 0, SEEK_SET);
	char *result = get_next_line(fd);
	printf("Actual : %s", result);
	close(fd);
	free(result);
	return (0);
}
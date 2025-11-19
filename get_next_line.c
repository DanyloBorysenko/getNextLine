/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danborys <borysenkodanyl@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 17:20:57 by danborys          #+#    #+#             */
/*   Updated: 2025/11/18 20:52:25 by danborys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>
#include <string.h>

char	*get_next_line(int fd)
{
	size_t	s;
	char	buff[1024];
	size_t count = 0;
	char	*ptr;
	size_t	i;

	s = read(fd, buff, 1);
	count += s;
	while (s > 0)
	{
		printf("s == %zu, count = %zu, buff is %s\n", s, count, buff);
		if (buff[count - 1] == '\n')
		{
			printf("s == %zu, count = %zu, buff is %s\n", s, count, buff);
			i = 0;
			ptr = malloc((count + 1) * sizeof(char));
			while (i < count)
			{
				ptr[i] = buff[i];
				i++;
			}
			ptr[i] = '\0';
			return (ptr);
		}
		s = read(fd, buff, 1);
		if (s == 0)
		{
			i = 0;
			ptr = malloc((count + 1) * sizeof(char));
			while (i < count)
			{
				ptr[i] = buff[i];
				i++;
			}
			ptr[i] = '\0';
			return (ptr);
		}
		count += s;
	}
	return (NULL);
}

int	main(void)
{
	char *file = "file.txt";
	char str[100] = "Hello world\n";
	size_t len = strlen(str);
	int fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0644);
	write(fd, str, len);
	lseek(fd, 0, SEEK_SET);
	char *result = get_next_line(fd);
	printf("Actual : %s\n", result);
	close(fd);
	free(result);
	return (0);
}
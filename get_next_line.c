/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danborys <borysenkodanyl@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 17:20:57 by danborys          #+#    #+#             */
/*   Updated: 2025/11/24 10:55:43 by danborys         ###   ########.fr       */
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

char	*extract_line(char *rem, char *del)
{
	if (!del || (*(del + 1) == '\0'))
		return (ft_substr(rem, 0, ft_strlen(rem)));
	return (ft_substr(rem, 0, del - rem + 1));
}

char	*trim_rem(char	*rem, char *del)
{
	size_t	len;
	char	*new_rem;

	if (!del || *(del + 1) == '\0')
	{
		free(rem);
		return (NULL);
	}
	len = ft_strlen(del + 1);
	new_rem = ft_substr(del + 1, 0, len);
	free(rem);
	return (new_rem);
}

char	*get_next_line(int fd)
{
	static char	*rem = NULL;
	char		*line;
	char		*del;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (rem == NULL)
		rem = ft_calloc(1, sizeof(char));
	rem = read_fd(fd, rem);
	if (!rem)
		return (NULL);
	if (*rem == '\0')
	{
		free(rem);
		rem = NULL;
		return (NULL);
	}
	del = ft_strchr(rem, '\n');
	line = extract_line(rem, del);
	rem = trim_rem(rem, del);
	return (line);
}
// int main(void)
// {
// 	//_________________Test 1_____________________
//     printf("Test 1: file contains \"\\n\\n\"\n");
//     char *file = "file.txt";
//     char str[100] = "\n\n";
//     char *result;
//     size_t len = strlen(str);

//     int fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0644);
//     write(fd, str, len);
//     lseek(fd, 0, SEEK_SET);

//     result = get_next_line(fd);
//     printf("Line 1: %s", result);
//     free(result);

//     result = get_next_line(fd);
//     printf("Line 2: %s", result);
//     free(result);

//     result = get_next_line(fd);
//     printf("Line 3: %s\n", result);
//     free(result);
//     close(fd);

// 	//_________________Test 2_____________________
// 	printf("\nTest 2: empty file\n");
// 	fd = open("empty.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
// 	lseek(fd, 0, SEEK_SET);

// 	result = get_next_line(fd);
// 	printf("Result: %s\n", result ? result : "NULL");
// 	free(result);
// 	close(fd);

// 	//_________________Test 3_____________________
// 	printf("\nTest 3: \"Hello World\" (no newline)\n");
// 	fd = open("single_no_nl.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
// 	write(fd, "Hello World", 11);
// 	lseek(fd, 0, SEEK_SET);

// 	result = get_next_line(fd);
// 	printf("Result: %s\n", result);
// 	free(result);

// 	result = get_next_line(fd);
// 	printf("Second call (should be NULL): %s\n", result ? result : "NULL");
// 	close(fd);

// 	// _________________Test 4_____________________
// 	printf("\nTest 4: multiple lines\n");
// 	fd = open("multi.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
// 	write(fd, "A\nB\nC\n", 6);
// 	lseek(fd, 0, SEEK_SET);

// 	for (int i = 1; i <= 4; i++)
// 	{
//     	result = get_next_line(fd);
//     	printf("Line %d: %s", i, result ? result : "NULL\n");
//     	free(result);
// 	}
// 	close(fd);
//     return (0);
// }
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoelman <vpoelman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 21:34:46 by vpoelman          #+#    #+#             */
/*   Updated: 2026/03/16 21:34:46 by vpoelman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

int	is_valid_extension(char *filename, char *extension)
{
	int	filename_len;
	int	extension_len;

	if (!filename)
		return (0);
	filename_len = ft_strlen(filename);
	extension_len = ft_strlen(extension);
	if (filename_len < extension_len)
		return (0);
	return (ft_strcmp(&filename[filename_len - extension_len], extension) == 0);
}

static char	**append_line(char **lines, char *line, int count)
{
	char	**temp;

	temp = malloc(sizeof(char *) * (count + 2));
	if (!temp)
		return (NULL);
	if (lines)
	{
		ft_memcpy(temp, lines, sizeof(char *) * count);
		free(lines);
	}
	temp[count] = line;
	temp[count + 1] = NULL;
	return (temp);
}

char	**read_file_lines(char *filename)
{
	int		fd;
	char	*line;
	char	**lines;
	int		count;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	lines = NULL;
	count = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		lines = append_line(lines, line, count);
		if (!lines)
		{
			free(line);
			close(fd);
			return (NULL);
		}
		count++;
		line = get_next_line(fd);
	}
	close(fd);
	return (lines);
}

int	count_lines(char **lines)
{
	int	count;

	if (!lines)
		return (0);
	count = 0;
	while (lines[count])
		count++;
	return (count);
}

void	free_lines(char **lines)
{
	int	i;

	if (!lines)
		return ;
	i = 0;
	while (lines[i])
	{
		free(lines[i]);
		i++;
	}
	free(lines);
}

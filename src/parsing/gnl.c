/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoelman <vpoelman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 21:34:46 by vpoelman          #+#    #+#             */
/*   Updated: 2026/03/16 21:34:46 by vpoelman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

static int	read_to_buffer(int fd, char *buffer, int *buffer_pos,
		int *buffer_size)
{
	if (*buffer_pos >= *buffer_size)
	{
		*buffer_size = read(fd, buffer, 1023);
		if (*buffer_size <= 0)
			return (0);
		buffer[*buffer_size] = '\0';
		*buffer_pos = 0;
	}
	return (1);
}

static void	process_buffer(char *buffer, int *buffer_pos, char *temp,
		int *line_pos)
{
	if (buffer[*buffer_pos] == '\n')
	{
		(*buffer_pos)++;
		return ;
	}
	if (*line_pos < 1023)
		temp[(*line_pos)++] = buffer[(*buffer_pos)++];
	else
		(*buffer_pos)++;
}

char	*get_next_line(int fd)
{
	static char	buffer[1024];
	static int	buffer_pos = 0;
	static int	buffer_size = 0;
	char		temp[1024];
	int			line_pos;

	line_pos = 0;
	while (1)
	{
		if (!read_to_buffer(fd, buffer, &buffer_pos, &buffer_size))
			break ;
		if (buffer[buffer_pos] == '\n')
		{
			buffer_pos++;
			break ;
		}
		process_buffer(buffer, &buffer_pos, temp, &line_pos);
	}
	if (line_pos == 0 && buffer_size <= 0)
		return (NULL);
	temp[line_pos] = '\0';
	return (ft_strdup(temp));
}

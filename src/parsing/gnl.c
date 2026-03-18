/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoelman <vpoelman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 21:34:46 by vpoelman          #+#    #+#             */
/*   Updated: 2026/03/18 20:52:42 by vpoelman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

static char	*append_char(char *line, char c)
{
	char	buf[2];
	char	*tmp;

	buf[0] = c;
	buf[1] = '\0';
	if (!line)
		tmp = ft_strjoin("", buf);
	else
		tmp = ft_strjoin(line, buf);
	free(line);
	return (tmp);
}

static char	*read_char(int fd, char *line)
{
	char	buf[2];
	int		bytes;

	buf[1] = '\0';
	while (1)
	{
		bytes = read(fd, buf, 1);
		if (bytes < 0)
			return (free(line), NULL);
		if (bytes == 0)
			break ;
		if (buf[0] == '\n')
		{
			if (!line)
				return (ft_strdup(""));
			return (line);
		}
		line = append_char(line, buf[0]);
		if (!line)
			return (NULL);
	}
	return (line);
}

char	*get_next_line(int fd)
{
	if (fd < 0)
		return (NULL);
	return (read_char(fd, NULL));
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoelman <vpoelman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 21:34:46 by vpoelman          #+#    #+#             */
/*   Updated: 2026/03/16 21:34:46 by vpoelman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

static int	load_texture_path(t_game *game, int dir, char *path)
{
	if (game->textures[dir].img.img)
	{
		free(path);
		return (print_error("Duplicate texture definition", game));
	}
	if (load_texture_from_file(game, &game->textures[dir], path) != 0)
	{
		free(path);
		return (1);
	}
	free(path);
	return (0);
}

static int	parse_texture(char *line, t_game *game, int direction)
{
	char	*path;
	int		i;

	i = 0;
	while (line[i] && !ft_isspace(line[i]))
		i++;
	while (line[i] && ft_isspace(line[i]))
		i++;
	if (!line[i])
		return (print_error("Missing texture path", game));
	path = ft_strdup(&line[i]);
	if (!path)
		return (1);
	i = ft_strlen(path) - 1;
	while (i >= 0 && ft_isspace(path[i]))
		path[i--] = '\0';
	return (load_texture_path(game, direction, path));
}

static int	is_texture_id(char *line, char *id)
{
	int	len;

	len = ft_strlen(id);
	if (ft_strncmp(line, id, len) == 0)
	{
		if (ft_isspace(line[len]) || line[len] == '\0')
			return (1);
	}
	return (0);
}

static int	process_line(char *line, t_game *game)
{
	if (is_texture_id(line, "NO"))
		return (parse_texture(line, game, NORTH));
	else if (is_texture_id(line, "SO"))
		return (parse_texture(line, game, SOUTH));
	else if (is_texture_id(line, "WE"))
		return (parse_texture(line, game, WEST));
	else if (is_texture_id(line, "EA"))
		return (parse_texture(line, game, EAST));
	else if (line[0] == 'F' && (ft_isspace(line[1]) || line[1] == '\0'))
		return (parse_color(line, game, 0));
	else if (line[0] == 'C' && (ft_isspace(line[1]) || line[1] == '\0'))
		return (parse_color(line, game, 1));
	else if (line[0] == '1' || line[0] == '0')
		return (2);
	else if (line[0] == 'N' && line[1] != 'O')
		return (2);
	else if (line[0] == 'S' && line[1] != 'O')
		return (2);
	else if (line[0] == 'W' && line[1] != 'E')
		return (2);
	else if (line[0] == 'E' && line[1] != 'A')
		return (2);
	return (print_error("Unknown identifier or header line", game));
}

int	parse_elements(char **lines, t_game *game)
{
	int	i;
	int	j;
	int	ret;

	i = 0;
	while (lines[i])
	{
		j = 0;
		while (lines[i][j] && ft_isspace(lines[i][j]))
			j++;
		if (lines[i][j])
		{
			ret = process_line(&lines[i][j], game);
			if (ret == 1)
				return (1);
			if (ret == 2)
				break ;
		}
		i++;
	}
	return (0);
}

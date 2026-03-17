/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoelman <vpoelman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 21:34:46 by vpoelman          #+#    #+#             */
/*   Updated: 2026/03/16 21:34:46 by vpoelman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

static int	is_texture_or_color(char *line)
{
	int	j;

	j = 0;
	while (line[j] && ft_isspace(line[j]))
		j++;
	if (!line[j])
		return (1);
	if ((line[j] == 'N' && line[j + 1] == 'O') || (line[j] == 'S'
			&& line[j + 1] == 'O')
		|| (line[j] == 'W' && line[j + 1] == 'E')
		|| (line[j] == 'E' && line[j + 1] == 'A'))
		return (1);
	if ((line[j] == 'F' || line[j] == 'C') && (ft_isspace(line[j + 1])
			|| line[j + 1] == '\0'))
		return (1);
	return (0);
}

static int	find_map_start(char **lines)
{
	int	i;
	int	j;

	i = 0;
	while (lines[i])
	{
		j = 0;
		while (lines[i][j] && ft_isspace(lines[i][j]))
			j++;
		if (is_texture_or_color(lines[i]))
		{
			i++;
			continue ;
		}
		if (ft_strchr("01NSEW", lines[i][j]))
			return (i);
		i++;
	}
	return (-1);
}

static int	validate_elements(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (!game->textures[i].img.img)
			return (print_error("Missing texture definition", game));
		i++;
	}
	if (game->floor_color == -1)
		return (print_error("Missing floor color (F)", game));
	if (game->ceiling_color == -1)
		return (print_error("Missing ceiling color (C)", game));
	return (0);
}

static int	process_map_content(t_game *game, char **lines)
{
	int	map_start;

	if (parse_elements(lines, game) != 0)
		return (1);
	if (validate_elements(game) != 0)
		return (1);
	map_start = find_map_start(lines);
	if (map_start == -1)
		return (print_error("No valid map found", game));
	if (parse_map(lines, game, map_start) != 0)
		return (1);
	if (validate_map(game) != 0)
		return (1);
	return (0);
}

int	parse_file(char *filename, t_game *game)
{
	char	**lines;

	if (!is_valid_extension(filename, ".cub"))
		return (print_error("Invalid file extension (must be .cub)", game));
	lines = read_file_lines(filename);
	if (!lines)
		return (print_error("Could not read file", game));
	if (process_map_content(game, lines) != 0)
	{
		free_lines(lines);
		return (1);
	}
	free_lines(lines);
	return (0);
}

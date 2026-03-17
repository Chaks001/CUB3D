/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoelman <vpoelman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 21:34:46 by vpoelman          #+#    #+#             */
/*   Updated: 2026/03/16 21:34:46 by vpoelman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

int	find_max_width(char **lines, int start)
{
	int	max_width;
	int	current_width;
	int	i;

	max_width = 0;
	i = start;
	while (lines[i])
	{
		current_width = ft_strlen(lines[i]);
		if (current_width > max_width)
			max_width = current_width;
		i++;
	}
	return (max_width);
}

static int	print_map_error(t_game *game, char c, int x, int y)
{
	print_error(NULL, game);
	ft_putstr_fd("Invalid character in map '", 2);
	ft_putchar_fd(c, 2);
	ft_putstr_fd("' at line ", 2);
	ft_putnbr_fd(y, 2);
	ft_putstr_fd(" col ", 2);
	ft_putnbr_fd(x, 2);
	ft_putchar_fd('\n', 2);
	return (1);
}

static int	process_map_char(t_game *game, char c, int x, int y)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		if (game->player.x != 0 || game->player.y != 0)
		{
			print_error("Multiple player positions found", game);
			return (1);
		}
		game->player.x = x + 0.5;
		game->player.y = y + 0.5;
		init_player_direction(game, c);
		return (0);
	}
	else if (c != '0' && c != '1' && c != ' ')
		return (print_map_error(game, c, x, y));
	return (0);
}

static int	fill_map_line(t_game *game, char *line, int i)
{
	int	j;

	j = 0;
	while (j < game->map_width && line[j])
	{
		game->map[i][j] = line[j];
		if (process_map_char(game, line[j], j, i) != 0)
			return (1);
		j++;
	}
	return (0);
}

int	parse_map(char **lines, t_game *game, int start)
{
	int	i;
	int	k;
	int	total_lines;

	total_lines = count_lines(lines);
	game->map_width = find_max_width(lines, start);
	game->map_height = total_lines - start;
	game->map = allocate_map(game->map_height, game->map_width);
	if (!game->map)
		return (print_error("Memory allocation failed", game));
	i = 0;
	k = start;
	while (k < total_lines)
	{
		if (fill_map_line(game, lines[k], i) != 0)
			return (1);
		i++;
		k++;
	}
	if (game->player.x == 0 && game->player.y == 0)
		return (print_error("No player position found", game));
	return (0);
}

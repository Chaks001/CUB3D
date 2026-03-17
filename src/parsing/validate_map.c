/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoelman <vpoelman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 21:34:46 by vpoelman          #+#    #+#             */
/*   Updated: 2026/03/16 21:34:46 by vpoelman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

static int	is_valid_position(t_game *game, int x, int y)
{
	if (x < 0 || x >= game->map_width || y < 0 || y >= game->map_height)
		return (0);
	return (1);
}

static int	print_flood_error(t_game *game, char *msg, int x, int y)
{
	print_error(NULL, game);
	ft_putstr_fd(msg, 2);
	ft_putnbr_fd(x, 2);
	ft_putstr_fd(", ", 2);
	ft_putnbr_fd(y, 2);
	ft_putstr_fd(")\n", 2);
	return (1);
}

static int	flood_fill(t_game *game, char **visited, int x, int y)
{
	if (!is_valid_position(game, x, y))
		return (print_flood_error(game, "Flood fill out of bounds at (", x, y));
	if (visited[y][x] == '1' || game->map[y][x] == '1')
		return (0);
	if (game->map[y][x] == ' ')
		return (print_flood_error(game, "Flood fill reached space at (", x, y));
	visited[y][x] = '1';
	if (flood_fill(game, visited, x + 1, y))
		return (1);
	if (flood_fill(game, visited, x - 1, y))
		return (1);
	if (flood_fill(game, visited, x, y + 1))
		return (1);
	if (flood_fill(game, visited, x, y - 1))
		return (1);
	return (0);
}

// static int	check_unreachable(t_game *game, char **visited)
// {
// 	int	x;
// 	int	y;

// 	y = 0;
// 	while (y < game->map_height)
// 	{
// 		x = 0;
// 		while (x < game->map_width)
// 		{
// 			if (game->map[y][x] == '0' && visited[y][x] == '0')
// 			{
// 				if (flood_fill(game, visited, x, y))
// 				{
// 					print_error("Map contains unreachable or open areas", game);
// 					return (1);
// 				}
// 			}
// 			x++;
// 		}
// 		y++;
// 	}
// 	return (0);
// }

int	validate_map(t_game *game)
{
	char	**visited;
	int		px;
	int		py;

	visited = create_visited_map(game);
	if (!visited)
		return (print_error("Memory allocation failed", game));
	px = (int)game->player.x;
	py = (int)game->player.y;
	if (flood_fill(game, visited, px, py))
	{
		print_error("Map is not properly enclosed by walls", game);
		free_visited_map(visited, game->map_height);
		return (1);
	}
	free_visited_map(visited, game->map_height);
	return (0);
}

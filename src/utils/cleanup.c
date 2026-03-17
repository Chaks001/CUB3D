/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoelman <vpoelman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 21:34:46 by vpoelman          #+#    #+#             */
/*   Updated: 2026/03/16 21:34:46 by vpoelman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

void	free_map(char **map)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

static void	free_mlx_resources(t_game *game)
{
	if (game->win && game->mlx)
	{
		mlx_destroy_window(game->mlx, game->win);
		game->win = NULL;
	}
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		game->mlx = NULL;
	}
}

void	cleanup_game(t_game *game)
{
	int	i;

	if (!game)
		return ;
	if (game->img.img && game->mlx)
	{
		mlx_destroy_image(game->mlx, game->img.img);
		game->img.img = NULL;
	}
	i = 0;
	while (i < 4)
	{
		free_texture(game, &game->textures[i]);
		i++;
	}
	free_map(game->map);
	game->map = NULL;
	free_mlx_resources(game);
}

int	close_game(t_game *game)
{
	cleanup_game(game);
	exit(0);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoelman <vpoelman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 21:34:46 by vpoelman          #+#    #+#             */
/*   Updated: 2026/03/16 21:34:46 by vpoelman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

int	init_game(t_game *game)
{
	game->win = mlx_new_window(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3D");
	if (!game->win)
		return (print_error("Window creation failed", game));
	game->img.img = mlx_new_image(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!game->img.img)
		return (print_error("Image creation failed", game));
	game->img.width = WINDOW_WIDTH;
	game->img.height = WINDOW_HEIGHT;
	game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bits_per_pixel,
			&game->img.line_length, &game->img.endian);
	if (load_textures(game) != 0)
		return (1);
	return (0);
}

int	game_loop(t_game *game)
{
	handle_movement(game);
	if (game->has_moved)
	{
		raycasting(game);
		mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
		game->has_moved = 0;
	}
	return (0);
}

void	init_player_direction(t_game *game, char dir)
{
	if (dir == 'N')
	{
		game->player.dir_x = 0;
		game->player.dir_y = -1;
		game->player.plane_x = 0.66;
	}
	else if (dir == 'S')
	{
		game->player.dir_x = 0;
		game->player.dir_y = 1;
		game->player.plane_x = -0.66;
	}
	else if (dir == 'E')
	{
		game->player.dir_x = 1;
		game->player.plane_y = 0.66;
	}
	else
	{
		game->player.dir_x = -1;
		game->player.plane_y = -0.66;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoelman <vpoelman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 21:34:46 by vpoelman          #+#    #+#             */
/*   Updated: 2026/03/16 21:34:46 by vpoelman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

static int	is_wall(t_game *game, double x, double y)
{
	if (x < 0 || x >= game->map_width || y < 0 || y >= game->map_height)
		return (1);
	if (game->map[(int)y][(int)x] == '1' || game->map[(int)y][(int)x] == ' ')
		return (1);
	return (0);
}

static void	rotate_player(t_game *game, double rot_speed)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->player.dir_x;
	game->player.dir_x = game->player.dir_x * cos(rot_speed)
		- game->player.dir_y * sin(rot_speed);
	game->player.dir_y = old_dir_x * sin(rot_speed) + game->player.dir_y
		* cos(rot_speed);
	old_plane_x = game->player.plane_x;
	game->player.plane_x = game->player.plane_x * cos(rot_speed)
		- game->player.plane_y * sin(rot_speed);
	game->player.plane_y = old_plane_x * sin(rot_speed) + game->player.plane_y
		* cos(rot_speed);
}

static void	move_player(t_game *game, double speed)
{
	if (!is_wall(game, game->player.x + game->player.dir_x * speed * MOVE_SPEED,
			game->player.y))
		game->player.x += game->player.dir_x * speed * MOVE_SPEED;
	if (!is_wall(game, game->player.x, game->player.y + game->player.dir_y
			* speed * MOVE_SPEED))
		game->player.y += game->player.dir_y * speed * MOVE_SPEED;
}

static void	move_strafe(t_game *game, double speed)
{
	if (!is_wall(game, game->player.x + game->player.plane_x * speed
			* MOVE_SPEED, game->player.y))
		game->player.x += game->player.plane_x * speed * MOVE_SPEED;
	if (!is_wall(game, game->player.x, game->player.y + game->player.plane_y
			* speed * MOVE_SPEED))
		game->player.y += game->player.plane_y * speed * MOVE_SPEED;
}

void	handle_movement(t_game *game)
{
	if (game->keys.w)
		move_player(game, 1);
	if (game->keys.s)
		move_player(game, -1);
	if (game->keys.a)
		move_strafe(game, -1);
	if (game->keys.d)
		move_strafe(game, 1);
	if (game->keys.left)
		rotate_player(game, -ROT_SPEED);
	if (game->keys.right)
		rotate_player(game, ROT_SPEED);
	if (game->keys.w || game->keys.s || game->keys.a || game->keys.d
		|| game->keys.left || game->keys.right)
		game->has_moved = 1;
}

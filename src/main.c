/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoelman <vpoelman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 21:34:46 by vpoelman          #+#    #+#             */
/*   Updated: 2026/03/16 21:34:46 by vpoelman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

static int	init_game_setup(t_game *game)
{
	ft_memset(game, 0, sizeof(t_game));
	game->floor_color = -1;
	game->ceiling_color = -1;
	game->has_moved = 1;
	game->mlx = mlx_init();
	if (!game->mlx)
		return (print_error("MLX initialization failed", game));
	return (0);
}

static int	start_window(t_game *game)
{
	if (init_game(game) != 0)
		return (1);
	mlx_hook(game->win, 2, 1, &key_press, game);
	mlx_hook(game->win, 3, 2, &key_release, game);
	mlx_loop_hook(game->mlx, &game_loop, game);
	mlx_hook(game->win, 17, 0, &close_game, game);
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		return (print_error("Usage: ./cub3D <map.cub>", NULL));
	if (init_game_setup(&game) != 0)
		return (1);
	if (parse_file(argv[1], &game) != 0)
	{
		cleanup_game(&game);
		return (1);
	}
	if (start_window(&game) != 0)
	{
		cleanup_game(&game);
		return (1);
	}
	mlx_loop(game.mlx);
	cleanup_game(&game);
	return (0);
}

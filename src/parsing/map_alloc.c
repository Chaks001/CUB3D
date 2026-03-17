/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_alloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoelman <vpoelman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 21:34:46 by vpoelman          #+#    #+#             */
/*   Updated: 2026/03/16 21:34:46 by vpoelman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

static char	*alloc_row(int width, char fill)
{
	char	*row;
	int		j;

	row = malloc(sizeof(char) * (width + 1));
	if (!row)
		return (NULL);
	j = 0;
	while (j < width)
	{
		row[j] = fill;
		j++;
	}
	row[width] = '\0';
	return (row);
}

static void	free_partial_map(char **map, int i)
{
	while (--i >= 0)
		free(map[i]);
	free(map);
}

char	**allocate_map(int height, int width)
{
	char	**map;
	int		i;

	map = malloc(sizeof(char *) * (height + 1));
	if (!map)
		return (NULL);
	i = 0;
	while (i < height)
	{
		map[i] = alloc_row(width, ' ');
		if (!map[i])
		{
			free_partial_map(map, i);
			return (NULL);
		}
		i++;
	}
	map[height] = NULL;
	return (map);
}

char	**create_visited_map(t_game *game)
{
	char	**visited;
	int		i;

	visited = malloc(sizeof(char *) * (game->map_height + 1));
	if (!visited)
		return (NULL);
	i = 0;
	while (i < game->map_height)
	{
		visited[i] = alloc_row(game->map_width, '0');
		if (!visited[i])
		{
			free_partial_map(visited, i);
			return (NULL);
		}
		i++;
	}
	visited[game->map_height] = NULL;
	return (visited);
}

void	free_visited_map(char **visited, int height)
{
	int	i;

	i = 0;
	while (i < height)
	{
		free(visited[i]);
		i++;
	}
	free(visited);
}

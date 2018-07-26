/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szheng <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/24 12:25:13 by szheng            #+#    #+#             */
/*   Updated: 2018/07/24 20:27:40 by szheng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
** This function creates an empty map taking in the map length size. It checks
** if the map is allocated, if not it returns NULL. Otherwise, at the end of
** each row a \0 is placed and a '.' for everything else.
*/

char	**emptymap(int const size)
{
	char	**map;
	int		i;
	int		j;

	if (!(map = (char **)malloc(sizeof(char*) * (size + 1))))
		return (NULL);
	map[size] = NULL;
	i = -1;
	while (++i < size)
	{
		if (!(map[i] = (char *)malloc(sizeof(char) * (size + 1))))
			return (NULL);
		map[i][size] = '\0';
	}
	i = -1;
	while (map[++i])
	{
		j = 0;
		while (j < size)
			map[i][j++] = '.';
	}
	return (map);
}

/*
** This function removes a tetromino shape from the map. This is done by taking
** the current shape index and the size of the entire map. To remove the shape,
** all we do is go through the map and replace the specific character at the
** shape index with '.'. So if we are at index 1, we remove all 'B' and replace
** them with '.'.
*/

void	rmshape(char **m, char index, int size)
{
	int i;
	int j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			if (m[i][j] == ('A' + index))
				m[i][j] = '.';
			j++;
		}
		i++;
	}
}

/*
** This is where the algorithm is located for putting the tetrimino shapes into
** the map. We take in each shape separately at the current index, the empty
** map that is being filled, and the map coordinate (where we are on this map).
** A new index i is used for tracking the current shape's location in given
** block string. Example: we take in string "...A..AA..A....." The f locates
** the first appearance of A. The i tracks your current location in the string.
** mc / s calculates the row you are in. For example, if you have a 5x5 map,
** then mc < 25. If mc is 6, then 6/5 means you are at row 1. i/4 - f/4 is the
** absolute distance in height (rows) from the first A to wherever the next
** index A is at. mc/s + i/4 -f/4 needs to be smaller than height of the map,
** else the block doesn't fit. This part test the block one character at a time.
** The / checks the blockstring to rows, likewise the % checks the blockstring
** to columns or width of map.
*/

int		tryshape(char *sp, char **m, int mc)
{
	int i;
	int f;
	int s;

	f = 0;
	s = ft_strlen(m[0]);
	while (sp[f] == '.')
		f++;
	i = 0;
	while (i < 16)
	{
		if (sp[i] != '.')
			if (mc / s + i / 4 - f / 4 >= s ||
				mc % s + i % 4 - f % 4 >= s ||
				m[mc / s + i / 4 - f / 4][mc % s + i % 4 - f % 4] != '.')
				return (0);
		i++;
	}
	i = -1;
	while (sp[++i])
		if (sp[i] != '.')
			m[mc / s + i / 4 - f / 4][mc % s + i % 4 - f % 4] = sp[i];
	return (1);
}

/*
** This function is where recursion happens. We are trying to fit the empty map
** with shapes by calling the tryshape function. We start from top left with
** map coordinates at 0, all the way to the bottom right. The mapsize only
** changes if we tried the shapes and they did not fit at all no matter how we
** move the shapes by changing the map coordinate. However, if the shape fits,
** then we call the trymap function again, but with the next tetrimino.
** If at any time the shape doesn't fit, we backtrack through our shapes and
** remove the previous one and move it along with the changing map coordinate.
*/

int		trymap(char **shapes, char **map, int shapeindex, int shapecount)
{
	int	mapcoor;
	int mapsize;

	mapsize = ft_strlen(map[0]);
	mapcoor = 0;
	while (mapcoor < mapsize * mapsize)
	{
		if (tryshape(shapes[shapeindex], map, mapcoor) == 1)
		{
			if (shapeindex == shapecount - 1 ||
				trymap(shapes, map, shapeindex + 1, shapecount))
				return (1);
			rmshape(map, shapeindex, mapsize);
		}
		mapcoor++;
	}
	return (0);
}

/*
** This function takes in the shapes that are already alphabetized along with
** number of tetriminos. We create a starting empty board size of sqrt(# of
** tetriminos * 4 characters per tetrimino). Then we loop the map while trying
** the pieces out in other functions. If no matter what we run cannot fit the
** tetriminos in the board, then we free the old board and create a bigger empty
** board. We don't exit the loop until a solution is found. This is when we
** break out of the loop. Finally, we print out the solution on the console.
*/

void	solve(char **shapes, int shapecount)
{
	char	**map;
	int		mapsize;
	int		i;

	mapsize = 2;
	while (mapsize * mapsize < shapecount * 4)
		mapsize++;
	while (1)
	{
		map = emptymap(mapsize);
		if (trymap(shapes, map, 0, shapecount))
			break ;
		i = 0;
		while (i < mapsize)
			free(map[i++]);
		free(map);
		map = NULL;
		mapsize++;
	}
	i = 0;
	while (map[i])
		ft_putendl(map[i++]);
}

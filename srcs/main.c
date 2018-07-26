/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcaixeta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/20 15:06:20 by gcaixeta          #+#    #+#             */
/*   Updated: 2018/07/23 13:40:52 by szheng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
** This function tests if the s are valid, that is to say it checks the
** connections that each # have and add them up. The connections are checked on
** the left, right, and top and bottom to see if a # is touching another #.
** As long as there are 6 or 8 connections, then the tetriminos is valid.
*/

int		checktetris(char *block)
{
	int count;
	int i;

	i = 0;
	count = 0;
	while (i < 20)
	{
		if (block[i] == '#')
		{
			if (i >= 1 && block[i - 1] == '#')
				count++;
			if (i < 19 && block[i + 1] == '#')
				count++;
			if (i >= 5 && block[i - 5] == '#')
				count++;
			if (i < 15 && block[i + 5] == '#')
				count++;
		}
		i++;
	}
	if (count == 6 || count == 8)
		return (1);
	return (0);
}

/*
** This function tests if a block is valid. This means the block must contain
** only ., #, and \n. Altogether, the \n must be located in index 4, 9, 14, 19
** and 20. A valid example would be "####\n....\n....\n....\n\n". The function
** makes sure that there is a \n before it goes to another row.
** In the end, it makes sure that there is exactly 4 # which is counted.
*/

int		checkmap(char *block)
{
	int i;
	int j;
	int count;

	i = 0;
	j = 0;
	count = 0;
	while (i < 4)
	{
		while (j < 4)
		{
			if (!(block[i * 5 + j] == '.' || block[i * 5 + j] == '#'))
				return (0);
			if (block[i * 5 + j] == '#')
				count++;
			j++;
		}
		if (block[i * 5 + j] != '\n')
			return (0);
		j = 0;
		i++;
	}
	if (count != 4)
		return (0);
	return (1);
}

/*
** This function test if tetriminos blocks are valid by going through
** each individual ones. This is done by breaking the tetrimino file into blocks
** by copying the indivdual block into a new memory allocated string of size 20.
** There is only a total of 26 tetriminos, so thats the reason for 26. We check
** to see the end of the read file by see if there is a '\0' since we don't know
** how many inputs there would be, but only maximum of 26 tetriminos.
*/

int		is_input_valid(char *buff)
{
	int		i;
	char	*block;

	i = 0;
	block = ft_strnew(20);
	while (i < 26)
	{
		ft_strncpy(block, &(buff[i * 21]), 20);
		if (!checkmap(block) || !checktetris(block))
		{
			free(block);
			return (0);
		}
		i++;
		if (buff[i * 20 + (i - 1)] == '\0')
			break ;
	}
	free(block);
	return (1);
}

/*
** This function takes in the valid tetrimino file and return a 2 dimensional
** array where all the files are converted into different parts. For example,
** all the newlines are disregarded, the dots are still there, and the # are
** transformed into letters starting with A with the first tetrimino. The 2nd
** tetrimino are made of B and so on. Finally, the shapes are counted.
*/

char	**make2darray(char *buff, int *count)
{
	char	**newarray;
	int		i;
	int		j;

	newarray = (char**)ft_memalloc(27 * sizeof(*newarray));
	i = 0;
	while (i < 26)
		newarray[i++] = ft_strnew(16);
	i = 0;
	j = 0;
	while (buff[i])
	{
		if (buff[i] != '\n')
		{
			if (buff[i] == '.')
				newarray[j / 16][j % 16] = '.';
			else
				newarray[j / 16][j % 16] = 'A' + ((j / 16));
			j++;
		}
		i++;
	}
	*count = j / 16;
	return (newarray);
}

/*
** The main checks that there is exactly one input and that the input has a
** name. If not, an error message is printed and the program exit. Otherwise,
** a buffer is created of size 777. Which is an arbitrary size greater than
** 26 tetriminos (the max input) * 21 (characters in a block). The file is
** read and if the reading fails, an error is printed. If the file is valid,
** then we call the functions to validate, then solve the rest.
*/

int		main(int ac, char **av)
{
	int		fd;
	int		ret;
	int		count;
	char	*buff;
	char	**map2solve;

	if (ac != 2 || !av[0])
		ft_puterror("usage: ./fillit <filename> \n");
	buff = ft_strnew(777);
	count = 0;
	if ((fd = open(av[1], O_RDONLY)) >= 0)
	{
		ret = read(fd, buff, 777);
		if (is_input_valid(buff))
		{
			map2solve = make2darray(buff, &count);
			solve(map2solve, count);
		}
		else
			ft_puterror("error");
	}
	else
		ft_puterror("error");
	return (0);
}

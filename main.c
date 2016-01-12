/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 22:54:01 by dmoureu-          #+#    #+#             */
/*   Updated: 2016/01/13 00:27:42 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	readopts(int ac, char **av, char *opts)
{
	int	i;
	const char *args = "lRart";

	i = 1;
	while (i < ac)
	{
		if (*av[i] == '-')
		{
			av[i]++;
			while (strchr(args, *av[i]) && *av[i] != '\0')
				opts[*(av[i]++)] = 1;
			if (*av[i] == '-')
				return (++i);
			if (*av[i] != '\0')
				return (-1);
		}
		else
			return (i);
		i++;
	}
	return (i);
}

int	main(int ac, char **av)
{
	char	*opts = ft_memalloc('z');
	int		firstpath;

	if((firstpath = readopts(ac, av, opts)) < 1)
	{
		puts("badarg");
		return (1);
	}
	printf("first path :%d \n", firstpath);

	if (opts['l'])
		puts("l donne");
	if (opts['r'])
		puts("r donne");
	if (opts['R'])
		puts("R donne");
	if (opts['a'])
		puts("a donne");
	if (opts['t'])
		puts("t donne");
	return (0);
}

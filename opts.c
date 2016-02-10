/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opts.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 22:43:35 by dmoureu-          #+#    #+#             */
/*   Updated: 2016/02/09 17:16:29 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	readoptsargs(char **av, char *opts, int i)
{
	const char	args[6] = {'l', 'R', 'a', 'r', 't', '1'};

	while (strchr(args, *av[i]) && *av[i] != '\0')
		opts[(int)(*av[i]++)] = 1;
	if (*av[i] != '\0')
		error("ls: illegal option -- ", *av[i]);
}

int		readopts(int ac, char **av, char *opts, int i)
{
	while (++i < ac)
	{
		if (*av[i] == '-')
		{
			av[i]++;
			if (*av[i] == '\0')
			{
				ft_putstr("");
				av[i]--;
				return (i);
			}
			if (*av[i] == '-')
			{
				if (*(++av[i]) == '\0')
					return (i + 1);
				else
					error("ft_ls: illegal option -- ", *(--av[i]));
			}
			readoptsargs(av, opts, i);
		}
		else
			return (i);
	}
	return (i);
}

void	viewopts(t_ls *ls)
{
	if (ls->opts['l'])
		puts("l donne");
	if (ls->opts['r'])
		puts("r donne");
	if (ls->opts['R'])
		puts("R donne");
	if (ls->opts['a'])
		puts("a donne");
	if (ls->opts['t'])
		puts("t donne");
}

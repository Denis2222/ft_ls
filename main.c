/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 22:54:01 by dmoureu-          #+#    #+#             */
/*   Updated: 2016/01/27 19:09:30 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	main(int ac, char **av)
{
	t_ls			ls;
	int				firstpath;
	int				i;

	ls.opts = ft_memalloc('z');
	firstpath = readopts(ac, av, ls.opts);
	parseargs(&ls, av, ac, firstpath);
	viewarg(ls.args);

	while (ls.args)
	{
		printf("@");
		listdir(ls.args->path);
		ls.args = ls.args->next;
	}

/*
	if (ls.opts['l'])
		puts("l donne");
	if (ls.opts['r'])
		puts("r donne");
	if (ls.opts['R'])
		puts("R donne");
	if (ls.opts['a'])
		puts("a donne");
	if (ls.opts['t'])
		puts("t donne");
*/

//	sleep(100);
	return (0);
}

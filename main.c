/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 22:54:01 by dmoureu-          #+#    #+#             */
/*   Updated: 2016/02/03 18:26:45 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	main(int ac, char **av)
{
	t_ls	*ls;
	t_arg	*args;

	ls = newls();
	ls->debug = 0;
	parseargs(ls, av, ac);
	readargs(ls->args, ls);
	if (ls->debug && ls->args)
	{
		ft_putstr("#viewargs:[");
		viewarg(ls->args);
		ft_putendl(" ");
	}
	ls->args = sortargs(ls->args, &ft_strasc);
	print_files(ls);
	print_args(ls->args, ls);
	return (0);
}

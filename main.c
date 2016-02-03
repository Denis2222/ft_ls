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

t_arg	*recurse(t_ls *ls)
{
	t_arg	*args;
	t_arg	*begin;
	t_ent	*ent;

	begin = ls->args;
	args = ls->args;
	while (args)
	{
		if (args->ent)
		{
			ent = args->ent;
			sortents(ent, &ft_strasc);
			while (ent)
			{
				if (!ft_strequ(ent->name,".") && !ft_strequ(ent->name,".."))
				{
					if (ent->dirent->d_type == 4)
					{
						ft_putstr(args->path);
						ft_putchar('/');
						ft_putstr(ent->name);
						ft_putchar('\n');
					}
				}
				ent = ent->next;
			}
		}
		args = args->next;
	}
	ls->args = begin;
	return (begin);
}

int	main(int ac, char **av)
{
	t_ls	*ls;
	t_arg	*args;

	ls = newls();
	parseargs(ls, av, ac);
	readargs(ls);
	ls->args = sortargs(ls->args, &ft_strasc);
	if (ls->opts['R'])
		ls->args = recurse(ls);
	print_files(ls);
	print_args(ls);
	return (0);
}

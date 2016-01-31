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
	t_ls	*ls;
	t_arg	*args;
	t_sfile	*files;
	
	ls = newls();
	parseargs(ls, av, ac);
	readargs(ls);
	if (ls->files)
		files = sortfiles(ls->files, &ft_strasc);
	while (files)
	{
		ft_putstr(files->path);
		ft_putchar('\n');
		if (!files->next)
			ft_putchar('\n');
		files = files->next;
	}
	args = sortargs(ls->args, &ft_strasc);
	while (args)
	{
		if (args->ent)
		{
			if (arglen(ls->args) > 1)
			{
				ft_putstr(args->path);
				ft_putstr(":\n");
			}
			sortents(args->ent, &ft_strasc);
			while (args->ent)
			{
				if (args->ent)
				{
					ft_putstr(args->ent->name);
					ft_putchar('\n');
				}
				args->ent = args->ent->next;
			}
			if (args->next)
				ft_putstr("\n");
		}
		args = args->next;
	}
	return (0);
}

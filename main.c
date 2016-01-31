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
	t_arg	*firstarg;

	ls = (t_ls*)malloc(sizeof(t_ls));
	ls->opts = NULL;
	ls->args = NULL;
	ls->nbarg = 0;
	parseargs(ls, av, ac);
	readargs(ls);
	ls->args = sortargs(ls->args, &ft_strasc);
	while (ls->args)
	{
		if (ls->args->ent)
			sortents(ls->args->ent, &ft_strasc);
		while (ls->args->ent)
		{
			ft_putstr("\n result : ");
			if (ls->args->ent)
				ft_putstr(ls->args->ent->name);
			//else
				//ft_putstr(ls.args->path);
			ls->args->ent = ls->args->ent->next;
		}
		ls->args = ls->args->next;
		ft_putstr("\n next \n");
	}

	//viewopts(&ls);
	//sleep(100);
	return (0);
}

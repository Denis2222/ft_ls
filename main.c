/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 22:54:01 by dmoureu-          #+#    #+#             */
/*   Updated: 2016/02/06 14:20:23 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	main(int ac, char **av)
{
	t_ls	*ls;

	ls = newls();
	setupls(ls, av, ac);
	ls->args = sortargs(ls->args, &ft_strdec);
	readfiles(ls->args, ls);
	readargs(ls->args, ls);
	return (0);
}

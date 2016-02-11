/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/10 18:45:31 by dmoureu-          #+#    #+#             */
/*   Updated: 2016/02/10 19:05:16 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	readfiles(t_ls *ls)
{
	t_arg	*arg;

	arg = ls->args;
	while (arg)
	{
		listfiles(arg, ls);
		arg = arg->next;
	}
	if (ls->sort_time && ls->files)
		sortentstime(ls->files, ls->sort_time);
	print_ents(".", ls->files, ls, 0);
}

void	readargs(t_arg *args, t_ls *ls)
{
	t_arg	*arg;

	arg = args;
	while (arg)
	{
		timedir(arg);
		arg = arg->next;
	}
	arg = args;
	if (ls->sort_alpha)
		sortargs(arg, ls->sort_alpha);
	if (ls->sort_time)
		sortargstime(arg, ls->sort_time);
	while (arg)
	{
		listdir(arg, ls);
		print_args(arg, ls);
		if (ls->opts['R'] && arg->sub)
			readargs(arg->sub, ls);
		arg = arg->next;
	}
}

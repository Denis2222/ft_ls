/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/06 12:10:28 by dmoureu-          #+#    #+#             */
/*   Updated: 2016/02/10 22:07:32 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_ents_l(char *path, t_ent *ent, t_column *col, int type)
{
	t_ent	*sent;

	sent = ent;
	seekcolumnsize(ent, path, col);
	if (type)
	{
		ft_putstr("total ");
		ft_putnbr(col->block);
		ft_putendl("");
	}
	ent = sent;
	printcolumns(ent, col, path);
}

void	print_ents(char *path, t_ent *ent, t_ls *ls, int type)
{
	t_column	col;

	col.link = 0;
	col.user = 0;
	col.group = 0;
	col.size = 0;
	col.block = 0;
	if (ent)
	{
		if (!ls->opts['l'])
		{
			while (ent)
			{
				if (type == 0)
					ls->out++;
				ft_putstr(ent->name);
				ft_putchar('\n');
				ent = ent->next;
			}
		}
		else
			print_ents_l(path, ent, &col, type);
	}
}

void	print_arg_ent(t_arg *arg, t_ls *ls)
{
	if (ls->out > 0)
		ft_putendl("");
	if ((arglen(ls->args) > 1 || ls->out > 0))
	{
		ft_putstr(arg->path);
		ft_putstr(":\n");
	}
	if (ls->sort_alpha)
		sortents(arg->ent, ls->sort_alpha);
	if (ls->sort_time)
		sortentstime(arg->ent, ls->sort_time);
	print_ents(arg->path, arg->ent, ls, 1);
}

void	print_arg_deny(t_arg *arg, t_ls *ls)
{
	if (ls->out > 0)
		ft_putendl("");
	if ((arglen(ls->args) > 1 || ls->out > 0))
	{
		ft_putstr(arg->path);
		ft_putstr(":\n");
	}
	ft_putstr_fd("ls:", 2);
	ft_putstr_fd(arg->path, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd("Permission denied", 2);
}

void	print_args(t_arg *args, t_ls *ls)
{
	t_arg *arg;

	arg = args;
	while (arg)
	{
		if (!arg->read)
		{
			if (arg->deny)
				print_arg_deny(arg, ls);
			else if (arg->ent)
				print_arg_ent(arg, ls);
			else if (!arg->empty)
			{
				if (ls->out > 0)
					ft_putendl("");
				if ((arglen(ls->args) > 1 || ls->out > 0))
				{
					ft_putstr(arg->path);
					ft_putstr(":\n");
				}
			}
			if (arg->sub)
				print_args(arg->sub, ls);
			ls->out++;
		}
		arg = arg->next;
	}
}

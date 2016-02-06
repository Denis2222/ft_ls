/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_arg.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/27 17:44:23 by dmoureu-          #+#    #+#             */
/*   Updated: 2016/02/06 17:06:32 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	readfiles(t_arg *args, t_ls *ls)
{
	t_arg	*arg;

	arg = ls->args;
	while (arg)
	{
		listfiles(arg, ls);
		arg = arg->next;
	}
	print_ents(".", ls->files, ls, 0);
}

void	readargs(t_arg *args, t_ls *ls)
{
	t_arg	*arg;

	arg = args;
	sortargs(arg, ls->sort_alpha);
	while (arg)
	{
		listdir(arg, ls);
		print_args(arg, ls);
		if (ls->opts['R'] && arg->sub)
			readargs(arg->sub, ls);
		arg = arg->next;
	}
}

t_arg	*newarg(char *str)
{
	t_arg *arg;

	arg = (t_arg*)malloc(sizeof(t_arg));
	arg->path = str;
	arg->deny = 0;
	arg->mtime = 0;
	arg->empty = 1;
	arg->ent = NULL;
	arg->sub = NULL;
	arg->next = NULL;
	return (arg);
}

t_arg	*addarg(t_arg **lstarg, t_arg *arg)
{
	t_arg	*beginlst;
	t_arg	*current;

	beginlst = *lstarg;
	current = beginlst;
	if (!*lstarg)
		beginlst = arg;
	else
	{
		while (current->next)
			current = current->next;
		current->next = arg;
	}
	return (beginlst);
}

int	arglen(t_arg *arg)
{
	int		length;
	t_arg	*marg;

	marg = arg;
	length = 0;
	while (marg)
	{
		length++;
		marg = marg->next;
	}
	return (length);
}

t_arg	*sortargs(t_arg *lst, int (*cmp)(char *, char *))
{
	t_arg	*tmparg;
	t_ent	*tmpent;
	char	*tmpstr;
	time_t	tmptime;

	tmparg = lst;
	while (tmparg->next)
	{
		if ((*cmp)(tmparg->path, tmparg->next->path) <= 0)
				tmparg = tmparg->next;
			else
			{
				tmpent = tmparg->ent;
				tmpstr = tmparg->path;
				tmptime = tmparg->mtime;
				tmparg->ent = tmparg->next->ent;
				tmparg->path = tmparg->next->path;
				tmparg->mtime = tmparg->next->mtime;
				tmparg->next->ent = tmpent;
				tmparg->next->path = tmpstr;
				tmparg->next->mtime = tmptime;
				tmparg = lst;
			}
	}
	return (lst);
}

t_arg	*sortargstime(t_arg *lst, int (*cmp)(time_t, time_t))
{
	t_arg	*tmparg;
	t_ent	*tmpent;
	char	*tmpstr;
	time_t	tmptime;

	tmparg = lst;
	while (tmparg->next)
	{
		if ((*cmp)(tmparg->mtime, tmparg->next->mtime) <= 0)
				tmparg = tmparg->next;
			else
			{
				tmpent = tmparg->ent;
				tmpstr = tmparg->path;
				tmptime = tmparg->mtime;
				tmparg->ent = tmparg->next->ent;
				tmparg->path = tmparg->next->path;
				tmparg->mtime = tmparg->next->mtime;
				tmparg->next->ent = tmpent;
				tmparg->next->path = tmpstr;
				tmparg->next->mtime = tmptime;
				tmparg = lst;
			}
	}
	return (lst);
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_arg.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/27 17:44:23 by dmoureu-          #+#    #+#             */
/*   Updated: 2016/02/03 17:03:15 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	parseargs(t_ls *ls, char **av, int ac)
{
	int start;

	if (ls->debug)
		ft_putendl("#parseargs");
	ls->opts = ft_memalloc('z');
	start = readopts(ac, av, ls->opts);
	if (start == ac)
		ls->args = addarg(&(ls->args), newarg("."));
	while (start < ac)
	{
		ls->args = addarg(&(ls->args), newarg(av[start]));
		start++;
	}
	ls->nbarg = arglen(ls->args);
}

void	readargs(t_arg *args, t_ls *ls)
{
	t_arg	*arg;

	if (ls->debug)
		ft_putendl("#readargs");
	arg = args;
	while (arg)
	{
		listdir(arg, ls);
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

void	viewarg(t_arg *arg)
{
	t_arg	*marg;
	marg = arg;
	while(marg)
	{
		ft_putstr(marg->path);
		if (marg->sub)
		{
			ft_putstr("$sub:");
			viewarg(marg->sub);
		}
		ft_putchar(' ');
		marg = marg->next;
	}
	ft_putstr("]");
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
		length += arglen(marg->sub);
		marg = marg->next;
	}
	return (length);
}

t_arg	*sortargs(t_arg *lst, int (*cmp)(char *, char *))
{
	t_arg	*tmparg;
	t_ent	*tmpent;
	char	*tmpstr;

	tmparg = lst;
	while (tmparg->next)
	{
		if ((*cmp)(tmparg->path,
			tmparg->next->path) <= 0)
			{
				tmparg = tmparg->next;
			}
			else
			{
				tmpent = tmparg->ent;
				tmpstr = tmparg->path;
				tmparg->ent = tmparg->next->ent;
				tmparg->path = tmparg->next->path;
				tmparg->next->ent = tmpent;
				tmparg->next->path = tmpstr;
				tmparg = lst;
			}
	}
	return (lst);
}

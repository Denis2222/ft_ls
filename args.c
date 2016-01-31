/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_arg.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/27 17:44:23 by dmoureu-          #+#    #+#             */
/*   Updated: 2016/01/27 18:57:50 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	parseargs(t_ls *ls, char **av, int ac)
{
	int start;

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

void	readargs(t_ls *ls)
{
	t_arg	*arg;

	arg = ls->args;
	while (arg)
	{
		listdir(arg, ls);
		arg = arg->next;
	}
}

t_arg	*newarg(char *str)
{
	t_arg *arg;

	arg = (t_arg*)malloc(sizeof(t_arg));
	arg->path = str;
	arg->ent = NULL;
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
		printf("[%s]", marg->path);
		marg = marg->next;
	}
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

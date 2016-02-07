/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorts.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/07 19:04:44 by dmoureu-          #+#    #+#             */
/*   Updated: 2016/02/07 19:08:24 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

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

t_ent	*sortents(t_ent *lst, int (*cmp)(char *, char *))
{
	t_ent	*tmp;
	char	*tmpstr;
	int		time;

	tmp = lst;
	while (tmp->next)
	{
		if ((*cmp)(tmp->name, tmp->next->name) <= 0)
			tmp = tmp->next;
		else
		{
			tmpstr = tmp->name;
			time = tmp->mtime;
			tmp->name = tmp->next->name;
			tmp->mtime = tmp->next->mtime;
			tmp->next->mtime = time;
			tmp->next->name = tmpstr;
			tmp = lst;
		}
	}
	lst = tmp;
	return (lst);
}

t_ent	*sortentstime(t_ent *lst, int (*cmp)(time_t, time_t))
{
	t_ent	*tmp;
	char	*tmpstr;
	int		time;

	tmp = lst;
	while (tmp->next)
	{
		if ((*cmp)(tmp->mtime, tmp->next->mtime) <= 0)
			tmp = tmp->next;
		else
		{
			tmpstr = tmp->name;
			time = tmp->mtime;
			tmp->name = tmp->next->name;
			tmp->mtime = tmp->next->mtime;
			tmp->next->mtime = time;
			tmp->next->name = tmpstr;
			tmp = lst;
		}
	}
	lst = tmp;
	return (lst);
}

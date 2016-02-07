/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ents.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/07 16:28:40 by dmoureu-          #+#    #+#             */
/*   Updated: 2016/02/07 19:08:46 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_ent	*newent(char *name, struct stat *filestat)
{
	t_ent	*ent;

	ent = (t_ent *)malloc(sizeof(t_ent));
	ent->name = ft_strdup(name);
	ent->mtime = filestat->st_mtimespec.tv_sec;
	ent->next = NULL;
	return (ent);
}

t_ent	*addent(t_ent **lstent, t_ent *ent)
{
	t_ent	*beginlst;
	t_ent	*current;

	beginlst = *lstent;
	current = beginlst;
	if (!*lstent)
		beginlst = ent;
	else
	{
		while (current->next)
			current = current->next;
		current->next = ent;
	}
	return (beginlst);
}

int		entlen(t_ent *ent)
{
	int		length;
	t_ent	*ment;

	ment = ent;
	length = 0;
	while (ment)
	{
		length++;
		ment = ment->next;
	}
	return (length);
}

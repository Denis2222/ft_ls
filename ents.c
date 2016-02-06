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

int	entlen(t_ent *ent)
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

t_ent	*sortents(t_ent *lst, int (*cmp)(char *, char *))
{
	t_ent	*tmp;
	char	*tmpstr;
	int		time;

	tmp = lst;
	while  (tmp->next)
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
	while  (tmp->next)
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


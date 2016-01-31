#include "ft_ls.h"

t_ent	*newent(struct dirent *dirent)
{
	t_ent	*ent;

	ent = (t_ent *)malloc(sizeof(t_ent));
	ent->dirent = dirent;
	ent->name = ft_strdup(dirent->d_name);
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

int	ft_strasc(char *s1, char *s2)
{
	int x;

	x = 0;
	while (s1[x] == s2[x] && s1[x] != '\0' && s2[x] != '\0')
		x++;
	return ((unsigned char)s1[x] - (unsigned char)s2[x]);
}

int	ft_strdec(char *s1, char *s2)
{
	int x;

	x = 0;
	while (s1[x] == s2[x] && s1[x] != '\0' && s2[x] != '\0')
		x++;
	return ((unsigned char)s2[x] - (unsigned char)s1[x]);
}

t_ent	*sortents(t_ent *lst, int (*cmp)(char *, char *))
{
	t_ent	*tmp;
	struct dirent *tmpdirent;
	char	*tmpstr;

	tmp = lst;
	while  (tmp->next)
	{
		if ((*cmp)(tmp->name,
			tmp->next->name) <= 0)
			{
				tmp = tmp->next;
			}
			else
			{
				tmpdirent = tmp->dirent;
				tmpstr = tmp->name;

				tmp->dirent = tmp->next->dirent;
				tmp->name = tmp->next->name;
				
				tmp->next->dirent = tmpdirent;
				tmp->next->name = tmpstr;
				
				tmp = lst;
			}
	}
	lst = tmp;
	return (lst);
}

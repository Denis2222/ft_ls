#include "ft_ls.h"

t_ent	*newent(struct dirent *dirent)
{
	t_ent	*ent;

	ent = (t_ent *)malloc(sizeof(t_ent));
	ent->dirent = dirent;
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

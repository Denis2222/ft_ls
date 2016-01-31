#include "ft_ls.h"

t_ls *newls(void)
{
	t_ls *ls;

	ls = (t_ls*)malloc(sizeof(t_ls));
	ls->opts = NULL;
	ls->args = NULL;
	ls->files = NULL;
	ls->nbarg = 0;
	return (ls);
}

#include "ft_ls.h"

void	print_files(t_ls *ls)
{
	t_sfile	*files;

	if (ls->files)
	{
		files = sortfiles(ls->files, &ft_strasc);
		while (files)
		{
			if (files->path)
			{
				ft_putstr(files->path);
				ft_putchar('\n');
				if (!files->next)
					ft_putchar('\n');
				files = files->next;
			}
		}
	}
}

void	print_args(t_arg *args, t_ls *ls)
{
	t_arg *arg;

	arg = args;
	while (arg)
	{
		if (arg->ent)
		{
			if (arglen(ls->args) > 1)
			{
				ft_putstr(arg->path);
				ft_putstr(":\n");
			}
			sortents(arg->ent, &ft_strasc);
			while (arg->ent)
			{
				ft_putstr(arg->ent->name);
				ft_putchar('\n');
				arg->ent = arg->ent->next;
			}
			if (arg->next && arg->next->ent)
				ft_putstr("\n");
		}
		if (arg->sub)
			print_args(arg->sub, ls);
		arg = arg->next;
	}
}

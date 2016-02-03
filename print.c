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

void	print_args(t_ls *ls)
{
	t_arg	*args;

	args = ls->args;
	while (args)
	{
		if (args->ent)
		{
			if (arglen(ls->args) > 1)
			{
				ft_putstr(args->path);
				ft_putstr(":\n");
			}
			sortents(args->ent, &ft_strasc);
			while (args->ent)
			{
				ft_putstr(args->ent->name);
				ft_putchar('\n');
				args->ent = args->ent->next;
			}
			if (args->next && args->next->ent)
				ft_putstr("\n");
		}
		args = args->next;
	}
}

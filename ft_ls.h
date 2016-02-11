/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/08 16:20:12 by dmoureu-          #+#    #+#             */
/*   Updated: 2016/02/10 22:00:21 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <dirent.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <pwd.h>
# include <grp.h>
# include <uuid/uuid.h>
# include <sys/xattr.h>
# include <errno.h>
# include <time.h>
# include "libft/libft.h"

void				error(char *str, char c);
void				erroremptyarg(void);
int					readopts(int ac, char **av, char *opts, int i);

typedef struct		s_column
{
	size_t			link;
	size_t			user;
	size_t			group;
	size_t			size;
	size_t			block;
}					t_column;

typedef struct		s_ent
{
	struct dirent	*dirent;
	char			*name;
	time_t			mtime;
	struct s_ent	*next;
}					t_ent;

typedef struct		s_arg
{
	char			*path;
	t_ent			*ent;
	struct s_arg	*sub;
	time_t			mtime;
	int				read;
	int				empty;
	int				deny;
	struct s_arg	*next;
}					t_arg;

typedef struct		s_ls
{
	char			*opts;
	t_arg			*args;
	t_ent			*files;
	void			*sort_alpha;
	void			*sort_time;
	int				nbarg;
	int				out;
}					t_ls;

t_ls				*newls(void);

t_arg				*newarg(char *str);
t_arg				*addarg(t_arg **lstarg, t_arg *arg);
t_arg				*sortargs(t_arg *lst, int(*cmp)(char *, char *));
void				viewarg(t_arg *arg);
void				setupls(t_ls *ls, char **av, int ac);
void				readargs(t_arg *arg, t_ls *ls);
t_arg				*sortargstime(t_arg *lst, int (*cmp)(time_t, time_t));
void				readfiles(t_ls *ls);
int					arglen(t_arg *arg);

void				listfiles(t_arg *arg, t_ls *ls);
void				listdir(t_arg *arg, t_ls *ls);
void				viewopts(t_ls *ls);

t_ent				*newent(char *name, struct stat *filestat);
t_ent				*addent(t_ent **lstent, t_ent *ent);
t_ent				*sortents(t_ent *ent, int(*cmp)(char *, char *));
t_ent				*sortentstime(t_ent *ent, int(*cmp)(time_t, time_t));
int					entlen(t_ent *ent);

int					ft_strasc(char *s1, char *s2);
int					ft_strdec(char *s1, char *s2);
int					ft_timeasc(time_t s1, time_t s2);
int					ft_timedec(time_t s1, time_t s2);

void				print_args(t_arg *args, t_ls *ls);
void				print_ents(char *path, t_ent *ent, t_ls *ls, int type);
void				ft_putstrn(char *str, int n, int s);

char				mode(mode_t st_mode);
char				*modetostr(mode_t st_mode);

void				timedir(t_arg *arg);

char				*putstrnright(char *newstr, char *str, int n);
void				ft_putstrn(char *str, int n, int s);
void				ctimetols(struct timespec *timespec);
char				*majorminor(dev_t dev);

void				printcolumns(t_ent *ent, t_column *col, char *path);
void				ft_putstrfree(char *str);
void				ft_putstrnfree(char *str, int n, int s);
void				seekcolumnsize(t_ent *ent, char *path, t_column *col);
char				*modetostr(mode_t st_mode);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 22:43:35 by dmoureu-          #+#    #+#             */
/*   Updated: 2016/01/27 19:04:27 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <dirent.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <pwd.h>
# include <uuid/uuid.h>
# include <sys/xattr.h>
# include <time.h>
# include "libft/libft.h"

void error(char *str, char c);
int	readopts(int ac, char **av, char *opts);

typedef struct  s_ent
{
  struct dirent *dirent;
  char          *name;
  struct s_ent  *next;
}               t_ent;

typedef struct  s_sfile
{
  char          *path;
  struct s_sfile *next;
}               t_sfile;

typedef struct  s_arg
{
  char          *path;
  t_ent         *ent;
  struct s_arg  *next;
}               t_arg;

typedef struct  s_ls
{
  char          *opts;
  t_arg         *args;
  t_sfile       *files;
  int           nbarg;
}				t_ls;

t_ls    *newls(void);

t_arg   *newarg(char *str);
t_arg   *addarg(t_arg **lstarg, t_arg *arg);
t_arg	*sortargs(t_arg *lst, int(*cmp)(char *, char *));
void    viewarg(t_arg *arg);
void    parseargs(t_ls *ls, char **av, int ac);
void    readargs(t_ls *ls);
int     arglen(t_arg *arg);

void    listdir(t_arg *arg, t_ls *ls);
void	viewopts(t_ls *ls);

t_ent   *newent(struct dirent *dirent);
t_ent   *addent(t_ent **lstent, t_ent *ent);
t_ent   *sortents(t_ent *ent, int(*cmp)(char *, char *));
int     entlen(t_ent *ent);

t_sfile  *newfile(char *path);
t_sfile  *addfile(t_sfile **lst, t_sfile *file);
t_sfile  *sortfiles(t_sfile *file, int (*cmp)(char *, char *));
int      filelen(t_sfile *file);

int	    ft_strasc(char *s1, char *s2);
int	    ft_strdec(char *s1, char *s2);
#endif

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

typedef struct  s_arg
{
  char          *path;
  struct s_arg  *next;
}               t_arg;

typedef struct  s_ls
{
  char          *opts;
  t_arg         *args;
}				t_ls;

t_arg   *newarg(char *str);
t_arg   *addarg(t_arg **lstarg, t_arg *arg);
void    parseargs(t_ls *ls, char **av, int ac);
void    viewarg(t_arg *arg);
void    listdir(char *dirpath);
void	viewopts(t_ls *ls);

#endif

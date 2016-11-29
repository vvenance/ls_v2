/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvenance <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/22 09:33:29 by vvenance          #+#    #+#             */
/*   Updated: 2016/11/22 09:33:32 by vvenance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H
# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/acl.h>
# include <sys/xattr.h>
# include <dirent.h>
# include <sys/stat.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>
# include <stdarg.h>
# include "./libft/inc/libft.h"
# define NSEC st_mtimespec.tv_nsec
# define SEC st_mtimespec.tv_sec

typedef struct	s_opt
{
	int			l;
	int			br;
	int			a;
	int			r;
	int			t;
	int			n;
	int			o;
	int			index;
}				t_opt;

typedef struct		s_dir
{
	int				disp_name;
	int				disp_total;
	int				total;
	int				maxlk;
	int				maxown;
	int				maxgrp;
	int				maxfsz;
	int				maxmin;
	char			*name;
	char			*path_name;
	char			*strerr;
	struct s_dir	*files;
	struct s_dir	*sdir;
	struct stat		*stat;
	struct passwd	*pswd;
	struct group	*grp;
	struct s_dir	*next;
}					t_dir;

typedef struct s_base
{
	t_dir		*error;
	t_dir		*solo_files;
	t_dir		*dir;
}				t_base;

t_opt	*init_opt(void);
t_dir	*init_dir(char *name, char *path_name);
t_base	*init_base(void);
t_opt	*get_opt(t_opt *opt, char **av, int ac, int i);
void	fts_open(int argc, char **argv);
void	ft_free(int nb, ...);
//void	ft_free(void **p1, void **p2, void **p3, void **p4);
t_base	*get_args(t_opt *opt, char **av, int ac, t_base *base);
void	*ft_stat_dup(void *s, size_t size);
char	*can_be_opened(char *name);
t_dir	*add_dir(char *avi, t_opt *opt, t_dir *dir, struct stat *stat);
t_dir	*add_file(char *avi, t_opt *opt, t_dir *dir, struct stat *stat);
//t_dir	*reverse_sort_t(t_dir *tmp, t_dir *f);
t_dir	*sort_t(t_dir *tmp, t_dir *f, int r);
t_dir	*reverse_sort_a(t_dir *tmp, t_dir *f);
t_dir	*sort_a(t_dir *tmp, t_dir *f, int r);
void	print_error(t_base *base);
void	display(t_base *base, t_opt* opt);
void	print_type(t_dir *files);
void	print_perm(t_dir *file);
void	print_extended(t_dir *dir, t_dir *files);
void	print_links(t_dir *files, t_dir *dir);
void	print_own(t_dir *files, t_dir *dir, t_opt *opt);
void	print_size(t_dir *files, t_dir *dir, int i, int j);
void	print_sym_link(t_dir *files, t_dir *dir, char *buf);
void	print_date(t_dir *files, int j);


t_dir	*reverse_sort_t(t_dir *tmp, t_dir *f);

#endif
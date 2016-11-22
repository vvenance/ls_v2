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
# include "./libft/inc/libft.h"

typedef struct	s_opt
{
	int	l;
	int	br;
	int	a;
	int	r;
	int	t;
	int	n;
	int	o;
	int	index;
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
	t_dir	*errors;
	t_dir	*solo_files;
	t_dir	*dir;
}				t_base;

#endif
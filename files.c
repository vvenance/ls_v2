/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvenance <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/22 14:46:55 by vvenance          #+#    #+#             */
/*   Updated: 2016/11/22 14:46:57 by vvenance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	get_info(t_dir *dir, t_dir *new)
{
	int temp;

	dir->total = dir->total + new->stat->st_blocks;
	dir->maxlk = (dir->maxlk <= new->stat->st_nlink) ? new->stat->st_nlink : dir->maxlk;
	if (S_ISBLK(new->stat->st_mode) || S_ISCHR(new->stat->st_mode))
	{
		temp = major(new->stat->st_rdev);
		dir->maxmin = (dir->maxmin <= temp) ? temp : dir->maxmin;
		temp = minor(new->stat->st_rdev);
		dir->maxfsz = (dir->maxfsz <= temp) ? temp : dir->maxfsz;
	}
	else
		dir->maxfsz = (dir->maxfsz <= new->stat->st_size) ? new->stat->st_size : dir->maxfsz;
	if (new->pswd)
	{
		if ((int)ft_strlen(new->pswd->pw_name) > dir->maxown)
			dir->maxown = (int)ft_strlen(new->pswd->pw_name);
	}
	if (new->grp)
	{
		if ((int)ft_strlen(new->grp->gr_name) > dir->maxgrp)
			dir->maxgrp = (int)ft_strlen(new->grp->gr_name);
	}
}

t_dir	*add_file(char *avi, t_opt *opt, t_dir *dir, struct stat *stat)
{
	t_dir	*new;
	int		r;

	new = init_dir(avi, NULL);
	if (opt->l || opt->t || opt->n || opt->o)
		new->stat = ft_stat_dup(stat, sizeof(struct stat));
	if (opt->l || opt->n || opt->o)
	{
		new->pswd = getpwuid(stat->st_uid);
		new->grp = getgrgid(stat->st_gid);
	}
	r = (opt->r == 1) ? 1 : 0;
	if (opt->t)
		dir->files = sort_t(new, dir->files, r);
	else
		dir->files = sort_a(new, dir->files, r);
	if (opt->l || opt->n || opt->o)
		get_info(dir, new);
	return (dir->files);
}

static t_dir	*add_f_err(t_dir *dir, char *path_name, char *dname, t_opt *opt)
{
	t_dir		*new;
	char		*tmp;
	struct stat	stat;
	int			r;

	new = NULL;
	lstat(path_name, &stat);
	new = init_dir(dname, path_name);
	new->stat = ft_stat_dup(&stat, sizeof(struct stat));
	new->name = ft_strdup(path_name);
	tmp = can_be_opened(path_name);
	new->strerr = ft_strjoin("ls: ", dname);
	new->strerr = ft_strjoin_free(new->strerr, ": ");
	new->strerr = ft_strjoin_free(new->strerr, tmp);
	if (!(dir))
		return (new);
	new->disp_total = (opt->l) ? 1 : 0;
	r = (opt->r == 1) ? 1 : 0;
	if (opt->t == 1)
		return (sort_t(new, dir, r));
	return (sort_a(new, dir, r));
}

static void	while_dir(t_dir *new, struct dirent *read_file, t_opt *opt)
{
	char		*path_name;
	struct stat	stat;
	char		*strerr;

	path_name = ft_strjoin(new->name, "/");
	path_name = ft_strjoin_free(path_name, read_file->d_name);
	new->path_name = ft_strdup(path_name);
	lstat(path_name, &stat);
	if (opt->a == 0 && read_file->d_name[0] == '.')
		;
	else
	{
		new->files = add_file(read_file->d_name, opt, new, &stat);
		if (S_ISDIR(stat.st_mode) && opt->br == 1 && (ft_strcmp(read_file->d_name, "."))
			&& (ft_strcmp(read_file->d_name, "..")))
		{
			strerr = NULL;
			if (!(strerr = can_be_opened(path_name)))
				new->sdir = add_dir(path_name, opt, new->sdir, &stat);
			else
				new->sdir = add_f_err(new->sdir, path_name, read_file->d_name, opt);
			ft_free((void **)&strerr, NULL, NULL, NULL);
		}
	}
	ft_free((void **)&path_name, NULL, NULL, NULL);
}

t_dir	*add_dir(char *avi, t_opt *opt, t_dir *dir, struct stat *stat)
{
	t_dir			*new;
	DIR				*ptr;
	struct dirent	*read_file;
	int				r;

	new = NULL;
	new = init_dir(avi, NULL);
	if (opt->l || opt->t || opt->n || opt->o)
		new->stat = ft_stat_dup(stat, sizeof(struct stat));
	ptr = NULL;
	ptr = opendir(new->name);
	while (ptr && ((read_file = readdir(ptr)) != NULL))
		while_dir(new, read_file, opt);
	if (ptr)
		closedir(ptr);
	new->disp_total = (opt->l) ? 1 : 0;
	r = (opt->r == 1) ? 1 : 0;
	if (opt->t == 1)
		return (sort_t(new, dir, r));
	return (sort_a(new, dir, r));
}
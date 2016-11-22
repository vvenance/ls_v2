/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvenance <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/22 10:55:05 by vvenance          #+#    #+#             */
/*   Updated: 2016/11/22 10:55:10 by vvenance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_opt	*init_opt(void)
{
	t_opt *opt;

	if (!(opt = malloc(sizeof(t_opt))))
		return (NULL);
	opt->l = 0;
	opt->br = 0;
	opt->a = 0;
	opt->r = 0;
	opt->t = 0;
	opt->n = 0;
	opt->o = 0;
	opt->index = 0;
	return (opt);
}

t_dir	*init_dir(char *name, char *path_name)
{
	t_dir *dir;

	if (!(dir = malloc(sizeof(t_dir))))
		return (NULL);
	dir->disp_name = 1;
	dir->disp_total = 0;
	dir->total = 0;
	dir->maxlk = 0;
	dir->maxown = 0;
	dir->maxgrp = 0;
	dir->maxfsz = 0;
	dir->maxmin = 0;
	dir->name = ft_strdup(name);
	dir->path_name = NULL;
	if (path_name)
		dir->path_name = ft_strdup(path_name);
	dir->strerr = NULL;
	dir->files = NULL;
	dir->sdir = NULL;
	dir->stat = NULL;
	dir->pswd = NULL;
	dir->grp = NULL;
	dir->next = NULL;
	return (dir);
}

t_base	*init_base(void)
{
	t_base	*base;

	if (!(base = malloc(sizeof(t_base))))
		return (NULL);
	base->errors = NULL;
	base->solo_files = NULL;
	base->dir = NULL;
	return (base);
}
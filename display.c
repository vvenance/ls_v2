/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvenance <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 13:13:05 by vvenance          #+#    #+#             */
/*   Updated: 2016/11/23 13:13:07 by vvenance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_type(t_dir *files)
{
	if (S_ISBLK(files->stat->st_mode))
		ft_putchar('b');
	else if (S_ISCHR(files->stat->st_mode))
		ft_putchar('c');
	else if (S_ISDIR(files->stat->st_mode))
		ft_putchar('d');
	else if (S_ISLNK(files->stat->st_mode))
		ft_putchar('l');
	else if (S_ISSOCK(files->stat->st_mode))
		ft_putchar('s');
	else if (S_ISFIFO(files->stat->st_mode))
		ft_putchar('p');
	else if (S_ISREG(files->stat->st_mode))
		ft_putchar('-');
}

static void	print_p_other(t_dir *file)
{
	char c;

	c = (file->stat->st_mode & S_IROTH) ? 'r' : '-';
	ft_putchar(c);
	c = (file->stat->st_mode & S_IWOTH) ? 'w' : '-';
	ft_putchar(c);
	if (file->stat->st_mode & S_IXOTH)
	{
		c = (file->stat->st_mode & S_ISVTX) ? 't' : 'x';
		ft_putchar(c);
	}
	else if (!(file->stat->st_mode & S_IXOTH) && file->stat->st_mode & S_ISVTX)
		ft_putchar('T');
	else
		ft_putchar('-');
}

static void	print_p_group(t_dir *file)
{
	char c;

	c = (file->stat->st_mode & S_IRGRP) ? 'r' : '-';
	ft_putchar(c);
	c = (file->stat->st_mode & S_IWGRP) ? 'w' : '-';
	ft_putchar(c);
	if (file->stat->st_mode & S_IXGRP)
	{
		c = (file->stat->st_mode & S_ISGID) ? 's' : 'x';
		ft_putchar(c);
	}
	else if (!(file->stat->st_mode & S_IXGRP) && file->stat->st_mode & S_ISGID)
		ft_putchar('S');
	else
		ft_putchar('-');
	print_p_other(file);
}

void	print_perm(t_dir *file)
{
	char c;

	c = (file->stat->st_mode & S_IRUSR) ? 'r' : '-';
	ft_putchar(c);
	c = (file->stat->st_mode & S_IWUSR) ? 'w' : '-';
	ft_putchar(c);
	if (file->stat->st_mode & S_IXUSR)
	{
		c = (file->stat->st_mode & S_ISUID) ? 's' : 'x';
		ft_putchar(c);
	}
	else if (!(file->stat->st_mode & S_IXUSR) && file->stat->st_mode & S_ISUID)
		ft_putchar('S');
	else
		ft_putchar('-');
	print_p_group(file);
}

void		print_extended(t_dir *dir, t_dir *files)
{
	char	*str;
	acl_t	acl;
	int		ret;

	str = ft_strjoin(dir->name, files->name);
	acl = acl_get_file(str, ACL_TYPE_EXTENDED);
	ret = listxattr(str, NULL, 0, XATTR_NOFOLLOW);
	if (ret > 0)
		ft_putchar('@');
	else if (acl)
	{
		ft_putchar('+');
		acl_free(acl);
	}
	else
		ft_putchar(' ');
	//ft_free(str, NULL);
	ft_putchar(' ');
}
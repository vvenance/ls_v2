/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvenance <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/22 10:54:50 by vvenance          #+#    #+#             */
/*   Updated: 2016/11/22 10:54:52 by vvenance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	main(int ac, char **av)
{
	t_base	*base;
	t_opt	*opt;

	opt = init_opt();
	base = init_base();
	if (!(opt = get_opt(opt, av, ac, 1)))
		return (0);
	fts_open(ac, av);
	base = get_args(opt, av, ac, base);
	ft_free(opt, base, NULL, NULL);
	return (0);
}
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

void	print_opt(t_opt *opt)
{
	printf("l = %d, br = %d, a = %d, r = %d, t = %d, n = %d, o = %d, index = %d\n", opt->l, opt->br, opt->a, opt->r, opt->t, opt->n, opt->o, opt->index);
}

int	main(int ac, char **av)
{
	t_base	*base;
	t_opt	*opt;

	opt = init_opt();
	base = init_base();
	if (!(opt = get_opt(opt, av, ac, 1)))
		return (0);
	print_opt(opt);
	free((void *)(opt));
	free((void *)(base));
	return (1);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comparators.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgleason <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/18 20:22:32 by cgleason          #+#    #+#             */
/*   Updated: 2018/08/18 20:22:41 by cgleason         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

int		fd_cmp_f(void *e1, void *e2)
{
	t_fdata	*tmp1;
	t_fdata	*tmp2;

	tmp1 = (t_fdata *)e1;
	tmp2 = (t_fdata *)e2;
	return (ft_strcmp(tmp1->name, tmp2->name));
}

int		fd_cmp_r(void *e1, void *e2)
{
	t_fdata	*tmp1;
	t_fdata	*tmp2;

	tmp1 = (t_fdata *)e1;
	tmp2 = (t_fdata *)e2;
	return (ft_strcmp(tmp2->name, tmp1->name));
}

int		fd_cmp_ft(void *e1, void *e2)
{
	t_fdata	*tmp1;
	t_fdata	*tmp2;

	tmp1 = (t_fdata *)e1;
	tmp2 = (t_fdata *)e2;
	if (tmp1->acc_time < tmp2->acc_time)
		return (1);
	else if (tmp1->acc_time > tmp2->acc_time)
		return (-1);
	if (tmp1->nsec == tmp2->nsec)
		return (ft_strcmp(tmp1->name, tmp2->name));
	return (tmp2->nsec - tmp1->nsec);
}

int		fd_cmp_rt(void *e1, void *e2)
{
	t_fdata	*tmp1;
	t_fdata	*tmp2;

	tmp1 = (t_fdata *)e1;
	tmp2 = (t_fdata *)e2;
	if (tmp1->acc_time < tmp2->acc_time)
		return (-1);
	else if (tmp1->acc_time > tmp2->acc_time)
		return (1);
	if (tmp1->nsec == tmp2->nsec)
		return (ft_strcmp(tmp2->name, tmp1->name));
	return (tmp1->nsec - tmp2->nsec);
}

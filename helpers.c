/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgleason <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/19 17:35:50 by cgleason          #+#    #+#             */
/*   Updated: 2018/08/19 17:35:58 by cgleason         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void			print_usage(void)
{
	ft_putendl("usage: ./ft_ls [-lRart] [file ...]");
	exit(1);
}

char			ft_1chr_ftype(mode_t mode)
{
	if (S_ISBLK(mode))
		return ('b');
	else if (S_ISCHR(mode))
		return ('c');
	else if (S_ISDIR(mode))
		return ('d');
	else if (S_ISFIFO(mode))
		return ('p');
	else if (S_ISREG(mode))
		return ('-');
	else if (S_ISLNK(mode))
		return ('l');
	else if (S_ISSOCK(mode))
		return ('s');
	else
		return ('u');
}

char			*ft_mode_check(mode_t mode)
{
	char	*out;
	int		i;

	out = ft_strdup("----------");
	i = 0;
	out[i++] = ft_1chr_ftype(mode);
	out[i++] = (S_IRUSR & mode) ? 'r' : '-';
	out[i++] = (S_IWUSR & mode) ? 'w' : '-';
	out[i++] = (S_IXUSR & mode) ? 'x' : '-';
	out[i - 1] = (S_ISUID & mode) ? "Ss"[out[i - 1] == 'x'] : out[i - 1];
	out[i++] = (S_IRGRP & mode) ? 'r' : '-';
	out[i++] = (S_IWGRP & mode) ? 'w' : '-';
	out[i++] = (S_IXGRP & mode) ? 'x' : '-';
	out[i - 1] = (S_ISGID & mode) ? "Ss"[out[i - 1] == 'x'] : out[i - 1];
	out[i++] = (S_IROTH & mode) ? 'r' : '-';
	out[i++] = (S_IWOTH & mode) ? 'w' : '-';
	out[i++] = (S_IXOTH & mode) ? 'x' : '-';
	out[i - 1] = (S_ISVTX & mode) ? "Tt"[out[i - 1] == 'x'] : out[i - 1];
	return (out);
}

unsigned int	num_digits(unsigned int n)
{
	unsigned int	output;

	output = 1;
	while ((n /= 10) != 0)
		output++;
	return (output);
}

long			ft_max(long num1, long num2)
{
	if (num1 > num2)
		return (num1);
	return (num2);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgleason <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/14 22:47:36 by cgleason          #+#    #+#             */
/*   Updated: 2018/08/24 13:38:06 by cgleason         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

unsigned int		g_opts = 0;

void	global_max_update(t_fdata *entry)
{
	unsigned int	maximum;

	if ((maximum = ft_strlen(entry->name)) > g_max[namelen])
		g_max[namelen] = maximum;
	if ((maximum = ft_strlen(entry->owner)) > g_max[uidlen])
		g_max[uidlen] = maximum;
	if ((maximum = ft_strlen(entry->group)) > g_max[gidlen])
		g_max[gidlen] = maximum;
	if (entry->mode[0] == 'b' || entry->mode[0] == 'c')
	{
		if ((maximum = num_digits(entry->majnum)) > g_max[majlen])
			g_max[majlen] = maximum;
		if ((maximum = num_digits(entry->minnum)) > g_max[minlen])
			g_max[minlen] = maximum;
		if (g_max[majlen] + g_max[minlen] + 2 > g_max[sizelen])
			g_max[sizelen] = g_max[majlen] + g_max[minlen] + 2;
	}
	else
	{
		if ((maximum = num_digits(entry->size)) > g_max[sizelen])
			g_max[sizelen] = maximum;
	}
	if ((maximum = num_digits(entry->nlinks)) > g_max[nlinkslen])
		g_max[nlinkslen] = maximum;
}

t_fdata	*entry_initializer(struct stat *buf, char *name, char *fmode)
{
	t_fdata	*entry;
	char	*the_time;

	the_time = ft_time_parse(buf->st_mtime);
	entry = (t_fdata *)ft_memalloc(sizeof(t_fdata));
	ft_memcpy(entry, &((t_fdata){name, fmode,
		ft_strdup(getpwuid(buf->st_uid)->pw_name),
		ft_strdup(getgrgid(buf->st_gid)->gr_name), the_time, buf->st_mtime,
		buf->st_mtimespec.tv_nsec, buf->st_size, buf->st_nlink,
		major(buf->st_rdev), minor(buf->st_rdev)}), sizeof(t_fdata));
	global_max_update(entry);
	g_total[blocks] += buf->st_blocks;
	g_total[files] += 1;
	return (entry);
}

void	ft_print_short(t_fdata **arr, long n)
{
	long			i;
	long			dims[2];
	long			ind;
	long			newbool;
	struct winsize	w;

	if (n == 0)
		return ;
	w.ws_col = 1;
	ioctl(1, TIOCGWINSZ, &w);
	g_max[namelen] += 8 - g_max[namelen] % 8;
	dims[col] = (w.ws_col / g_max[namelen]) ? w.ws_col / g_max[namelen] : 1;
	dims[row] = (n + dims[col] - 1) / dims[col];
	dims[col] = (n + dims[row] - 1) / dims[row];
	i = 0;
	while (i < n)
	{
		ind = set_ind_newlines(dims, i, n, &newbool);
		ft_printf("%s%.*s%.*s", arr[ind % n]->name,
			!newbool *
			((g_max[namelen] - ft_strlen(arr[ind % n]->name) - 1) / 8 + 1),
			"\t\t\t\t\t\t\t\t\t\t", newbool, "\n");
		i++;
	}
}

void	ft_print_long(t_fdata **arr, unsigned long n)
{
	unsigned long	i;

	i = 0;
	while (i < n)
	{
		ft_printf("%s %*u %-*s  %-*s ", arr[i]->mode,
			g_max[nlinkslen] + 1, arr[i]->nlinks, g_max[uidlen],
			arr[i]->owner, g_max[gidlen], arr[i]->group,
			g_max[sizelen] + 1, arr[i]->size);
		if (arr[i]->mode[0] == 'b' || arr[i]->mode[0] == 'c')
			ft_printf("%*u, %*u %s %s\n",
				g_max[majlen] + 1, arr[i]->majnum,
				g_max[minlen], arr[i]->minnum, arr[i]->time, arr[i]->name);
		else
			ft_printf("%*lu %s %s\n", g_max[sizelen] + 1, arr[i]->size,
				arr[i]->time, arr[i]->name);
		i++;
	}
}

int		main(int argc, char **argv)
{
	t_dirvec	*dirs;
	t_entryvec	*files;

	if (argc == 1)
		ft_list_dir(".");
	else if (argc == 2)
	{
		if (argv[1][0] == '-')
		{
			ft_parse_opts(argv[1]);
			ft_list_dir(".");
		}
		else
			ft_list_dir(argv[1]);
	}
	else
	{
		dirs = vecnew(NULL, sizeof(t_dirdata));
		files = vecnew(NULL, sizeof(t_fdata));
		ft_order_args(argc, argv, dirs, files);
	}
	return (0);
}

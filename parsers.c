/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgleason <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/19 17:44:03 by cgleason          #+#    #+#             */
/*   Updated: 2018/08/19 17:44:10 by cgleason         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

char		*link_processor(char *name, char *full_path, char c)
{
	char		*tmp;
	char		link_path[PATH_MAX + 1];
	long		end;

	if (!(g_opts & LONG) || c != 'l')
		return (ft_strdup(name));
	if ((end = readlink(full_path, link_path, PATH_MAX)) == -1)
	{
		perror("Failed to inspect file");
		return (NULL);
	}
	name = ft_strjoin(name, " -> ");
	tmp = name;
	link_path[end] = '\0';
	name = ft_strjoin(name, link_path);
	free(tmp);
	return (name);
}

char		*ft_time_parse(time_t raw_time)
{
	char	*the_time;
	char	*year;

	the_time = ctime(&raw_time);
	the_time[16] = '\0';
	if (raw_time - time(NULL) > 15780000 || time(NULL) - raw_time > 15780000)
	{
		the_time[24] = '\0';
		year = ft_strjoin(" ", the_time + 20);
		the_time[11] = '\0';
		the_time = ft_strjoin(the_time + 4, year);
		free(year);
	}
	else
		the_time = ft_strdup(the_time + 4);
	return (the_time);
}

void		ft_parse_opts(char *opt_list)
{
	char	*opts;

	opts = "lRart1";
	opt_list++;
	while (*opt_list)
	{
		if (chrind(opts, *opt_list) != -1)
			g_opts |= 1 << chrind(opts, *opt_list++);
		else
			print_usage();
	}
}

t_dirdata	**ft_dirsort(t_dirvec *dirs)
{
	t_dirdata		**tmp;

	if (g_opts & MODTIME)
	{
		if (g_opts & REVERSE)
			tmp = (t_dirdata **)vec_sort(dirs, sizeof(t_dirdata), &dd_cmp_rt);
		else
			tmp = (t_dirdata **)vec_sort(dirs, sizeof(t_dirdata), &dd_cmp_ft);
	}
	else
	{
		if (g_opts & REVERSE)
			tmp = (t_dirdata **)vec_sort(dirs, sizeof(t_dirdata), &dd_cmp_r);
		else
			tmp = (t_dirdata **)vec_sort(dirs, sizeof(t_dirdata), &dd_cmp_f);
	}
	return (tmp);
}

void		ft_order_args(int argc, char **argv, t_dirvec *dirs,
				t_entryvec *files)
{
	int			i;
	t_dirdata	**tmp;
	int			filbool;

	filbool = 0;
	i = 0;
	if (argv[i + 1][0] == '-')
		ft_parse_opts(argv[++i]);
	while (++i < argc)
		ft_vector_args(argv[i], files, dirs, &filbool);
	ft_print_heap(files);
	tmp = ft_dirsort(dirs);
	i = 0;
	while (tmp[i] != NULL)
	{
		if (tmp[1] != NULL || filbool)
			ft_printf("%.*s%s:\n", i || filbool, "\n", tmp[i]->full_path);
		ft_list_dir(tmp[i++]->full_path);
	}
	free_dirs(dirs);
	free(tmp);
}

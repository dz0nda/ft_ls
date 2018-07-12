/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_ls_init.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/03/17 16:23:37 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/07/12 14:01:22 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/ft_ls.h"

static t_path	*ft_init_list(int ac, const char *av[], t_path *begin, size_t i)
{
	t_path		*path;

	path = NULL;
	begin = path;
	if (((int)i == ac) || ((ft_strcmp(av[i], "--") == 0) && ((int)i + 1 == ac)))
	{
		if ((path = ft_path_new(".")))
			ft_path_add(&begin, path);
	}
	else if (ft_strcmp(av[i], "--") == 0)
		i++;
	while ((int)i < ac)
		if ((path = ft_path_new(av[i++])))
			ft_path_add(&begin, path);
	return (begin);
}

static t_path	*ft_init_fill(t_path *init, t_path *begin, t_file **fbegin)
{
	t_path		*path;
	t_file		*file;
	t_read		*read;

	path = NULL;
	begin = path;
	if ((read = (t_read *)malloc(sizeof(t_read))))
	{
		while (init)
		{
			if (lstat(init->uid, &read->stat) == -1)
				ft_false(2, init->uid, ' ');
			else if (S_ISDIR(read->stat.st_mode))
			{
				if ((path = ft_path_new(init->uid)))
					ft_path_add(&begin, path);
			}
			else if ((file = ft_file_new(init->uid, NULL)))
				if (ft_formsize(&init, file))
					ft_file_add(fbegin, file);
			init = init->next;
		}
		free(read);
	}
	return (begin);
}

t_path			*ft_init(int ac, const char *av[], t_path *begin, size_t *i)
{
	t_path		*init;
	t_path		*initnext;
	t_file		*fbegin;

	init = NULL;
	begin = NULL;
	fbegin = NULL;
	if ((init = ft_init_list(ac, av, init, *i)))
	{
		begin = ft_init_fill(init, begin, &fbegin);
		if (fbegin)
			ft_print(&fbegin, init, 0);
		while (init)
		{
			ft_strdel(&init->uid);
			initnext = init->next;
			free(init);
			init = initnext;
		}
	}
	free(init);
	*i = 0;
	return (begin);
}

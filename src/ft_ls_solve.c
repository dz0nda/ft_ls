/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_ls_solve.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/01 00:27:52 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/07/12 14:02:09 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/ft_ls.h"

t_file			*ft_solve_file(t_path **path, t_path **subpath, t_file *begin,
		DIR *dir)
{
	t_dirent	*ent;
	t_file		*file;
	t_path		*pathnew;
	char		idpath[1024];

	file = NULL;
	begin = file;
	while ((ent = readdir(dir)) != NULL)
	{
		ft_bzero(idpath, 1024);
		ft_strcpy(idpath, (*path)->uid);
		(idpath[ft_strlen(idpath) - 1] != '/') ? ft_strcat(idpath, "/") : 0;
		ft_strcat(idpath, ent->d_name);
		if (!(g_flag[1] != 1 && ent->d_name[0] == '.'))
			if ((file = ft_file_new(idpath, (*path))))
			{
				if (ft_formsize(path, file))
					ft_file_add(&begin, file);
				if (g_flag[0] == 1 && ft_strcmp(ent->d_name, "..") != 0 &&
				ft_strcmp(ent->d_name, ".") != 0 && file->array[0][0] == 'd')
					if ((pathnew = ft_path_new(idpath)))
						ft_path_add(subpath, pathnew);
			}
	}
	return (begin);
}

int				ft_solve(t_path *path, size_t count)
{
	DIR			*dir;
	t_path		*pathnext;

	while (path)
	{
		if ((dir = opendir(path->uid)) != NULL)
		{
			path->lstfile = ft_solve_file(&path, &path->subpath, path->lstfile,
					dir);
			ft_print(&path->lstfile, path, ++count);
			if (path->subpath)
			{
				ft_putchar('\n');
				ft_solve(path->subpath, count);
			}
		}
		dir == NULL ? ft_false(3, path->uid, ' ') : closedir(dir);
		path->next != NULL ? ft_putchar('\n') : 0;
		pathnext = path->next;
		ft_strdel(&path->uid);
		free(path);
		path = pathnext;
	}
	return (1);
}

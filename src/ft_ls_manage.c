/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_ls_manage.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/01 08:30:46 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/07/12 13:58:49 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/ft_ls.h"

void			ft_file_add(t_file **begin, t_file *file)
{
	while (*begin)
	{
		if (g_flag[3] == 0 && g_flag[4] == 0 &&
				(ft_strcmp((*begin)->array[7], file->array[7]) >= 0))
			break ;
		if (g_flag[3] == 1 && g_flag[4] == 0 &&
				(ft_strcmp((*begin)->array[7], file->array[7]) < 0))
			break ;
		else if (g_flag[3] == 0 && g_flag[4] == 1 &&
			(((*begin)->time < file->time) || (((*begin)->time == file->time) &&
			(ft_strcmp((*begin)->array[7], file->array[7]) >= 0))))
			break ;
		else if (g_flag[3] == 1 && g_flag[4] == 1 &&
			(((*begin)->time > file->time) || (((*begin)->time == file->time) &&
			(ft_strcmp((*begin)->array[7], file->array[7]) < 0))))
			break ;
		else
			begin = &(*begin)->next;
	}
	file->next = *begin;
	*begin = file;
}

char			*ft_file_new_get(t_stat stat, int i)
{
	t_passwd	*user;
	t_group		*grp;
	char		*s;

	if (i == 1)
	{
		if ((user = getpwuid(stat.st_uid)))
			s = ft_strdup(user->pw_name);
		else
			s = ft_itoa(stat.st_uid);
	}
	else if (i == 2)
	{
		if ((grp = getgrgid(stat.st_gid)))
			s = ft_strdup(grp->gr_name);
		else
			s = ft_itoa(stat.st_gid);
	}
	else
		return (NULL);
	return (s);
}

t_file			*ft_file_new(const char *name, t_path *path)
{
	t_file		*new;
	t_stat		stat;
	char		buff[1024];

	ft_bzero(buff, 1024);
	if ((!(new = (t_file *)malloc(sizeof(t_file)))) || lstat(name, &stat) == -1)
		return (NULL);
	path != NULL ? path->size += stat.st_blocks : 0;
	new->array[0] = ft_fill_chmod(stat.st_mode, (char *)name);
	new->array[1] = ft_itoa(stat.st_nlink);
	new->array[2] = ft_file_new_get(stat, 1);
	new->array[3] = ft_file_new_get(stat, 2);
	new->array[4] = ft_is_min_maj(stat, 0);
	new->array[5] = ft_is_min_maj(stat, 1);
	new->array[6] = ft_fill_time(stat);
	new->array[7] = (ft_strrchr(name, '/')) ?
		ft_strdup(ft_strrchr(name, '/') + 1) : ft_strdup(name);
	new->array[8] = (S_ISLNK(stat.st_mode) && readlink(name, buff, 1024)) ?
		ft_strjoin("-> ", buff) : ft_strdup("");
	new->time = stat.st_mtime;
	new->next = NULL;
	return (new);
}

void			ft_path_add(t_path **begin, t_path *path)
{
	while (*begin)
	{
		if (g_flag[3] == 0 && g_flag[4] == 0 &&
				(ft_strcmp((*begin)->uid, path->uid) >= 0))
			break ;
		if (g_flag[3] == 1 && g_flag[4] == 0 &&
				(ft_strcmp((*begin)->uid, path->uid) < 0))
			break ;
		else if (g_flag[3] == 0 && g_flag[4] == 1 &&
				((*begin)->time < path->time))
			break ;
		else if (g_flag[3] == 1 && g_flag[4] == 1 &&
				((*begin)->time >= path->time))
			break ;
		else
			begin = &(*begin)->next;
	}
	path->next = *begin;
	*begin = path;
}

t_path			*ft_path_new(const char *path)
{
	t_path		*new;
	t_read		read;
	int			i;

	if (!(new = (t_path *)malloc(sizeof(t_path))))
		return (NULL);
	i = -1;
	while (++i < 9)
		new->len[i] = 0;
	new->uid = ft_strdup(path);
	if (lstat(new->uid, &read.stat) > -1)
	{
		new->time = read.stat.st_mtime;
		new->size = 0;
	}
	new->subpath = NULL;
	new->next = NULL;
	return (new);
}

/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_ls_print.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/03/31 23:26:15 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/07/12 13:58:49 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/ft_ls.h"

void			ft_print_header(t_path *path, size_t count)
{
	char		*s;

	s = NULL;
	if ((count != 1 || path->next != NULL) && count != 0)
		s = ft_strjoin(path->uid, ":");
	ft_putendl(s);
	if (s)
		ft_strdel(&s);
	if (g_flag[2] == 1 && path->lstfile != NULL)
	{
		ft_putstr("total ");
		s = ft_itoa(path->size);
		ft_putendl(s);
		ft_strdel(&s);
	}
}

void			ft_print(t_file **fil, t_path *path, size_t count)
{
	t_file		*filenext;
	int			i;
	int			j;

	ft_print_header(path, count);
	while ((*fil))
	{
		i = (g_flag[2] == 1 && g_flag[5] != 1) ? -1 : 6;
		while (++i < 9)
		{
			j = path->len[i] - ft_strlen((*fil)->array[i]);
			while (i < 7 && i != 2 && i != 3 && j-- > 0)
				ft_putchar(' ');
			i == 8 ? ft_putendl((*fil)->array[i]) : ft_putstr((*fil)->array[i]);
			while ((i == 2 || i == 3) && j-- > 0)
				ft_putchar(' ');
			i != 8 ? ft_putchar(' ') : 0;
		}
		i = -1;
		while (++i < 9)
			ft_strdel(&(*fil)->array[i]);
		filenext = (*fil)->next;
		free(*fil);
		(*fil) = filenext;
	}
}

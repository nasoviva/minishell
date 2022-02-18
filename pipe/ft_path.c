/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hverda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 16:12:11 by hverda            #+#    #+#             */
/*   Updated: 2021/12/16 16:12:13 by hverda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_path(char *comd, char **mypathes, t_cmd *cmd)
{
	int		i;
	char	*path;
	char	*row_path;
	char	**tmp;

	i = 0;
	if (access(comd, X_OK) == 0)
		return (comd);
	tmp = mypathes;
	while (tmp[i])
	{
		row_path = ft_strjoin(tmp[i], "/", cmd);
		path = ft_strjoin(row_path, comd, cmd);
		if (row_path)
			free(row_path);
		if (access(path, F_OK) == 0)
			return (path);
		if (path)
			free(path);
		i++;
	}
	return (NULL);
}

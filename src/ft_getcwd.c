/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getcwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hverda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 16:07:25 by hverda            #+#    #+#             */
/*   Updated: 2021/12/16 16:07:27 by hverda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_getcwd(t_cmd *cmd)
{
	char	*buf;
	int		len;
	char	*result;
	char	*new_dir;

	len = 100500;
	buf = malloc(sizeof (char) * len);
	if (!buf)
		ft_mistake("Error: Out of memory\n", cmd);
	result = getcwd(buf, len);
	new_dir = ft_strdup(result, cmd);
	free(buf);
	return (new_dir);
}

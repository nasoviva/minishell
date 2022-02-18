/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hverda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 16:09:13 by hverda            #+#    #+#             */
/*   Updated: 2021/12/16 16:09:15 by hverda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strdup(char *s1, t_cmd *cmd)
{
	char	*str;
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(s1);
	str = NULL;
	str = (char *) malloc(sizeof(char) * (len + 1));
	if (str == 0)
		ft_mistake("Error: Out of memory\n", cmd);
	while (i < len)
	{
		str[i] = s1[i];
		i++;
		str[i] = '\0';
	}
	return (str);
}

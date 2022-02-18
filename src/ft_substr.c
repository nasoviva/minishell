/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hverda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 16:09:56 by hverda            #+#    #+#             */
/*   Updated: 2021/12/16 16:09:58 by hverda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_substr(char *s, unsigned int start, size_t len, t_cmd *cmd)
{
	unsigned int	i;
	unsigned int	j;
	char			*dst;

	i = 0;
	j = 0;
	if (s == 0)
		return (0);
	dst = NULL;
	dst = (char *)malloc(sizeof(char) * (len + 1));
	if (dst == 0)
		ft_mistake("Error: Out of memory\n", cmd);
	while (s[i] != '\0')
	{
		if (i >= start && j < (unsigned int)len)
		{
			dst[j] = s[i];
			j++;
		}
		i++;
	}
	dst[j] = '\0';
	return (dst);
}

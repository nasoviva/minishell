/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_comparison.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hverda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 16:09:01 by hverda            #+#    #+#             */
/*   Updated: 2021/12/16 16:09:03 by hverda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_str_cmp(char *s1, char *s2)
{
	int	len1;
	int	len2;
	int	i;

	i = 0;
	len1 = (int) ft_strlen(s1);
	len2 = (int) ft_strlen(s2);
	if (len1 != len2)
		return (1);
	while (i < len1)
	{
		if (s1[i] != s2[i])
			return (1);
		i++;
	}
	return (0);
}

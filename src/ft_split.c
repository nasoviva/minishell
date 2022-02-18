/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hverda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 16:08:49 by hverda            #+#    #+#             */
/*   Updated: 2021/12/16 16:08:52 by hverda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_numwords(char *s, char c)
{
	int	n;
	int	i;

	n = 0;
	i = 0;
	while (s[i] != '\0')
	{
		while ((s[i] == c) && (s[i] != '\0'))
			i++;
		if ((s[i] != c) && (s[i] != '\0'))
			n++;
		while ((s[i] != c) && (s[i] != '\0'))
			i++;
		if (s[i] == c && s[i + 1] == '\0')
			n++;
	}
	return (n);
}

static int	ft_len_of_middle(char *s, char c)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while ((s[i] != c) && (s[i] != '\0'))
	{
		k++;
		i++;
	}
	return (k);
}

static char	*ft_middle(char *s, char c, t_cmd *cmd)
{
	int		n;
	char	*middle;

	n = ft_len_of_middle(s, c);
	middle = NULL;
	middle = (char *) malloc(sizeof (char) * (n + 1));
	if (middle == 0)
		ft_mistake("Error: Out of memory\n", cmd);
	ft_strlcpy (middle, s, n + 1);
	middle[n] = 0;
	return (middle);
}

static char	**ft_freemalloc(char **mass)
{
	int	j;

	j = ft_strlen(*mass);
	while ((j + 1) > 0)
	{
		free(mass[j--]);
		j--;
	}
	free(mass);
	mass = 0;
	return (mass);
}

char	**ft_split(char *s, char c, t_cmd *cmd)
{
	int		n;
	int		j;
	char	**result;

	if (s == 0)
		return (NULL);
	n = ft_numwords(s, c);
	j = 0;
	result = (char **) malloc(sizeof (char *) * (n + 1));
	if (result == 0)
		ft_mistake("Error: Out of memory\n", cmd);
	while ((j < n) && (*s != '\0'))
	{
		while (*s == c)
			s++;
		result[j] = ft_middle(s, c, cmd);
		if (result[j] == 0)
			ft_freemalloc(result);
		s = s + ft_strlen(result[j]);
		j++;
	}
	result[n] = 0;
	return (result);
}

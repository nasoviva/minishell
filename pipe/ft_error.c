/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hverda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 16:10:43 by hverda            #+#    #+#             */
/*   Updated: 2021/12/16 16:10:45 by hverda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_error(char *begin, char *object, char *err, int i)
{
	g_error = i;
	write(2, begin, ft_strlen(begin));
	write(2, object, ft_strlen(object));
	write(2, err, ft_strlen(err));
}

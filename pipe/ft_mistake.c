/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mistake.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hverda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 16:11:50 by hverda            #+#    #+#             */
/*   Updated: 2021/12/16 16:11:52 by hverda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_mistake(char *message, t_cmd *cmd)
{
	while (*message)
	{
		write(2, message, 1);
		message++;
	}
	ft_free(cmd);
	exit (1);
}

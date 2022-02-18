/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hverda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 16:08:19 by hverda            #+#    #+#             */
/*   Updated: 2021/12/16 16:08:21 by hverda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_razryad(int n)
{
	int	d;

	d = 1;
	if (n == -2147483648)
		d = 10;
	if ((n >= -2147483647) && (n < 0))
		n = n * (-1);
	while (((n / 10) != 0) && (n >= 0))
	{
		d++;
		n = n / 10;
	}
	return (d);
}

static int	ft_ten_power(int n)
{
	int	power;

	power = 1;
	n = n - 1;
	while (n > 0)
	{
		power = power * 10 ;
		n--;
	}
	if (power == 1)
		power = 10;
	return (power);
}

static char	*ft_itoa_print(char *res, int i, int n)
{
	int	razr;

	razr = ft_razryad(n);
	while (razr > 0)
	{
		if (razr == 1)
		{
			res[i] = n + 48;
			i++;
		}
		else
		{
			res[i] = (n / ft_ten_power(razr)) + 48;
			n = n % ft_ten_power(razr);
			i++;
		}
		razr--;
	}
	res[i] = '\0';
	return (res);
}

static char	*ft_malloc(int n, int razr)
{
	char	*res;

	if (n < 0)
		res = (char *) malloc(razr + 2);
	else
		res = (char *) malloc(razr + 1);
	return (res);
}

char	*ft_itoa(int n, t_cmd *cmd)
{
	char	*res;
	int		i;

	res = ft_malloc(n, ft_razryad(n));
	if (!res)
		ft_mistake("Error: Out of memory\n", cmd);
	i = 0;
	if (n < 0)
	{
		if (n == -2147483648)
		{
			n = 147483648;
			res[0] = '-';
			res[1] = '2';
			i = 2;
		}
		else
		{
			res[i] = '-';
			n = n *(-1);
			i++;
		}
	}
	return (ft_itoa_print(res, i, n));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carfern2 <carfern2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 14:06:06 by carfern2          #+#    #+#             */
/*   Updated: 2024/10/07 14:36:26 by carfern2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_num_len(int n)
{
	int	len;
	int	num;

	len = 1;
	if (n < 0)
		len++;
	num = n;
	while (num / 10 != 0)
	{
		num /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*str;
	long	num;
	int		len;
	int		is_negative;

	num = n;
	is_negative = 0;
	if (n < 0)
	{
		is_negative = 1;
		num = -num;
	}
	len = ft_num_len(n);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = '\0';
	if (is_negative)
		str[0] = '-';
	while (--len >= is_negative)
	{
		str[len] = (num % 10) + '0';
		num /= 10;
	}
	return (str);
}

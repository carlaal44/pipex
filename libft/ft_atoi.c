/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carfern2 <carfern2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 11:30:58 by carfern2          #+#    #+#             */
/*   Updated: 2024/10/16 15:49:33 by carfern2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	sign;
	int	result;

	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	sign = 1;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	result = 0;
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return (sign * result);
}

/*
#include <stdio.h>

int		main(void)
{
	char *str1 = "-21";
	char *str2 = "--42";
	char *str3 = "     a +3";

	printf("%d\n", ft_atoi(str1));
	printf("%d\n", atoi(str1));
	printf("%d\n", ft_atoi(str2));
	printf("%d\n", atoi(str2));
	printf("%d\n", ft_atoi(str3));
	printf("%d\n", atoi(str3));
}
*/
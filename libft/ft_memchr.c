/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carfern2 <carfern2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 08:34:40 by carfern2          #+#    #+#             */
/*   Updated: 2024/10/15 14:45:52 by carfern2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t len)
{
	unsigned int	i;
	unsigned char	character;
	unsigned char	*str;

	i = 0;
	str = (unsigned char *)s;
	character = (unsigned char)c;
	while (len > i)
	{
		if (str[i] == character)
			return (i + (void *)s);
		i++;
	}
	return (NULL);
}

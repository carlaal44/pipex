/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carfern2 <carfern2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 10:50:38 by carfern2          #+#    #+#             */
/*   Updated: 2024/10/15 14:16:01 by carfern2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;
	size_t				cont;

	d = (unsigned char *)dst;
	s = (const unsigned char *)src;
	cont = 0;
	while (cont < n)
	{
		d[cont] = s[cont];
		cont++;
	}
	return (dst);
}

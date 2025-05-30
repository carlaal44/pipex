/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carfern2 <carfern2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 14:57:53 by carfern2          #+#    #+#             */
/*   Updated: 2024/10/15 14:54:02 by carfern2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	sep_finder(char str, char c)
{
	if (str == c)
		return (1);
	return (0);
}

static int	cont_words(char *str, char c)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	while (str[i])
	{
		if (!sep_finder(str[i], c) && (sep_finder(str[i + 1], c) || str[i
					+ 1] == '\0'))
			words++;
		i++;
	}
	return (words);
}

static int	free_str(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
	return (0);
}

static int	write_str(char **r, char *str, char c)
{
	int	i;
	int	j;
	int	words;

	i = 0;
	words = 0;
	while (str[i])
	{
		if (sep_finder(str[i], c))
			i++;
		else
		{
			j = 0;
			while (!sep_finder(str[i + j], c) && (str[i + j]))
				j++;
			r[words] = ft_substr(str, i, j);
			if (r[words] == NULL)
				return (free_str(r));
			i += j;
			words++;
		}
	}
	return (1);
}

char	**ft_split(char const *s, char c)
{
	int		words;
	char	**res;

	if (!s)
		return (NULL);
	words = cont_words((char *)s, c);
	res = ft_calloc(words + 1, sizeof(char *));
	if (!res)
		return (NULL);
	if (!write_str(res, (char *)s, c))
		return (NULL);
	return (res);
}

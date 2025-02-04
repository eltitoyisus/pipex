/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramos-a <jramos-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 10:55:24 by marvin            #+#    #+#             */
/*   Updated: 2025/01/29 13:23:19 by jramos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_counter(const char *s, char c)
{
	int	word;
	int	in_word;

	word = 0;
	in_word = 0;
	while (*s)
	{
		if (*s != c && !in_word)
		{
			word++;
			in_word = 1;
		}
		else if (*s == c)
			in_word = 0;
		s++;
	}
	return (word);
}

static char	*ft_read_word(const char *s, char c, int *index)
{
	int		start;
	int		len;
	char	*word;

	while (s[*index] == c)
		(*index)++;
	start = *index;
	while (s[*index] && s[*index] != c)
		(*index)++;
	len = *index - start;
	word = (char *)malloc((len + 1) * sizeof(char));
	if (!word)
		return (NULL);
	ft_strlcpy(word, &s[start], len + 1);
	return (word);
}

static char	**ft_split_word(const char *s, char c)
{
	char	**arr;
	int		words;
	int		i;
	int		index;

	words = ft_counter(s, c);
	arr = (char **)malloc((words + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	i = 0;
	index = 0;
	while (i < words)
	{
		arr[i] = ft_read_word(s, c, &index);
		if (!arr[i])
		{
			while (i > 0)
				free(arr[--i]);
			free(arr);
			return (NULL);
		}
		i++;
	}
	arr[i] = NULL;
	return (arr);
}

char	**ft_split(char const *s, char c)
{
	if (!s)
		return (NULL);
	return (ft_split_word(s, c));
}

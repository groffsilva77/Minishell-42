/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggroff-d <ggroff-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 20:32:26 by ggroff-d          #+#    #+#             */
/*   Updated: 2024/11/06 17:04:27 by ggroff-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_substr(char const *s, char c)
{
	int		count;
	int		in_substr;

	count = 0;
	in_substr = 0;
	while (*s)
	{
		if (*s != c && !in_substr)
		{
			in_substr = 1;
			count++;
		}
		else if (*s == c)
			in_substr = 0;
		s++;
	}
	return (count);
}

static char	*ft_extract_substr(char const **s, char c)
{
	const char	*start;
	int			len;

	start = *s;
	len = 0;
	while (**s && **s != c)
	{
		(*s)++;
		len++;
	}
	return (ft_substr(start, 0, len));
}

static void	ft_free(char **str)
{
	size_t	i;

	i = 0;
	if (str)
	{
		while (str[i] != NULL)
		{
			free(str[i]);
			i++;
		}
		free(str);
	}
}

char	**ft_split(char const *s, char c)
{
	char		**new_subs;
	int			i;

	new_subs = (char **)malloc((ft_count_substr(s, c) + 1) * sizeof(char *));
	if (!new_subs || !s)
		return (NULL);
	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			new_subs[i] = ft_extract_substr(&s, c);
			if (!new_subs[i])
			{
				ft_free(new_subs);
				return (NULL);
			}
			i++;
		}
		else
			s++;
	}
	new_subs[i] = NULL;
	return (new_subs);
}

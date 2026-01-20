/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpolo <gpolo@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 13:24:10 by gpolo             #+#    #+#             */
/*   Updated: 2024/07/16 10:09:58 by gpolo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

static size_t	gnl_strlen(const char *s)
{
	size_t	c;

	c = 0;
	while (s[c] != '\0')
		c++;
	return (c);
}

char	*gnl_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (*s == (char)c)
		return ((char *)s);
	return (0);
}

char	*gnl_strdup(const char *s)
{
	char	*dup;
	size_t	len;
	size_t	c;	

	len = gnl_strlen(s) + 1;
	dup = (char *)malloc(len);
	if (dup == NULL)
		return (NULL);
	c = 0;
	if (!dup && !s)
		return (0);
	while (c < len)
	{
		((unsigned char *) dup)[c] = ((unsigned char *) s)[c];
		c++;
	}
	return (dup);
}

char	*gnl_strjoin(char const *s1, char const *s2)
{
	char	*join;
	int		leng;
	int		c;
	int		c2;

	c = 0;
	c2 = 0;
	if (!s1 && !s2)
		return (0);
	leng = (gnl_strlen(s1) + gnl_strlen(s2));
	join = (char *)malloc(sizeof(char) * (leng + 1));
	if (!join)
		return (0);
	while (s1[c])
	{
		join[c] = s1[c];
		c++;
	}
	while (s2[c2])
		join[c++] = s2[c2++];
	join[c] = '\0';
	return (join);
}

char	*gnl_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	c;
	size_t	s_len;

	c = 0;
	s_len = gnl_strlen(s);
	if (start >= s_len)
		return (gnl_strdup(""));
	if (len > s_len - start)
		len = s_len - start;
	substr = (char *)malloc(sizeof(char) * (len + 1));
	if (substr == NULL)
		return (NULL);
	while (s[start + c] && c < len)
	{
		substr[c] = s[start + c];
		c++;
	}
	substr[c] = '\0';
	return (substr);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtaniga <vtaniga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 11:57:51 by vtaniga           #+#    #+#             */
/*   Updated: 2025/12/12 21:27:04 by vtaniga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "../inc/minishell.h"

size_t	ft_strcpy(char *dest, char *src)
{
	size_t	i;

	i = 0;
	if (!dest || !src)
		return (0);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (i);
}

// int	ft_strncmp(const char *s1, const char *s2, size_t n)
// {
// 	unsigned char	*ptr1;
// 	unsigned char	*ptr2;

// 	ptr1 = (unsigned char *)s1;
// 	ptr2 = (unsigned char *)s2;
// 	if (n == 0)
// 		return (0);
// 	while (n--)
// 	{
// 		if (*ptr1 != *ptr2)
// 			return (*ptr1 - *ptr2);
// 		if (*ptr1 == '\0')
// 			break ;
// 		ptr1++;
// 		ptr2++;
// 	}
// 	return (0);
// }

int	ft_revstrncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*ptr1;
	unsigned char	*ptr2;
	int				len1;
	int				len2;

	if (!s1 || !s2 || n == 0)
		return (0);
	ptr1 = (unsigned char *)s1;
	ptr2 = (unsigned char *)s2;
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if (len1 == 0 || len2 == 0)
		return (0);
	ptr1 += len1 - 1;
	ptr2 += len2 - 1;
	while (n--)
	{
		if (*ptr1 != *ptr2)
			return (*ptr1 - *ptr2);
		if (ptr1 == (unsigned char *)s1 || ptr2 == (unsigned char *)s2)
			break ;
		ptr1--;
		ptr2--;
	}
	return (0);
}

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	if (!*little)
		return ((char *)big);
	i = 0;
	while (big[i] && i < len)
	{
		j = 0;
		while (big[i + j] == little[j] && (i + j) < len)
		{
			if (!little[j + 1])
				return ((char *)&big[i]);
			j++;
		}
		i++;
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jderachi <jderachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 10:15:31 by jderachi          #+#    #+#             */
/*   Updated: 2025/12/12 18:32:31 by jderachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char	*ft_strrchr(char *str, int c)
{
	int	len;

	len = ft_strlen(str);
	if ((char)c == '\0')
		return (str + len);
	while (len >= 0)
	{
		if (str[len] == (char)c)
			return (str + len);
		len--;
	}
	return (0);
}
/*
int main(void)
{
    char *str = "Test de chaine";
    char find = 'a';
    char *result;

    result = ft_strrchr(str, find);
    if (result)
        printf("%c trouvée à: %s\n", find, result);
    else
        printf("%c non trouvé\n", find);

    return 0;
}
*/

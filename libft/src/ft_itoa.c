/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jderachi <jderachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 09:11:29 by jderachi          #+#    #+#             */
/*   Updated: 2025/12/12 18:30:11 by jderachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

static int	count_digits(int n)
{
	int		len;
	long	nb;

	nb = (long)n;
	len = (nb <= 0);
	if (nb < 0)
		nb = -nb;
	while (nb)
	{
		nb /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*str;
	long	nb;
	int		len;

	nb = (long)n;
	len = count_digits(n);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = '\0';
	if (nb == 0)
		str[0] = '0';
	if (nb < 0)
	{
		str[0] = '-';
		nb = -nb;
	}
	while (nb > 0)
	{
		str[--len] = (nb % 10) + '0';
		nb /= 10;
	}
	return (str);
}

/*
int	main(void)
{
	printf("%s", ft_itoa(-2147483648));
	return (0);
}
*/

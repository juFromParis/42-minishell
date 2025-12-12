/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jderachi <jderachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 11:38:26 by jderachi          #+#    #+#             */
/*   Updated: 2025/12/12 18:29:55 by jderachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

int	ft_isalnum(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9'))
		return (1);
	return (0);
}
/*
int main(void)
{
	printf("%d\n", ft_isalnum('J'));
	printf("%d\n", ft_isalnum('2'));
	printf("%d\n", ft_isalnum('@'));
	return 0;
}
*/

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jderachi <jderachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 15:19:51 by jderachi          #+#    #+#             */
/*   Updated: 2025/12/12 18:29:48 by jderachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}
/*
int main(void)
{
    char test[10] = "abcdefghi";
    ft_bzero(test, 4);
    printf("%s\n", test + 4);
}
*/

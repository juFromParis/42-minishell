/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jderachi <jderachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 10:55:58 by jderachi          #+#    #+#             */
/*   Updated: 2025/12/12 18:33:44 by jderachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

int	ft_lstsize(t_list *lst)
{
	int	len;

	len = 0;
	while (lst)
	{
		len++;
		lst = lst->next;
	}
	return (len);
}
/*
int	main(void)
{
	t_list *n1 = ft_lstnew("ch1");
	t_list *n2 = ft_lstnew("ch2");
	t_list *n3 = ft_lstnew("ch3");

	ft_lstadd_front(&n1, n2);
	ft_lstadd_front(&n2, n3);

	int size = ft_lstsize(n3);
	printf("%d\n", size);

	free(n1);
	free(n2);
	free(n3);

	return (0);
}
*/

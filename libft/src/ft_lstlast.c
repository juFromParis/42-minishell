/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jderachi <jderachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 11:40:57 by jderachi          #+#    #+#             */
/*   Updated: 2025/12/12 18:33:48 by jderachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}
/*
int	main(void)
{
	t_list *n1 = ft_lstnew("First");
	t_list *n2 = ft_lstnew("Second");
	t_list *n3 = ft_lstnew("Last");

	ft_lstadd_front(&n2, n3);
	ft_lstadd_front(&n1, n2);

	t_list *last = ft_lstlast(n1);

	if (last)
		printf("Dernier élément : %s\n", (char *)last->content);
	else
		printf("Liste vide\n");

	free(n1);
	free(n2);
	free(n3);

	return (0);
}
*/

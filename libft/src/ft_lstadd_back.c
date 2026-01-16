/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jderachi <jderachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 11:44:38 by jderachi          #+#    #+#             */
/*   Updated: 2025/12/12 18:33:52 by jderachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (!lst || !new)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	last = *lst;
	while (last->next)
		last = last->next;
	last->next = new;
}
/*
int	main(void)
{
	t_list *list = NULL;

	t_list *n1 = ft_lstnew("ch1");
	t_list *n2 = ft_lstnew("ch2");
	t_list *n3 = ft_lstnew("ch3");

	ft_lstadd_back(&list, n1); // list -> n1
	ft_lstadd_back(&list, n2); // list -> n1 -> n2
	ft_lstadd_back(&list, n3); // list -> n1 -> n2 -> n3

	t_list *tmp = list;
	while (tmp)
	{
		printf("Maillon : %s\n", (char *)tmp->content);
		tmp = tmp->next;
	}

	free(n1);
	free(n2);
	free(n3);

	return 0;
}
*/

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jderachi <jderachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 14:26:20 by jderachi          #+#    #+#             */
/*   Updated: 2026/01/16 10:19:21 by jderachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_redir	*redir_new(char *type, char *arg)
{
	t_redir	*r;

	r = malloc(sizeof(t_redir));
	if (!r)
		return (NULL);
	r->type = type ? ft_strdup(type) : NULL;
	r->file = NULL;
	r->delimiter = NULL;
	r->content = NULL;
	r->next = NULL;

	if (type && !ft_strcmp(type, "<<"))
		r->delimiter = arg ? ft_strdup(arg) : NULL;
	else
		r->file = arg ? ft_strdup(arg) : NULL;

	return (r);
}



void	redir_add_back(t_redir **list, t_redir *new)
{
	t_redir	*tmp;

	if (!new)
		return ;
	if (!*list)
	{
		*list = new;
		return ;
	}
	tmp = *list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

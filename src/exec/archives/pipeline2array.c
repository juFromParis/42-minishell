/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline2array.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtaniga <vtaniga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 11:44:40 by vtaniga           #+#    #+#             */
/*   Updated: 2025/12/04 12:04:58 by vtaniga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../utils/utils.h"

char	**pipeline2array(t_node *pipeline)
{
	// c'est une fonction qui transforme un pipeline en tableau pour la fonction execve
	// le tableau doit etre termine par un NULL
	// parcours l'arbre et remplit le tableau
	// on prend le premier cmd
	t_node *cur;

	cur = pipeline->child;
	while (cur)
	{
		if (cur->type == 2)
		{
			// compte le nombre d'arguments
			int count = 0;
			t_node *arg;
			arg = cur->child;
			while (arg)
			{
				count++;
				arg = arg->sibling;
			}
			// alloue le tableau
			char **args = malloc(sizeof(char *) * (count + 1));
			// remplit le tableau
			int i = 0;
			arg = cur->child;
			while (arg)
			{
				args[i] = arg->value;
				i++;
				arg = arg->sibling;
			}
			args[i] = NULL;
			return (args);
		}
		cur = cur->sibling;
	}
	return (NULL);
}
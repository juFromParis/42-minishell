/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sandbox.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtaniga <vtaniga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 16:16:48 by vtaniga           #+#    #+#             */
/*   Updated: 2025/12/15 11:32:13 by vtaniga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../utils/utils.h"
#include <stdio.h>

int	main(void)
{
	char	*tmp1;
	char	*tmp2;
	char	**tmp;
	char	**result;
	char	**original;
	char	**tmp;
	
	tmp1 = ft_strjoin("start", "test1*test2");
	tmp2 = ft_strjoin(tmp1, "end");
	free(tmp1);
	result = ft_split(tmp2, '*');
	free(tmp2);
	original = result;
	tmp = result;
	while (result && *result)
	{
		printf("'%s'\n", *result);
		result++;
	}
	while (original && *original)
	{
		free(*original);
		original++;
	}
	free(tmp);

	return (0);
}
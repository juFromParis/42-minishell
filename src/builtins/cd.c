/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtaniga <vtaniga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 15:24:09 by vtaniga           #+#    #+#             */
/*   Updated: 2025/12/15 11:52:45 by vtaniga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int	cd_command(char *path)
{
	(void)path;
	// est ce qu'il faut rajouter des options ?
	//~/path ou ~user/path : extension combinée avec chemin relatif à la home.
	//- qui permet de revenir au repertoire precedent
	//~ qui permet d'aller dans le repertoire home
	// . et .. pour naviguer dans les repertoires
	// gestion des erreurs si le repertoire n'existe pas
	// gestion des permissions
	// gestion des liens symboliques
	// mise a jour des variables d'environnement PWD et OLDPWD
	// c'est une fonction qui change le repertoire courant
	// utilise la fonction chdir
	// retourne 0 en cas de succes, -1 en cas d'erreur
	//  = chdir(path);
	// if (ret == -1)
	// {
	// 	perror("cd");
	// 	return (-1);
	// }
	printf("cwd: %s\n", getcwd(NULL, 0));
	chdir("/");
	printf("cwd: %s\n", getcwd(NULL, 0));
	return (0);
}


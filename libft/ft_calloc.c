/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduport <rduport@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 11:27:29 by rduport           #+#    #+#             */
/*   Updated: 2024/11/26 14:11:09 by rduport          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t elementcount, size_t elementsize)
{
	char	*alloc;
	size_t	i;

	i = 0;
	alloc = malloc(elementcount * elementsize);
	if (alloc == NULL)
		return (NULL);
	while (i < (elementcount * elementsize))
	{
		alloc[i] = 0;
		i++;
	}
	return (alloc);
}

/*#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define INT_NUMBER 8

int main() {
    
    int i;
    int * pointer = (int *) ft_calloc( INT_NUMBER, 10 );

    //Un petit test sur le bon fonctionnement de calloc
    assert( pointer != NULL );

    // Le dernier élément du tableau ne sera pas affecté par la
    // boucle mais n'oubliez pas que calloc initialise de toute
    // façon à 0 chaque octet.
    // On affiche le contenu du tableau d'entier
    // Ce qui donne : 0 1 2 3 4 5 6 7 8 0
    for (i=0; i<INT_NUMBER; i++ ) {
        printf( "%d ", pointer[i] );
    }
    printf( "\n" );

    // On libère le bloc de mémoire alloué dynamiquement
    free( pointer );

    return 0;
}*/

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduport <rduport@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 11:37:07 by rduport           #+#    #+#             */
/*   Updated: 2024/11/20 14:27:48 by rduport          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*new_elem;
	t_list	*temp;

	new_lst = NULL;
	while (lst != NULL)
	{
		new_elem = ft_lstnew(f(lst->content));
		if (new_elem == NULL)
		{
			ft_lstclear(&new_lst, del);
			return (NULL);
		}
		if (new_lst == NULL)
			new_lst = new_elem;
		else
		{
			temp = new_lst;
			while (temp->next != NULL)
				temp = temp->next;
			temp->next = new_elem;
		}
		lst = lst->next;
	}
	return (new_lst);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/10 10:01:36 by thallot           #+#    #+#             */
/*   Updated: 2019/07/05 10:49:16 by thallot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

float		ft_sqrt(float nb)
{
	float	x;

	x = 0;
	while (x * x < nb)
		x++;
	return (x);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngodard <ngodard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 22:10:00 by ngodard           #+#    #+#             */
/*   Updated: 2023/05/17 22:36:48 by ngodard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

double	ft_lerp(double first, double second, double p)
{
	if (first == second)
		return (first);
	return (first + (second - first) * p);
}

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


#include "fractol.h"
#include "libft.h"
#include "mlx.h"
#include <pthread.h>

void		*render_thread(void *m)
{
	t_thread	*t;
	int			x;
	int			y;

	t = (t_thread *)m;
	y = WIN_HEIGHT / THREADS * t->id;
	while (y < WIN_HEIGHT / THREADS * (t->id + 1))
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			*(t->mlx->data + y * WIN_WIDTH + x) =
				t->mlx->fractal->pixel(x, y, &t->mlx->viewport, t->mlx);
			x++;
		}
		y++;
	}
	return (NULL);
}

void		render(t_mlx *mlx)
{
	int			i;
	t_render	*r;

	i = 0;
	r = &mlx->render;
	while (i < THREADS)
	{
		r->args[i].id = i;
		r->args[i].mlx = mlx;
		pthread_create(r->threads + i, NULL, render_thread, &(r->args[i]));
		i++;
	}
	i = 0;
	while (i < THREADS)
	{
		pthread_join(r->threads[i], NULL);
		i++;
	}
	draw(mlx);
}

void		draw(t_mlx *mlx)
{
	int x;
	int y;

	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			image_set_pixel(mlx->image, x, y,
					get_color(*(mlx->data + y * WIN_WIDTH + x), mlx));
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(mlx->mlx, mlx->window, mlx->image->image, 0, 0);
}

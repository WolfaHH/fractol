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


#include "libft.h"
#include "mlx.h"
#include "fractol.h"

t_mlx		*mlxdel(t_mlx *mlx)
{
	if (mlx->window != NULL)
		mlx_destroy_window(mlx->mlx, mlx->window);
	if (mlx->image != NULL)
		del_image(mlx, mlx->image);
	ft_memdel((void **)&mlx);
	return (NULL);
}

t_mlx		*init(t_fractal *f)
{
	t_mlx	*mlx;
	char	*title;

	if ((mlx = ft_memalloc(sizeof(t_mlx))) == NULL)
		return (NULL);
	title = ft_strjoin("Fract'ol - ", f->name);
	if ((mlx->mlx = mlx_init()) == NULL ||
		(mlx->window = mlx_new_window(mlx->mlx, WIN_WIDTH,
			WIN_HEIGHT, title)) == NULL ||
		(mlx->image = new_image(mlx)) == NULL ||
		(mlx->data = ft_memalloc(sizeof(t_pixel) * WIN_WIDTH
								* WIN_HEIGHT)) == NULL)
		return (mlxdel(mlx));
	mlx->mouse.isdown = 0;
	mlx->fractal = f;
	mlx->mouselock = 1 - f->mouse;
	mlx->palette = get_palettes();
	mlx->smooth = 1;
	return (mlx);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_math.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 15:35:58 by ydzhuryn          #+#    #+#             */
/*   Updated: 2017/11/15 15:19:05 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MATH_H
# define FT_MATH_H

# define M_PI	3.14159265358979323846
# define M_PI_2	1.57079632679489661923

int		ft_ceil(float f);
float	ft_fabs(float f);
float	ft_fsqrt(float f);
int		ft_round(float f);
int		ft_powi(int i, int n);
float	ft_powf(float f, int n);
double	ft_powd(double i, int n);

#endif

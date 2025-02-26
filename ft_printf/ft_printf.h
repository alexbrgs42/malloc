/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 10:38:51 by pbourgeo          #+#    #+#             */
/*   Updated: 2023/11/06 14:17:52 by pbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <stdarg.h>

void	ft_putchar(char c, int *nb);
void	ft_putstr(char *str, int *nb);
void	ft_put_pointer(void *p, int *nb);
void	ft_putnbr_pointer(size_t n, int *nb);
void	ft_putnbr_hexa(unsigned int n, unsigned int base, int *nb, int upper);
void	ft_putnbr(long n, int *nb);
void	ft_putnbr_size_t(size_t n, int *nb);
void	ft_putunbr(unsigned int n, int *nb);
int		ft_printf(const char *str, ...);

#endif

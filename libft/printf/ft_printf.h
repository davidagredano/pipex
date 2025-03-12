/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 23:32:06 by dagredan          #+#    #+#             */
/*   Updated: 2025/03/12 23:32:10 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# define CONVERSION_SPECIFIERS "cspdiuxX%"
# define FLAGS "#0- +"

# include <stdarg.h>
# include <stdbool.h>

typedef struct s_spec
{
	bool	alternative_form;
	bool	zero_padding;
	bool	left_align;
	bool	leading_blank;
	char	leading_sign;
	int		field_width;
	int		precision;
	char	specifier;
}		t_spec;

bool	ft_isvalid(const char *spec_str);
int		ft_parse(const char *spec_str, t_spec *spec);

char	*ft_get_base_str(t_spec *spec);
void	ft_insert_conv(char *dst, const char *src, t_spec *spec);

int		ft_print_c(int c, t_spec *spec);
int		ft_print_s(const char *s, t_spec *spec);
int		ft_print_p(void *p, t_spec *spec);
int		ft_print_d(int n, t_spec *spec);
int		ft_print_u(unsigned n, t_spec *spec);
int		ft_print_x(unsigned n, t_spec *spec);

#endif

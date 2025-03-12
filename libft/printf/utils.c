/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 23:32:20 by dagredan          #+#    #+#             */
/*   Updated: 2025/03/12 23:32:22 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "../libft.h"

/**
 * Copies the src string, from right to left, to the buffer pointed to by dst.
 * Prepends the character ' ', the character '+' and the string "0x" to src
 * if the correspondent flags are present; then adds '0' characters
 * if there is room to fill in the precision size before copying the src.
 */
static void	ft_insert_conv_rtl(char *dst, const char *src, t_spec *spec)
{
	int	i;
	int	padding;
	int	lead_signs;

	padding = spec->field_width - spec->precision;
	lead_signs = spec->precision - ft_strlen(src);
	i = 0;
	if (spec->leading_blank)
		dst[padding + i++] = ' ';
	if (spec->leading_sign != '\0')
		dst[padding + i++] = spec->leading_sign;
	if (spec->alternative_form && ft_strchr("xp", spec->specifier))
		i += ft_strlcpy(dst + padding + i, "0x", 3);
	else if (spec->alternative_form && spec->specifier == 'X')
		i += ft_strlcpy(dst + padding + i, "0X", 3);
	while (i < lead_signs)
	{
		dst[padding + i] = '0';
		i++;
	}
	ft_strlcpy(dst + padding + lead_signs, src, ft_strlen(src) + 1);
}

/**
 * Copies the src string, from left to right, to the buffer pointed to by dst.
 * Prepends the character ' ', the character '+' and the string "0x" to src
 * if the correspondent flags are present; then adds '0' characters
 * if there is room to fill in the precision size before copying the src.
 */
static void	ft_insert_conv_ltr(char *dst, const char *src, t_spec *spec)
{
	int	i;
	int	lead_signs;

	lead_signs = spec->precision - ft_strlen(src);
	i = 0;
	if (spec->leading_blank)
		dst[i++] = ' ';
	if (spec->leading_sign != '\0')
		dst[i++] = spec->leading_sign;
	if (spec->alternative_form && ft_strchr("xp", spec->specifier))
		i += ft_strlcpy(dst, "0x", 3);
	else if (spec->alternative_form && spec->specifier == 'X')
		i += ft_strlcpy(dst, "0X", 3);
	ft_memset(dst + i, '0', lead_signs - i);
	i = 0;
	while (lead_signs + i < spec->precision)
	{
		dst[lead_signs + i] = src[i];
		i++;
	}
}

/**
 * Calls one of the insertion functions depending on the left alignment flag.
 */
void	ft_insert_conv(char *dst, const char *src, t_spec *spec)
{
	if (spec->left_align)
		ft_insert_conv_ltr(dst, src, spec);
	else
		ft_insert_conv_rtl(dst, src, spec);
}

/**
 * Allocates a string of the appropriate size.
 * Initializes all characters except for the terminating NUL character to ' ',
 * or '0' if the zero_padding flag is present.
 * Returns a pointer to the allocated string, or NULL if allocation fails.
 */
char	*ft_get_base_str(t_spec *spec)
{
	char	*str;

	str = ft_calloc(spec->field_width + 1, sizeof(char));
	if (!str)
		return (NULL);
	if (spec->zero_padding)
		ft_memset(str, '0', spec->field_width);
	else
		ft_memset(str, ' ', spec->field_width);
	return (str);
}

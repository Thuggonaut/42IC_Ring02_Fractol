/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tquemato <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 15:11:52 by tquemato          #+#    #+#             */
/*   Updated: 2023/09/26 15:11:53 by tquemato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t buffsize)
{
	size_t	dstlen;
	size_t	srclen;

	dstlen = ft_strlen(dst);
	srclen = ft_strlen(src);
	if (dstlen < buffsize - 1 && buffsize > 0)
		ft_strlcpy(&dst[dstlen], src, buffsize - dstlen);
	if (dstlen >= buffsize)
		dstlen = buffsize;
	return (dstlen + srclen);
}

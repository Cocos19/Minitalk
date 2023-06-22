/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 11:39:03 by mprofett          #+#    #+#             */
/*   Updated: 2022/12/09 11:39:05 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_BONUS_H
# define MINITALK_BONUS_H

# include <signal.h>
# include "libft/libft.h"

typedef struct s_string_to_receive_datas
{
	int				byte_index;
	int				str_index;
	int				str_len;
	unsigned char	*str_to_print;
}					t_client_datas;

#endif

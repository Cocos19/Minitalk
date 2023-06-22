/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 11:39:03 by mprofett          #+#    #+#             */
/*   Updated: 2023/02/18 13:31:16 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

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

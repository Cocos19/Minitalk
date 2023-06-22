/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 11:37:09 by mprofett          #+#    #+#             */
/*   Updated: 2022/12/09 11:37:11 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_client_datas	g_infos;

static void	init_client_infos(void)
{
	g_infos.str_to_print = NULL;
	g_infos.byte_index = 32;
	g_infos.str_index = 0;
	g_infos.str_len = 0;
}

static void	get_client_strlen(int signal_id)
{
	if (signal_id == SIGUSR2)
		g_infos.str_len |= 1 << (--g_infos.byte_index);
	else
		--g_infos.byte_index;
	if (g_infos.byte_index == 0)
	{
		g_infos.str_to_print = malloc(sizeof(char) * (g_infos.str_len));
		if (!g_infos.str_to_print)
			exit (EXIT_FAILURE);
		g_infos.byte_index += 8;
	}
}

static void	get_next_char(int signal_id)
{
	static unsigned char	c;

	if (signal_id == SIGUSR2)
		c |= 1 << --g_infos.byte_index;
	else
		--g_infos.byte_index;
	if (g_infos.byte_index == 0)
	{
		g_infos.byte_index += 8;
		g_infos.str_to_print[g_infos.str_index++] = c;
		c = 0;
	}
}

static void	get_str(int signal_id, siginfo_t *sig_info, void *context)
{
	if (!g_infos.str_to_print)
		get_client_strlen(signal_id);
	else
		get_next_char(signal_id);
	if (g_infos.str_index == g_infos.str_len && g_infos.str_to_print)
	{
		write(1, (char *)g_infos.str_to_print, g_infos.str_len);
		free(g_infos.str_to_print);
		if (kill(sig_info->si_pid, SIGUSR2) == -1)
		{
			ft_printf("\nKill function failure when sending confirmation");
			exit (EXIT_FAILURE);
		}
		init_client_infos();
	}
	(void) context;
}

int	main(void)
{
	struct sigaction	signal_processing;

	init_client_infos();
	signal_processing.sa_sigaction = &get_str;
	signal_processing.sa_flags = SA_SIGINFO;
	ft_printf("Server process ID: %u\n", getpid());
	if (sigaction(SIGUSR1, &signal_processing, NULL) == -1)
		exit (EXIT_FAILURE);
	else if (sigaction(SIGUSR2, &signal_processing, NULL) == -1)
		exit (EXIT_FAILURE);
	while (1)
		pause();
	return (0);
}

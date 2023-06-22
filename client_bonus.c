/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 11:37:23 by mprofett          #+#    #+#             */
/*   Updated: 2022/12/09 11:37:25 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	g_server_pid;

static void	send_str_len(int str_len)
{
	int	i;

	i = 32;
	while (--i >= 0)
	{
		if ((str_len >> i) & 1)
		{
			if (kill(g_server_pid, SIGUSR2) == -1)
				exit (EXIT_FAILURE);
		}
		else
		{
			if (kill(g_server_pid, SIGUSR1) == -1)
				exit (EXIT_FAILURE);
		}
		usleep(100);
	}
}

static void	send_str(char *str_to_send)
{
	int	i;

	send_str_len(ft_strlen(str_to_send));
	while (*str_to_send)
	{
		i = 8;
		while (--i >= 0)
		{
			if ((*str_to_send >> i) & 1)
			{
				if (kill(g_server_pid, SIGUSR2) == -1)
					exit (EXIT_FAILURE);
			}
			else
			{
				if (kill(g_server_pid, SIGUSR1) == -1)
					exit (EXIT_FAILURE);
			}
			usleep(100);
		}
		++str_to_send;
	}
}

static void	get_confirmation(int signal_id, siginfo_t *sig_info, void *context)
{
	if (sig_info->si_pid == g_server_pid)
	{
		ft_printf("Confirmations received from %d", g_server_pid);
		exit (EXIT_SUCCESS);
	}
	(void) signal_id;
	(void) context;
}

static void	check_args(int argc, char **argv)
{
	if (argc != 3)
	{
		ft_printf("Wrong arguments number\n");
		exit (EXIT_FAILURE);
	}
	else if (argv[2] == NULL)
	{
		ft_printf("String to send is null.\n");
		exit (EXIT_FAILURE);
	}
	g_server_pid = ft_atoi(argv[1]);
	if (g_server_pid < 1 || g_server_pid > 99998)
	{
		ft_printf("Invalid value given for server pid.\n");
		exit (EXIT_FAILURE);
	}
}

int	main(int argc, char **argv)
{
	struct sigaction	signal_processing;

	check_args(argc, argv);
	signal_processing.sa_sigaction = &get_confirmation;
	signal_processing.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR2, &signal_processing, NULL) == -1)
		exit (EXIT_FAILURE);
	send_str(argv[2]);
	pause();
	return (EXIT_FAILURE);
}

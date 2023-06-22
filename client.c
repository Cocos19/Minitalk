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

static void	send_str_len(int str_len, int server_pid)
{
	int	i;

	i = 32;
	while (--i >= 0)
	{
		if ((str_len >> i) & 1)
		{
			if (kill(server_pid, SIGUSR2) == -1)
				exit (EXIT_FAILURE);
		}
		else
		{
			if (kill(server_pid, SIGUSR1) == -1)
				exit (EXIT_FAILURE);
		}
		usleep(100);
	}
}

static void	send_str(char *str_to_send, int server_pid)
{
	int	i;

	send_str_len(ft_strlen(str_to_send), server_pid);
	while (*str_to_send)
	{
		i = 8;
		while (--i >= 0)
		{
			if ((*str_to_send >> i) & 1)
			{
				if (kill(server_pid, SIGUSR2) == -1)
					exit (EXIT_FAILURE);
			}
			else
			{
				if (kill(server_pid, SIGUSR1) == -1)
					exit (EXIT_FAILURE);
			}
			usleep(100);
		}
		++str_to_send;
	}
}

static int	check_args(int argc, char **argv)
{
	int	server_pid;

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
	server_pid = ft_atoi(argv[1]);
	if (server_pid < 1 || server_pid > 99998)
	{
		ft_printf("Invalid value given for server pid.\n");
		exit (EXIT_FAILURE);
	}
	return (server_pid);
}

int	main(int argc, char **argv)
{
	int	server_pid;

	server_pid = check_args(argc, argv);
	send_str(argv[2], server_pid);
	return (EXIT_SUCCESS);
}

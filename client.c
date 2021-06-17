/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grigo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 14:13:32 by grigo             #+#    #+#             */
/*   Updated: 2021/06/17 14:54:51 by grigo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include <stdio.h>

static long long		ft_atoi(const char *str)
{
	unsigned long long	result;
	int					i;
	int					value;

	i = 0;
	while ((str[i] > 8 && 14 > str[i]) || str[i] == 32)
		i++;
	value = 1;
	result = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			value = -1;
		i++;
	}
	while (str[i] > 47 && 58 > str[i])
	{
		if (str[i + 1] > 47 && 58 > str[i + 1])
			result = (result + ((char)str[i] - 48)) * 10;
		else
			result = result + ((char)str[i] - 48);
		i++;
	}
	return (result * value);
}

static void send_char(pid_t pid, int c)
{
	int i;

	i = 0;
	while (i < 8)
	{
		usleep(100);
		if (c & 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		c = c >> 1;
		i++;
	}
}

static void send_message(pid_t pid, char* message)
{
	int i;

	i = 0;
	while (message[i])
	{
		send_char(pid, message[i]);
		i++;
	}
	send_char(pid, message[i]);
}

static void received(int sig, siginfo_t *sig_info, void *ok)
{
	(void)sig;
	(void)sig_info;
	(void)ok;
	write(1, "signal receveid\n", 16);
}

int main(int ac, char *av[])
{
	struct sigaction catch;

	catch.sa_flags = SA_SIGINFO;
	catch.sa_sigaction = received;
	sigaction(SIGUSR2, &catch, 0);
	if (ac != 3)
	{
		write(2, "Usage: ./client pid(server) message\n", 36);
		return (0);
	}
	else
		send_message(ft_atoi(av[1]), av[2]);
	pause();
	return (0);
}


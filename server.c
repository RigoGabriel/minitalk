/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grigo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 13:59:09 by grigo             #+#    #+#             */
/*   Updated: 2021/06/17 15:04:20 by grigo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <signal.h>

static void	receive(int sig, siginfo_t *sig_info, void *ok)
{
	static char			c = 0;
	static int			i = 0;

	(void)ok;
	if (sig == SIGUSR1)
		c += 1 << i;
	i++;
	if (i == 8)
	{
		if (c == '\0')
		{
			write(1, "\n", 1);
			usleep(100);
			kill(sig_info->si_pid, SIGUSR2);
		}
		else
			write(1, &c, 1);
		i = 0;
		c = 0;
	}
}

int	main(void)
{
	pid_t				pid;
	struct sigaction	catch;

	pid = getpid();
	printf("pid = %d\n", pid);
	catch.sa_flags = SA_SIGINFO;
	catch.sa_sigaction = receive;
	sigaction(SIGUSR1, &catch, 0);
	sigaction(SIGUSR2, &catch, 0);
	while (1)
	{
	}
	return (0);
}

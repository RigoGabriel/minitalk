/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grigo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 13:59:09 by grigo             #+#    #+#             */
/*   Updated: 2021/06/16 14:57:18 by grigo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <signal.h>

static void receive(int sig)
{
	static char c = 0;
	static int i = 0;

	if (sig == SIGUSR1)
		c += 1 << i;
	i++;
	if (i == 8)
	{
		if (c == '\0')
			write(1, "\n", 1);
		else
			write(1, &c, 1);
		i = 0;
		c = 0;
	}
}

int main()
{
	pid_t pid;

	pid = getpid();
	printf("pid = %d\n", pid);
	signal(SIGUSR1, receive);
	signal(SIGUSR2, receive);
	while(1){}
	return (0);
}

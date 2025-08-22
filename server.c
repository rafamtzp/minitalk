#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include "printf/ft_printf.h"
#include "libft/libft.h"


int lastsignal;

int is_sent(char *binstr)
{

	if (ft_strlen(binstr) < 8)
		return (0);
	if (ft_strlen((const char *)binstr) % 8 == 0)
	{
		while (*binstr)
			binstr++;
		binstr = binstr - 8;
		if (ft_strncmp((const char *)binstr, "00000000", 8) == 0)
			return (1);
	}
	return (0);
}

void sighandler(int signum)
{
	lastsignal = signum;
	// if (lastsignal == SIGUSR2)
	// 	ft_printf("%i", 0);
	// else if (lastsignal == SIGUSR1)
	// 	ft_printf("%i", 1);
}

char *plug_bit(char *binstr, int signum)
{
	char *bit;
	char *tmp;

	if (signum == SIGUSR1)
		bit = "1";
	else if (signum == SIGUSR2)
		bit = "0";
	tmp = binstr;
	binstr = ft_strjoin(tmp, bit);
	free(tmp);
	return (binstr);
}

int power(int num, int exp)
{
	int factor;

	factor = 1;
	while (exp > 0)
	{
		factor = factor * num;
		exp--;
	}
	return (factor);
}

char bintochar(char *bytestr)
{
	int i;
	char c;

	i = 7;
	c = 0;
	while (bytestr[7 - i])
	{
		if (bytestr[7 - i] == '1')
			c += power(2, i);
		i--;
	}
	return (c);
}
// decrypt.  Get next 8 chars from str each time
void write_bintoa(char *binstr)
{
	char *bytestr;
	char c;
	int i;

	i = 0;
	c = 1;
	while (1)
	{
		bytestr = ft_substr((const char *)binstr, i, 8);
		if (!bytestr)
			return ; // handle error!!!!!!!1
		c = bintochar(bytestr);
		if (c == 0)
			break ;
		free(bytestr);
		write(1, &c, 1);
		i = i + 8;
	}
}

int main(void)
{
	int pid;
	char *binstr;

	pid = getpid();
	ft_printf("Server PID: %i\n", pid);
	
	// wait for the signal
	binstr = ft_strdup("");
	if (!binstr)
		return (-1);
	signal(SIGUSR1, sighandler);
	signal(SIGUSR2, sighandler);
	while (binstr != NULL && is_sent(binstr) == 0)
	{
		pause();
		binstr = plug_bit(binstr, lastsignal);
	}
	if (binstr == NULL)
		return (-1);
	write_bintoa(binstr); // TODO: make it so that server keeps listening!!!!1
	free(binstr);
}
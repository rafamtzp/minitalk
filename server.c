#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include "printf/ft_printf.h"
#include "libft/libft.h"


int lastsignal;

// int is_sent(char *binstr)
// {

// 	if (ft_strlen(binstr) < 8)
// 		return (0);
// 	if (ft_strlen((const char *)binstr) % 8 == 0)
// 	{
// 		while (*binstr)
// 			binstr++;
// 		binstr = binstr - 8;
// 		if (ft_strncmp((const char *)binstr, "00000000", 8) == 0)
// 			return (1);
// 	}
// 	return (0);
// }

void sighandler(int signum)
{
	lastsignal = signum;
}

// char *plug_bit(char *binstr, int signum)
// {
// 	char *bit;
// 	char *tmp;

// 	if (signum == SIGUSR1)
// 		bit = "1";
// 	else if (signum == SIGUSR2)
// 		bit = "0";
//     else
//         return (NULL);
// tmp = binstr;
// binstr = ft_strjoin(tmp, bit);
// free(tmp);
// if (!binstr)
//     return (NULL); // handle here
// return (binstr);
// }

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

// int write_bytestr(char *bytestr, int i)
// {
// 	char c;

// 	c = 0;
// 	while (bytestr[7 - i])
// 	{
// 		if (bytestr[7 - i] == '1')
// 			c += power(2, i);
// 		i--;
// 	}
//     if (c == 0)
//         return (-1);
// write(1, &c, 1);
// return (0);
// }
// decrypt.  Get next 8 chars from str each time
// void write_bintoa(char *binstr)
// {
// 	char *bytestr;
// 	char c;
// 	int i;

// 	i = 0;
// 	c = 1;
// 	while (1)
// 	{
// 		bytestr = ft_substr((const char *)binstr, i, 8);
// 		if (!bytestr)
// 			return ; // handle error!!!!!!!1
// 		c = bintochar(bytestr);
// 		if (c == 0)
// 			break ;
// 		free(bytestr);
// 		write(1, &c, 1);
// 		i = i + 8;
// 	}
// }

int main(void)
{
	int pid;
    char c;
    int i;

	pid = getpid();
	ft_printf("%i\n", pid);
	
	// wait for the signal
	signal(SIGUSR1, sighandler);
	signal(SIGUSR2, sighandler);

    while (1)
    {
        i = 0;
        c = 0;
        while (i < 8)
        {
            pause();
            if (lastsignal == SIGUSR1)
                c += power(2, 7 - i);
            i++;
        }
        if (c != 0)
            write(1, &c, 1);
    }
}

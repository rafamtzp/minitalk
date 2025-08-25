#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <errno.h>
#include "libft/libft.h"
#include "printf/ft_printf.h"

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

char *chartobin(unsigned char c)
{
	char *charstr;
	int num;
	int i;

	charstr = ft_calloc(1, 8);
	if (!charstr)
		return (NULL); // handle error!
	num = (int)c;
	i = 7;
	while (i >= 1)
	{
		if (num >= power(2, i))
		{
			num = num - power(2, i);
			charstr[7 - i] = '1'; 
		}
		else
			charstr[7 - i] = '0';
		i--;
	}
	if (num == 0)
		charstr[7] = '0';
	else
		charstr[7] = '1';
	return (charstr);
}


// char *atobin(char *argv)
// {
// 	char *binchar;
// 	char *binstr;
// 	char *tmp;

// 	binstr = ft_strdup("");
// 	while (*argv)
// 	{
// 		binchar = chartobin(*argv);
// 		tmp = binstr;
// 		binstr = ft_strjoin(tmp, binchar);
// 		free(tmp);
// 		free(binchar);
// 		argv++;
// 	}
// 	return (binstr);
// }

int main(int argc, char  ** argv)
{
	int server_pid;
	char *binchar;
	int i;
    int j;

	if (argc != 3)
		return (-1); // handle err.  Terminate server?
	// check that PID exists
	server_pid = ft_atoi(argv[1]);
	if (kill(server_pid, 0) == -1 && errno == ESRCH)
		return (-1);
	// check that message is nonempty
	if (argv[2][0] == '\0')
		return (-1);
	// encrypt message
	//binstr = atobin(argv[2]);
	//ft_printf("%s\n", binstr);
	// send message
    i = 0;
    while (argv[2][i])
    {
        binchar = chartobin(argv[2][i]);
        if (!binchar)
            return (-1);
        j = 0;
        while (binchar[j])
        {
            if (binchar[j] == '0')
                kill(server_pid, SIGUSR2);
            else if (binchar[j] == '1')
                kill(server_pid, SIGUSR1);
            usleep(100);
            j++;
        }
        free(binchar);
        i++;
    }
	i = 0;
	while (i++ < 8)
	{
		kill(server_pid, SIGUSR2); // send null terminator 00000000
		usleep(100);
	}
	return (0);
}

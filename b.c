#include <stdlib.h>
#include <stdio.h>
#include <pty.h>

int	main(){
	int	fd,fds;
	char	n[100];
	struct termios tp;
	struct termios *termios_p=&tp;
	           termios_p->c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP
                           | INLCR | IGNCR | ICRNL | IXON);
           termios_p->c_oflag &= ~OPOST;
           termios_p->c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
           termios_p->c_cflag &= ~(CSIZE | PARENB);
           termios_p->c_cflag |= CS8;


	openpty(&fd,&fds,n,termios_p,0);

	printf("%s\n",n);
	while(1){
		read(fd,n,1);
		printf("%x ",n[0]);
		fflush(stdout);
//		write(fd,n,1);
//		write(fd,"\n",1);
//		read(fd,n,1);
//		sleep(1000);
	}
}

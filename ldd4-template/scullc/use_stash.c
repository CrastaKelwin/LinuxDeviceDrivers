/* application to invoke and KEEP OPEN the device driver module, kernel_semaphore, and read the device file randomly*/  
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include<signal.h>
#include<stdlib.h>

//#include "userscull.h" // for the other program 
int fd;
int keep_spinning = 1;

void catch_ctrlc(int signo) {
	printf ("Got SIGINT (%d), closing driver.\n",signo);
	keep_spinning = 0;
        close(fd);
}
int main ( ) {
        int i,k=3;        // to sort 3rd quantum (by changing the value of k )                        //changes
        char ch, write_buf[80], read_buf[80];

	signal(2, catch_ctrlc);

        fd = open("/dev/kernel_semaphore", O_RDWR);  //changes

        if (fd == -1)
        {
                printf("Error in opening file \n");
                exit(-1);
        }
        printf ("What do you want? PRESS r for reading (or) w for write: "); 
        scanf ("%c", &ch);  /* First time, should choose writing */


        switch (ch) {
                case 'w':
                         printf (" Enter the message to device: ");  ///changes
                         scanf (" %[^\n]", write_buf);
                        write(fd,write_buf,sizeof(write_buf));
			//ioctl(fd,SCULL_IOCSORTNQUANTUM , &k);   
                        break;
                case 'r':
                        lseek(fd, 0L, SEEK_SET);
                        read(fd, read_buf,sizeof(read_buf));
        	        printf ("The message from the device is : %s\n", read_buf);
			//ioctl(fd,SCULL_IOCGQUANTUM, &k);
			//printf("uantum = %d",k);
			break; 	

                default:
                        printf(" press either r or w \n");
                        break;
        }
	while (keep_spinning)
		;
	
	
  //      close(fd);


}

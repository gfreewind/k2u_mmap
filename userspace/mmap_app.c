/*
 * =====================================================================================
 *
 *       Filename:  mmap_app.c
 *
 *    Description:  The mmap app
 *                  Used to test mmap kernel memory to user space
 *
 *        Version:  1.0
 *        Created:  03/20/2013 10:10:32 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  gfree.wind@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#include <string.h>
#include <errno.h>

#define MMAP_DEV_NAME       "/dev/mmap_drv"

int main(void)
{
    char buf[32] = {0};

    int fd = open(MMAP_DEV_NAME, O_RDONLY|O_NDELAY);
    if (fd < 0) {
        printf("Fail to open %s. Error:%s\n", MMAP_DEV_NAME, strerror(errno));
        exit(-1);
    }
   
    read(fd, buf, 32);
    printf("buff is %s\n", buf);
   
    close(fd);

    return 0;
}

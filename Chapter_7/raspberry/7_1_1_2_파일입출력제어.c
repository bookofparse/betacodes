#include<stdio.h>
#include <fcntl.h>
#include <strintg.h>

int main(void)
{
int fd;
char buf[BUFSIZ];
fd = open("sys/class/gpio/export",O_WRONLY);
sprintf(buf,"%d",gpio);
write(fd, buf, strlen(buf));
close(fd);

sprintf(buf,"/sys/class/gpio/gpio%d/direction",gpio);
fd = open(buf, O_WRONLY);
write(fd, "out", 3);
close(fd);

sprintf(buf,"/sys/class/gpio/gpio%d/vlaue",gpio);
fd = open(buf, O_WRONLY);
write(fd, "1", 1);
close(fd);

sys_delay(1000);

sprintf(buf,"/sys/class/gpio/gpio%d/value",gpio);
fd = open(buf, O_WRONLY);
write(fd, "0", 1);
close(fd);

sys_delay(1000);

sprintf(buf,"%d",gpio);
fd = open("sys/class/gpio/unexport", O_WRONLY);
write(fd, buf, strlen(buf));
close(fd);

return 0;
}

#include <unistd.h>
#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  
#include <unistd.h>  
#include <netinet/ip.h>  
#include <linux/if_ether.h>  
#include <linux/if_tun.h>
#include <linux/if.h>
#include <fcntl.h>
#include <sys/ioctl.h>

int tun_alloc(char dev[IFNAMSIZ]) {
  struct ifreq ifr;
  int fd, err;

  if ((fd = open("/dev/net/tun", O_RDWR)) < 0) {  // 打开文件
    perror("open");
    return -1;
  }

  bzero(&ifr, sizeof(ifr));
  ifr.ifr_flags = IFF_TUN | IFF_NO_PI;  // tun设备不包含以太网头部

  if (*dev) {
    strncpy(ifr.ifr_name, dev, IFNAMSIZ);
  }

  if ((err = ioctl(fd, TUNSETIFF, (void *) &ifr)) < 0) {  // 打开设备
    perror("ioctl TUNSETIFF");
    close(fd);
    return err;
  }
  strcpy(dev, ifr.ifr_name);
  return fd;
}

int main(int argc, char *argv[]) {
    char tun_name[IFNAMSIZ];
    tun_name[0] = '\0';
    tun_alloc(tun_name);
    getchar();
    return 0;
}

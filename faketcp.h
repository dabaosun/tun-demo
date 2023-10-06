#include <algorithm>  // std::swap

#include <assert.h>
#include <stdint.h>
#include <string.h>
#include <arpa/inet.h>  // inet_ntop
#include <net/if.h>

struct SocketAddr
{
  uint32_t saddr, daddr;  // 源地址和目的地址
  uint16_t sport, dport;  // 源端口和目的端口

  bool operator==(const SocketAddr& rhs) const
  {
    return saddr == rhs.saddr && daddr == rhs.daddr && 
        sport == rhs.sport && dport == rhs.dport;
  }

  bool operator<(const SocketAddr& rhs) const
  {
    return memcmp(this, &rhs, sizeof(rhs)) < 0;
  }
};

int tun_alloc(char dev[IFNAMSIZ]);
uint16_t in_checksum(const void* buf, int len);

void icmp_input(int fd, const void* input, const void* payload, int len);


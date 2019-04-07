#ifndef LIBC_ARPA_INET_H
#define LIBC_ARPA_INET_H 1

#include <inttypes.h>

#ifndef HAS_INPORT_T
typedef uint16_t in_port_t;
#define HAS_INPORT_T 1
#endif

#ifndef HAS_INADDR_T
typedef uint32_t in_addr_t;
struct in_addr{
  in_addr_t s_addr;
};
#define HAS_INADDR_T 1
#endif

#ifndef HAS_IN6_ADDR
struct _in6_addr{
  union{
    uint8_t  __u6_addr8[16];
    uint16_t __u6_addr16[8];
    uint32_t __u6_addr32[4];
  } __in6_u;

};
#define HAS_IN6_ADDR 1
#endif

#ifndef HAS_INET_ADDRSTRLEN
#define INET_ADDRSTRLEN         16 //Length of the string form for IP
#define HAS_INET_ADDRSTRLEN 1
#endif

#ifndef HAS_INET6_ADDRSTRLEN
#define INET6_ADDRSTRLEN         64 //Length of the string form for IP
#define HAS_INET6_ADDRSTRLEN 1
#endif

uint32_t htonl(uint32_t);
uint16_t htons(uint16_t);
uint32_t ntohl(uint32_t);
uint16_t ntohs(uint16_t);

in_addr_t    inet_addr(constchar *);
char        *inet_ntoa(struct in_addr);
const char  *inet_ntop(int, const void *restrict, char *restrict,socklen_t);
int          inet_pton(int,const char *restrict, void *restrict);



#endif

#ifndef LIBC_NETINET_IN_H
#define LIBC_NETINET_IN_H 1

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

#define IPPROTO_IP         0      //  Internetprotocol.
#define IPPROTO_ICMP       1      //  Control message protocol.
#define IPPROTO_TCP        6      //  Transmission control protocol.
#define IPPROTO_UDP       17      //  Userdatagram protocol.
#define IPPROTO_IPV6      41      // Internet Protocol Version 6.
#define IPPROTO_RAW       255    // Raw IP Packets Protocol.

/* Address to accept any incoming messages.  */
#define        INADDR_ANY                ((in_addr_t) 0x00000000)
/* Address to send to all hosts.  */
#define        INADDR_BROADCAST        ((in_addr_t) 0xffffffff)
/* Address indicating an error return.  */
#define        INADDR_NONE                ((in_addr_t) 0xffffffff)

#ifndef HAS_INET_ADDRSTRLEN
#define INET_ADDRSTRLEN         16 //Length of the string form for IP
#define HAS_INET_ADDRSTRLEN 1
#endif

#ifndef HAS_INET6_ADDRSTRLEN
#define INET6_ADDRSTRLEN         64 //Length of the string form for IP
#define HAS_INET6_ADDRSTRLEN 1
#endif

#endif

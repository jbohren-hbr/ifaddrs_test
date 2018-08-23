/*
 * Simple test to show ip addresses as retrived by getifaddrs().
 * Author: Jonathan Bohren <jrbohren@honeybeerobotics.com>
 * 
 * See licensing terms in-line.
 */

#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/in.h>
#include <linux/if.h>
#include <ifaddrs.h>
#include <linux/if_packet.h>
#include <string.h>

/**
 * `print_sockaddr` is derived from StackOverflow answer:
 * https://stackoverflow.com/a/18949572
 * This code is implictily licensed under CC-BA-SA according to the
 * StackOverflow meta post:
 * https://meta.stackexchange.com/questions/271080/the-mit-license-clarity-on-using-code-on-stack-overflow-and-stack-exchange
**/
void
print_sockaddr(struct sockaddr* addr,const char *name)
{
  char addrbuf[128] ;

  addrbuf[0] = 0;
  if(addr->sa_family == AF_UNSPEC)
    return;

  switch(addr->sa_family) {
    case AF_INET:
      inet_ntop(addr->sa_family,&((struct sockaddr_in*)addr)->sin_addr,
          addrbuf,sizeof(struct sockaddr_in));
      break;
      break;
    case AF_INET6:
      inet_ntop(addr->sa_family, &((struct sockaddr_in6*)addr)->sin6_addr,
          addrbuf,sizeof(struct sockaddr_in6));
      break;
    default:
      sprintf(addrbuf,"Unknown family (%d)",(int)addr->sa_family);
      break;

  }
  printf("%-16s %s\n",name,addrbuf);
}


/*
 * This code is derived from the Gazebo project (gazebosim.org), and is subject
 * to the following license:
 *
 * Copyright (C) 2012 Open Source Robotics Foundation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
*/
int main(int argc, char** argv) {
    // the following is *nix implementation to get the external IP of the
    // current machine.

    struct ifaddrs *ifaddr, *ifa;

    int up_only = (argc > 1) ? (strcmp(argv[1],"up") == 0) : (0);

    // Get interface addresses
    if (getifaddrs(&ifaddr) == -1) {
      return 1;
    }

    // Iterate over all the interface addresses
    for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next)
    {
      if (up_only && !(ifa->ifa_flags & IFF_UP))
        continue;
      if (ifa->ifa_addr == NULL)
        continue;
       
      int family = ifa->ifa_addr->sa_family;
      if (family == AF_INET) {
        print_sockaddr(ifa->ifa_addr, ifa->ifa_name);
      }
    }

    freeifaddrs(ifaddr);
    return 0;
}

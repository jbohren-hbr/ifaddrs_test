#!/usr/bin/env bash

#IFCONFIG_IFACES="$(ifconfig | grep -B1 "inet addr" | grep " Link" | cut -d' ' -f1)"
GETIFADDRS_IFACES="$(./build/print_ifaddrs up | cut -d' ' -f1 | sort)"
NETSTAT_IFACES="$(netstat -i | tail -n +3 | cut -d' ' -f1 | sort)"
IPLINK_IFACES="$(ip link show | grep '<' | cut -d' ' -f2 | cut -d':' -f1 | sort)"
IPLINK_UP_IFACES="$(ip link show up | grep '<' | cut -d' ' -f2 | cut -d':' -f1 | sort)"

if [[ $IPLINK_UP_IFACES == $GETIFADDRS_IFACES ]] ; then
  >&2 echo "matching."
  exit 0
else
  >&2 echo "not matching."
  >&2 echo -e "$(diff <(echo "$GETIFADDRS_IFACES") <(echo "$NETSTAT_IFACES"))"
  exit 1 
fi

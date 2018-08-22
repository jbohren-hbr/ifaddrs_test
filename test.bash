#!/usr/bin/env bash

GETIFADDRS_IFACES="$(./build/print_ifaddrs | cut -d' ' -f1 | sort)"
IFCONFIG_IFACES="$(ifconfig | grep -B1 "inet addr" | grep " Link" | cut -d' ' -f1)"

if [[ $GETIFADDRS_IFACES == $IFCONFIG_IFACES ]] ; then
  >&2 echo "matching."
  exit 0
else
  >&2 echo "not matching."
  >&2 echo -e "$(diff <(echo "$GETIFADDRS_IFACES") <(echo "$IFCONFIG_IFACES"))"
  exit 1 
fi

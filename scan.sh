#!/bin/sh

set -euo pipefail

i=0

until [ $i -gt 4095 ]
do
  printf "sending command '%X'\n" $i

  ./onkyo-send-command $i

  ((i=i+1))
  sleep 0.1
done

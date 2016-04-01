#!/bin/bash

exec 3<>/dev/tcp/127.0.0.1/${1} && echo -e ${2} >&3 && exec 3<&-


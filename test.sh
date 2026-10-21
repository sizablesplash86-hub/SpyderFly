#!/bin/bash

if ! ls /etc/spyderfl &> /dev/null; then
    echo "example command failed"
else
    echo "example command succeeded"
fi

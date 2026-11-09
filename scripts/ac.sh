# this is for independently testing the auto config

rm tests/auto-config
gcc src/auto-config/*.c src/auto-config/testing/main.c -o tests/auto-config
./tests/auto-config

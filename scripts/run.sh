sudo rm /usr/sbin/spyderfly
gcc src/core/*.c src/auto-config/*.c -o /usr/sbin/spyderfly -lssl -lcrypto
sudo spyderfly

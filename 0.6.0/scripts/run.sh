sudo rm /usr/sbin/spyderfly
gcc src/*.c -o /usr/sbin/spyderfly -lssl -lcrypto
sudo spyderfly

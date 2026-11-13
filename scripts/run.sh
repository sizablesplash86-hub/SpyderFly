sudo rm /usr/sbin/spyderfly
gcc $(find src/ -name "*.c") -o /usr/sbin/spyderfly -lssl -lcrypto -lcurl
sudo spyderfly

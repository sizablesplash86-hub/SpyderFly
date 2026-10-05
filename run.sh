sudo fuser -k -9 5768/tcp
sudo fuser -k -9 5768/tcp
sudo fuser -k -9 25569/tcp
sudo fuser -k -9 25569/tcp
rm spyderfly
cd 0.4.0/build/
cmake --build .
mv spyderfly ..
cd ..
mv spyderfly ..
cd ..
./spyderfly

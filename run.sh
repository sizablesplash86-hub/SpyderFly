sudo fuser -k 2026/tcp

rm spyderfly
cd 0.4.0/build/
cmake --build .
mv spyderfly ..
cd ..
mv spyderfly ..
cd ..
./spyderfly

if [ $1 == "c" ]; then
	clear
fi

./clean.sh
echo "1 >-------------->"
./build.sh
echo "2 >-------------->"
./qemu.sh
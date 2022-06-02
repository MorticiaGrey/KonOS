if [ $1 == "c" ]; then
	clear
fi

./build.sh
echo ">-------------->"
./qemu.sh
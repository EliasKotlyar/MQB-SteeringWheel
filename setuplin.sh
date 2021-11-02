## Init Lin etc:
config-pin P2_22 hi # Enable LIN-Bus1
config-pin P2_19 hi # Enable Power for LIN
cd /work/linux-lin
sudo insmod /work/linux-lin/sllin/sllin.ko
sudo ./slcan_attach -w /dev/ttyS4
sudo ip link set sllin0 up
ip link show dev sllin0
candump sllin0

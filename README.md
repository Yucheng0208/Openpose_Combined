# Reference
* Software
  * JSON parser from: <https://github.com/udp/json-parser> <br >
  * Openpose from: <https://github.com/CMU-Perceptual-Computing-Lab/openpose> <br >
  * TCP/IP Socket: <https://github.com/Yucheng0208/TCP_Socket> <br >
  * Ubuntu Version: Ubuntu LTS 18.04 <br >
* Hardware
  * Raspberry Pi: 3B+ 4GB. <br >
  * Desktop: CPU i9-9900KF, GPU RTX-2060(2 sets), RAM DDR4-3200 32GB(2 sets), SSD 1TB,and HDD 2TB.
    * this desktop has a dual system. <br >

# Turn-On Systrm
## Raspberry Pi (Server)
1. Search Raspberry Pi's HOST/IP (Touch on Wi-Fi Icon, or Raspberry Pi's Terminal is key-in `ip a`). <br >
2. Open Raspberry Pi's Termial. <br >
3. Raspberry Pi's Termial key-in `cd Desktop`, goto Desktop. <br >
4. Raspberry Pi's Termial key-in `python3 raspberry_pi_control.py`, running progarm. <br >

## Dektop (Client)
1. Open Ubuntu PC's Terminator.
2. Ubuntu PC's Terminator key in `cd openpose_combined`, goto openpose_combined directory. <br >
3. Open "main.c", and write HOST/IP (Raspberry Pi HOST/IP). <br >
4. Ubuntu PC's Terminator key-in `gcc main.c json.c -lm`, will be building program main.c. <br >
5. Ubuntu PC's Terminator key-in `cd ..`,it back to upper layer directory, until key-in `ll` can look for openpose directory. <br >
7. Ubuntu PC's Terminator key-in `cd openpose`, goto openpose directory. <br >
8. Ubuntu PC's Terminator key-in `./test "./build/examples/openpose/openpose.bin --write_json /home/Yu.Cheng/openpose_combined/json >/dev/null 2>/dev/null" "/home/Yu.Cheng/openpose_combined/a.out" 2>/dev/null`, running system all. <br >
* **Notice: The paths and instructions in the program need to be changed according to the computer environment.** <br >

# Turn-Off System
1. Ubuntu PC's Camera form key in `esc`, will be stop program openpose Camera-Fram. <br >
2. Ubuntu PC's Terminator key-in `ctrl+c`, will be close program openpoe and openpose_combined. <br >
3. Raspberry Pi's Termial key-in `ctrl+c` will be break Tcp/IP and close program raspberry_pi_control.py. <br >

   
# Reference
* Software
  * JSON parser from: <https://github.com/udp/json-parser>. <br >
  * Openpose from: <https://github.com/CMU-Perceptual-Computing-Lab/openpose>. <br >
  * TCP/IP Socket: <https://github.com/Yucheng0208/TCP_Socket>. <br >
  * Ubuntu 18.04 LTS: <https://ftp.ubuntu-tw.org/ubuntu-releases/18.04.6/ubuntu-18.04.6-desktop-amd64.iso>. <br >
* Hardware
  * Raspberry Pi: 3B+ 4GB. <br >
  * Desktop: CPU i9-9900KF, GPU RTX-2060(2 sets), RAM DDR4-3200 32GB(2 sets), SSD 1TB,and HDD 2TB.
    * This desktop has a dual system. <br >
    
# Turn-On System
## Raspberry Pi (Server)
1. Search Raspberry Pi's HOST/IP (Touch on Wi-Fi Icon, or Raspberry Pi's Terminal is key-in `ip a`). <br >
2. Open Raspberry Pi's Terminal. <br >
3. Raspberry Pi's Terminal key-in `cd Desktop`, goto Desktop. <br >
4. Raspberry Pi's Terminal key-in `python3 raspberry_pi_control.py`, running program(`raspberry_pi_control.py`). <br >
   * Python version is very important, key-in `python3 -v` or `python -v` to check your Python version default set.  <br >
## Desktop (Client)
1. Open PC's Terminator or Terminal.
2. PC's Terminator key in `cd openpose_combined`, goto openpose_combined directory. <br >
3. Open "main.c", and write HOST/IP (Raspberry Pi HOST/IP). <br >
4. PC's Terminator key-in `gcc main.c json.c -lm`, will be building program `main.c`. <br >
5. PC's Terminator key-in `cd ..`,it back to upper layer directory, until key-in `ll` can look for openpose directory. <br >
6. PC's Terminator key-in `cd openpose`, goto openpose directory. <br >
7. PC's Terminator key-in `./test "./build/examples/openpose/openpose.bin --write_json /home/Yu.Cheng/openpose_combined/json >/dev/null 2>/dev/null" "/home/Yu.Cheng/openpose_combined/a.out" 2>/dev/null`, running system all (`openpose` and `openpose_combined`). <br >
   * **Notice: The paths and instructions in the program need to be changed according to the computer environment.** <br >

# Turn-Off System
1. Ubuntu PC's Camera form click `esc`, will be stop program openpose Camera-Frame. <br >
2. Ubuntu PC's Terminator click `Ctrl+c`, will be close program openpose and `openpose_combined`. <br >
3. Raspberry Pi's Terminal click `Ctrl+c` will be break Tcp/IP and close program `raspberry_pi_control.py`. <br >
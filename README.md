JSON parser from: https://github.com/udp/json-parser<br >
Openpose from: https://github.com/CMU-Perceptual-Computing-Lab/openpose<br >

# 開啟系統(Turn-On Systrm)

## 樹莓派伺服器 (Raspberry Pi-Server)

1. Search Raspberry Pi's HOST/IP (Touch on Wi-Fi Icon, or Raspberry Pi's Terminal is key-in `ip a`).
2. Open Raspberry Pi's Termial.
3. Raspberry Pi's Termial key-in `cd Desktop`, goto Desktop.
4. Raspberry Pi's Termial key-in `python3 raspberry_pi_control.py`, running progarm.

## 影像處理器 (Ubuntu LTS 18.04-Ubuntu PC/Detect Images Client)

1. Open Ubuntu PC's Terminator.
2. Ubuntu PC's Terminator key in `cd openpose_combined`, goto openpose_combined directory.
3. Open "main.c", and write HOST/IP (Raspberry Pi HOST/IP).
4. Ubuntu PC's Terminator key-in `gcc main.c json.c -lm`, will be building program main.c.
5. Ubuntu PC's Terminator key-in `cd ..`,it back to upper layer directory, until key-in `ll` can look for openpose directory.
7. Ubuntu PC's Terminator key-in `cd openpose`, goto openpose directory.
8. Ubuntu PC's Terminator key-in `./test "./build/examples/openpose/openpose.bin --write_json /home/Yu.Cheng/openpose_combined/json >/dev/null 2>/dev/null" "/home/Yu.Cheng/openpose_combined/a.out" 2>/dev/null`, running system all.

# 關閉系統(Turn-Off System)

1. Ubuntu PC's Camera form key in `esc`, will be stop program openpose Camera-Fram.
2. Ubuntu PC's Terminator key-in `ctrl+c`, will be close program openpoe and openpose_combined.
3. Raspberry Pi's Termial key-in `ctrl+c` will be break Tcp/IP and close program raspberry_pi_control.py.

   
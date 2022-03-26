#!/usr/bin/python
# -*- coding: UTF-8 -*-

# Create the TCP server
def create_tcp_server(host,port):
    # create socket
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_address = (host, port)
    # bind port
    sock.bind((server_address))
    # listen
    sock.listen(1)
    # Receive client send data
    conn, addr = sock.accept()
    # Buffer size setup
    BUFFER_SIZE = 4

    # Raspberry pi pin setup
    GPIO.setmode(GPIO.BOARD)
    GPIO.setup(7, GPIO.OUT)  # Green light
    GPIO.setup(11, GPIO.OUT) # Yellow light
    GPIO.setup(12, GPIO.OUT) # Red light and Buzzer
    GPIO.setup(13, GPIO.OUT) # Machine

    while True:
        # Receive client send data save to the string"data"
        data = conn.recv(BUFFER_SIZE)

        # If not receive data,the while can break(exit) program
        if not data: break

        # The data is the "bytes", you can decoding to "UTF-8"
        data_decode = data.decode("UTF-8")

        # Module settings: Sit
        if data_decode == '0101':
            print("休息中，1號崗位電源已關閉") # sit
            GPIO.output(7,True)     # Green light is Turn off
            GPIO.output(11,False)   # Yellow light is Turn on
            GPIO.output(12,False)   # Red light and Buzzer are Turn off
            GPIO.output(13,False)   # Machine is Turn off
        # Module settings: Working
        elif data_decode == '0102':
            print("工作中") # 坐姿半舉
            GPIO.output(7,True)     # Green light is Turn off
            GPIO.output(11,False)   # Yellow light is Turn on
            GPIO.output(12,False)   # Red light and Buzzer are Turn off
            GPIO.output(13,True)    # Machine is Turn off

        # Module settings: Sit and raise hands
        elif data_decode == '0103':
            print("警告：1號崗位向您提問，電源已關閉！！！")
            print("請至現場協助與查看")
            GPIO.output(7,False)    # Green light is Turn off
            GPIO.output(11,True)    # Yellow light is Turn on
            GPIO.output(12,False)   # Red light and Buzzer are Turn off
            GPIO.output(13,False)   # Machine is Turn off

        # Module settings: Stand
        elif data_decode == '0104':
            print("注意：1號崗位休息中，電源已關閉")
            GPIO.output(7,True)     # Green light is Turn off
            GPIO.output(11,False)   # Yellow light is Turn on
            GPIO.output(12,False)   # Red light and Buzzer are Turn off
            GPIO.output(13,False)   # Machine is Turn off

        # Module settings: Stand and Raise hands
        elif data_decode == '0105':
            print("警告：1號崗位向您提問，電源已關閉！！！")
            GPIO.output(7,False)    # Green light is Turn off
            GPIO.output(11,True)    # Yellow light is Turn on
            GPIO.output(12,False)   # Red light and Buzzer are Turn off
            GPIO.output(13,False)   # Machine is Turn off

        # Module settings: Lie down
        elif data_decode == '0106':
            print("警告：1號崗位躺下，電源已關閉！！！")
            print('請至現場查看並求救！！！')
            GPIO.output(7,False)    # Green light is Turn off
            GPIO.output(11,False)   # Yellow light is Turn off
            GPIO.output(12,True)    # Red light and Buzzer are Turn on
            GPIO.output(13,False)   # Machine is Turn off

# Main
def main():
    create_tcp_server('0.0.0.0',2000)

if __name__ == '__main__':
    main()
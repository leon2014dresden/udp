import socket
import json
BUFSIZE = 1024
ip_port = ('127.0.0.1', 9999)
server = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)  # udp协议
server.bind(ip_port)
i = 0
while True:
    data,client_addr = server.recvfrom(BUFSIZE)
    data = json.loads(data)
    print("index: ", i)
    if data.__contains__("age"):
        print("age: ", data["age"])
    print('server收到的数据', data)
    #server.sendto(data.upper(),client_addr)
    i += 1
server.close()
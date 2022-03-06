import socket
import json
BUFSIZE = 1024
client = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
while True:
    msg = {
    "firstName": "Jane",
    "lastName": "Doe",
    "hobbies": ["running", "sky diving", "singing"],
    "age": 35,
    "children": [
        {
            "firstName": "Alice",
            "age": 6
        },
        {
            "firstName": "Bob",
            "age": 8
        }
    ]
}
    msg = json.dumps(msg)
    ip_port = ('127.0.0.1', 9999)
    client.sendto(msg.encode('utf-8'),ip_port)
 
    #data,server_addr = client.recvfrom(BUFSIZE)
    #print('客户端recvfrom ',data,server_addr)
 
client.close()
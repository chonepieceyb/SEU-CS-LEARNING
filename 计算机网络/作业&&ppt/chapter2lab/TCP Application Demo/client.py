import socket

if __name__ =='__main__':
    hostname = "localhost"         # 服务器 IP
    port = "20000"                 # 服务器端口号

    # 新建socket , AN_INET 表明使用 IPv4协议， SOCK_STREAM 表明使用TCP服务
    client_socket = socket.socket(socket.AN_INET,socket.SOCK_STREAM)

    # 和服务器建立连接
    client_socket.connect((hostname,port))

    #用户输入
    sentence = input('input sentence')

    #通过socket 将输入发送给服务器
    client_socket.send(sentence.encode())

    #接收来自服务器的数据
    buffer = []
    while True:
        # 每次接收1k字节， 1024 指定字节大小
        d = client_socket.recv(1024)
        if d:
            buffer.append(d)
        else :
            break;          #接收完成
    message = b''.join(buffer)   #接收得到数据
    # 完成连接关闭 TCP
    client_socket.close()
    print(message.decode())




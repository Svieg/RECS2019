import socketserver

def check(user_data):
    """ Encryption method for the registration server."""
    user_data = user_data.decode()
    inc_data = [chr(ord(c)+1) for c in user_data]
    checksum = 0
    for i in range(len(inc_data)//2):
        checksum += ord(inc_data[i]) ^ ord(inc_data[i+1])
    if checksum == 338:
        return True
    else:
        return False

class RegistrationServerHandler(socketserver.BaseRequestHandler):
    """ Handler class for the device registration server."""
    def handle(self):
        self.data = self.request.recv(1024).strip()
        print("{} wrote:".format(self.client_address[0]))
        print(self.data)
        if check(self.data):
            self.request.sendall(b"FLAG-2f7018891e2856066a47fb7d93a7f305\n")
        else:
            self.request.sendall(b"INVALID REGISTRATION KEY\nThis incident will be reported.\nDEBUG: Checksum should be equal to 338.")

if __name__ == "__main__":
    HOST, PORT = "localhost", 2019

    # Create the server, binding to localhost on port 2019
    server = socketserver.TCPServer((HOST, PORT), RegistrationServerHandler)
    server.serve_forever()

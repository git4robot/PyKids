#https://www.digitalocean.com/community/tutorials/how-to-work-with-the-zeromq-messaging-library

import zmq

# ZeroMQ Context
context = zmq.Context()

# Define the socket using the "Context"
sock = context.socket(zmq.REP)
sock.bind("tcp://127.0.0.1:5678")

# Run a simple "Echo" server
while True:
    message = sock.recv()
    sock.send("Echo: " + message.encode('ascii'))
    print("Echo: " + message)
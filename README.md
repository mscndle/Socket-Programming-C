Implementations completed - 

1. Simple streaming TCP server

Telnet to the host that the server is running on and it will return a "Hello Client!" message.

2. Simple streaming TCP client
   Client that prints out the messages sent by the server
   Currently there is a bug in this implementation - 9/10/14
<code>
    mscndle$ ./tcpclient<br>
    client socket descriptor: 4<br>
    Attempting to connect now...<br>
    yay. connected!<br>
    client: connecting to 0.0.0.0<br>
    Segmentation fault: 11<br>
</code>
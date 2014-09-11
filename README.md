Implementations completed - 

1. Simple streaming TCP server

    Telnet to the host that the server is running on and it will return a "Hello Client!" message.

2. Simple streaming TCP client
    Client that prints out the messages sent by the server.
    Currently there is a bug in this implementation - 9/10/14
<pre>
<code>
    mscndle$ ./tcpclient
    client socket descriptor: 4
    Attempting to connect now...
    yay. connected!
    client: connecting to 0.0.0.0
    Segmentation fault: 11
</code>
</pre>
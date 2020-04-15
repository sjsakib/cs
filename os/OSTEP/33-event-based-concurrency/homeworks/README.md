# Operating systems Three Easy Pieces: Chapter 33 solution

## Question 1
[tcp.c](./tcp.c)

Serves one connection at a time. Other connections wait while one connection is not fully done. Usages:

`./tcp.c`

In another shell, while running:

```
telnet localhost 8080

Trying 127.0.0.1...
Connected to localhost.
Escape character is '^]'.

Henlo!
Server time: 14 Apr 2020 11:07

hi # <- input
hi you # <- response

bye
Connection closed by foreign host.
```

## Question 2

[multi-tcp.c](./multi-tcp.c)

Can serve other connections while waiting for input in one. One interesting mistake that I made was not using `FD_CLR` after closing a connection. That causes the loop keep running even when there is not active connection.

## Question 4

[aio-file-tcp.c](./aio-file-tcp.c)

Apart from the cumbersome API C provides for doing stuff, incorporating async I/O was not that hard for this simple use case.

## Question 6

Event based async approaches are worth it when the concurrency is too high, like thousands of connections. Using thousands of threads would be very expensive. And if the computation needed to serve a connection isn't too high, async approach is definitely the way to go. And if there is heavy computation to be done for any connection, that can be done in a separate thread.

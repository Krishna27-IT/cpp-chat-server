# C++ Chat Server

A TCP chat server built from scratch in C++ using the Windows Winsock API. This project is being developed incrementally to understand low-level networking, socket programming, and server architecture rather than relying on high-level networking libraries.

## Current Progress

### Milestone 1 – Server Initialization ✅

The server can:

* Initialize the Winsock library
* Create a TCP socket
* Bind to `127.0.0.1:8080`
* Start listening for incoming client connections
* Handle initialization errors using a fail-fast approach

## Technologies

* C++
* Winsock2
* Windows Socket API
* Object-Oriented Programming

## Project Structure

```text
.
├── main.cpp
├── Server.h
├── Server.cpp
```

## Concepts Learned

* Winsock initialization (`WSAStartup`)
* Socket creation
* IPv4 addressing (`AF_INET`)
* TCP sockets (`SOCK_STREAM`)
* Socket binding
* Listening sockets
* Network byte order (`htons`)
* Basic server architecture
* Separation of interface (`.h`) and implementation (`.cpp`)

## Planned Features

* Accept client connections
* Multi-client support
* Client management
* Broadcast messaging
* Username system
* Private messaging
* Threading
* Graceful client disconnect handling
* Chat history
* Persistent storage

## Build

Compile with MinGW:

```bash
g++ main.cpp Server.cpp -o main -lws2_32
```

Run:

```bash
./main
```

## Learning Goal

This project is focused on understanding how TCP servers work internally by implementing each networking component step by step, from socket creation to handling multiple simultaneous clients.

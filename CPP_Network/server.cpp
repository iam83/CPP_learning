#include <iostream>
#include <winsock2.h>


int main() {
    // Initialize Winsock
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Failed to initialize Winsock\n";
        return 1;
    }

    // Create a socket
    SOCKET server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == INVALID_SOCKET) {
        std::cerr << "Socket creation failed\n";
        WSACleanup();
        return 1;
    }

    // Bind the socket to an IP address and port
    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);
    if (bind(server_socket, (struct sockaddr *)&address, sizeof(address)) == SOCKET_ERROR) {
        std::cerr << "Bind failed\n";
        closesocket(server_socket);
        WSACleanup();
        return 1;
    }

    // Listen for incoming connections
    if (listen(server_socket, 3) == SOCKET_ERROR) {
        std::cerr << "Listen failed\n";
        closesocket(server_socket);
        WSACleanup();
        return 1;
    }

    // Accept a new connection
    int addrlen = sizeof(address);
    SOCKET client_socket = accept(server_socket, (struct sockaddr *)&address, &addrlen);
    if (client_socket == INVALID_SOCKET) {
        std::cerr << "Accept failed\n";
        closesocket(server_socket);
        WSACleanup();
        return 1;
    }

    // Send a message to the client
    const char *message = "Hello from server!";
    if (send(client_socket, message, strlen(message), 0) == SOCKET_ERROR) {
        std::cerr << "Send failed\n";
        closesocket(client_socket);
        closesocket(server_socket);
        WSACleanup();
        return 1;
    }
    std::cout << "Message sent to client\n";

    // Close the sockets
    closesocket(client_socket);
    closesocket(server_socket);
    WSACleanup();

    system("pause");
    return 0;
}
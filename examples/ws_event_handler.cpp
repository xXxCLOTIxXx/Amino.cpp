#include "Amino/Client.h"


void on_text_message(json data){
    std::cout << "Text message in chat" << std::endl;
}


void on_chat_message(json data){
    std::cout << "some message in chat" << std::endl;
    std::cout << data << std::endl;
}

int main() {
    Client client;
    std::cout << "All types of events: " << std::endl;
    std::vector<std::string>vec = EventTypes::all_ws_types();
    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << vec[i] << std::endl;
    }

    client.login("email@gmail.com", "password");
    client.ws_socket.addHandler("on_text_message", on_text_message);
    client.ws_socket.addHandler("chat_message", on_chat_message);

    client.wait();
}
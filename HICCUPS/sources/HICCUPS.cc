#include <HICCUPS.hh>

namespace HICCUPS {

HICCUPS::HICCUPS(const std::string &interface):
    WLAN(interface) {}

void HICCUPS::HDC3_send(const Network::MACAddress &addr, Crypto::DataLoader &dload, const std::string &path) {
    if (ifconfig.mtu < 281)
        throw std::runtime_error("MTU less than needed header size");

    std::string data = Crypto::DataLoader::load(path);

    for (std::size_t idx = 0, end_idx = data.size(), step = ifconfig.mtu - 281, i = 0; idx < end_idx; idx += step, ++i) {

        std::string dpart = "";
        dpart.resize(std::min(ifconfig.mtu - 14 - 11 - path.length(), data.size() - idx));
        for (std::size_t j = 0; j < step; ++j)
            dpart[j] = data[idx + j];

        RawData raw;
        // std::cout << path << " = " << path.size() << " | " << " = " << dpart.size() << std::endl;
        raw.set_name(path) ;
        raw.set_data(dpart);
        raw.type = 0;
        raw.packet_num = i;
        raw.is_end = (idx + step > end_idx);
        raw.crc_calc();

        std::string etext = dload.chipper_text(raw.to_string());

        std::cout << i << std::endl;
        send(addr, etext);        
    }
}

void HICCUPS::HDC3_recv(const Network::MACAddress &addr, Crypto::DataLoader &dload, const std::string &path) {
    std::string result_msg = "";
    std::vector<std::string> listen_msgs;

    char *recv_msg = new char[ifconfig.mtu];
    struct sockaddr_ll from;
    socklen_t fromlen = sizeof(from);

    std::size_t count = 0;
    bool exit = false;

    for (;;) {
        for (;;) {
            std::memset(recv_msg, 0, ifconfig.mtu);
            if (recvfrom(ifconfig.socket_id, recv_msg, ifconfig.mtu, 0, (struct sockaddr *)&from, &fromlen) == -1) {
                std::cout << "Can not recv msg" << std::endl;
                usleep(10000);
            } else {
                break;
            }
        }

        Network::MACAddress my_addr = ifconfig.MAC; 

        WLAN_header *wlan_hdr = (WLAN_header *)recv_msg;
        bool is_for_me = true;
        for (std::size_t i = 0; i < 6; ++i) {
            is_for_me &= ((wlan_hdr-> src.addr[i]  == addr.addr[i]) 
                      &&  (wlan_hdr->dest.addr[i]  == my_addr.addr[i]));
        }
        
        if (is_for_me) {
            ++count;
            std::string msg = std::string(recv_msg + wlan_hdr->size);

            std::string new_buffer = dload.dechipper_text(msg);

            std::size_t offset = new_buffer[6];
            for (std::size_t i = 7 + offset, end_i = msg.size() - sizeof(std::uint32_t); i < end_i; ++i)
                result_msg += msg[i];

            std::cout << result_msg << std::endl;

            if (new_buffer[5] == 1 || count == 187) {
                exit = true;
                break;
            }
        }
        if (exit) break;
    }
    delete[] recv_msg;

    Crypto::DataLoader::save(result_msg, path);
}

}
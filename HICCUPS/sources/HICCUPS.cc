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
        dpart.resize(std::min(ifconfig.mtu - 14, data.size() - idx));
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

        for (int j = 0, end_j = etext.size(); j < end_j; ++j) {
            printf("%02x", etext[j]);
        }
        printf("\n");

        send(addr, etext);        
    }
}

void HICCUPS::HDC3_recv(const Network::MACAddress &addr, Crypto::DataLoader &dload, const std::string &path) {
    std::string result_msg = "";

    char *recv_msg = new char[ifconfig.mtu];
    struct sockaddr_ll from;
    socklen_t fromlen = sizeof(from);
    
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

        Network::MACAddress my_addr; 
        struct ifreq s;
        int fd = socket(PF_INET, SOCK_DGRAM, IPPROTO_IP);
        strcpy(s.ifr_name, interface.data());
        if (!ioctl(fd, SIOCGIFHWADDR, &s)) {
            for (std::size_t i = 0, end_i = Network::MACAddress::size(); i < end_i; ++i)
                my_addr.addr[i] = (unsigned char)s.ifr_addr.sa_data[i];
        } else {
            throw std::runtime_error("Can\'t get recver MAC");
        }
        close(fd);

        WLAN_header *wlan_hdr = (WLAN_header *)recv_msg;
        bool is_for_me = true;
        for (std::size_t i = 0; i < 6; ++i) {
            is_for_me &= ((wlan_hdr->src.addr[i]  == addr.addr[i]) 
                      &&  (wlan_hdr->dest.addr[i] == my_addr.addr[i]));
        }
        std::cout << "Source | " << wlan_hdr-> src.to_string() << " | " << addr.to_string() << std::endl;
        std::cout << "Destin | " << wlan_hdr->dest.to_string() << " | " << my_addr.to_string() << std::endl;
        
        if (is_for_me) {
            std::cout << "I hear something good" << std::endl;
        }

    }
    delete[] recv_msg;
}

}
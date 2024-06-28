import socket
from scapy.all import *

def send_udp_datagram_2(src_port: int, dst_port: int) -> None:
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)  # Use SOCK_DGRAM for standard UDP socket
    ip_addr_to_bind = "192.168.79.129" #
    sock.bind((ip_addr_to_bind, src_port))  # Bind to the source port
    message = b'hello'
    sock.sendto(message, ("127.0.0.1", dst_port))  # Send the UDP packet
    data, address = sock.recvfrom(4096)
    print("recived message from server:" + str(data))

def send_raw_udp_datagram(src_port: int, dst_port: int) -> None:
    
    #conf.L3socket=L3RawSocket # sport=src_port, 
    #packet=IP()/UDP(dport=dst_port)/"HELLO WORLD"
    #send(packet)

    rawudp=socket.socket(socket.AF_INET, socket.SOCK_RAW, socket.IPPROTO_UDP)
    rawudp.bind(('0.0.0.0',56789))
    rawudp.setsockopt(socket.SOL_IP, socket.IP_HDRINCL,1)

    pkt = IP()/UDP(sport=56789, dport=5000)/'hello'

    rawudp.sendto(pkt.build(), ('127.0.0.1',5000))

def send_datagram_packet(src_port: int, dst_port: int) -> None:
    src_mac_address = "AA:BB:CC:DD:EE:FF"
    #tap_interface = "AA:00:BB:11:CC:22"
    ethernet = Ether(dst='ff:ff:ff:ff:ff:ff',src=src_mac_address,type=0x800)
    ip = IP(src ='0.0.0.0',dst='255.255.255.255')
    udp = UDP(sport=int(src_port) ,dport=int(dst_port))
    #fam,hw = get_if_raw_hwaddr(tap_interface)
    #bootp = BOOTP(chaddr = hw, ciaddr = '0.0.0.0',xid =  0x01020304,flags= 1)
    dhcp = DHCP(options=[("message-type","discover"),"end"])
    packet = ethernet / ip / udp /  dhcp # after udp comes bootp
    print("the DHCP packet composed is:" + str(packet))

def send_dhcp_message() -> None:

    if len(sys.argv)<3:
        print ("Not enough argument")
        #return
    else:
        tap_interface = sys.argv[1]
        src_mac_address = sys.argv[2]

    src_mac_address = "AA:BB:CC:DD:EE:FF"
    #tap_interface = "AA:00:BB:11:CC:22"
    ethernet = Ether(dst='ff:ff:ff:ff:ff:ff',src=src_mac_address,type=0x800)
    ip = IP(src ='0.0.0.0',dst='255.255.255.255')
    udp = UDP (sport=68,dport=67)
    #fam,hw = get_if_raw_hwaddr(tap_interface)
    #bootp = BOOTP(chaddr = hw, ciaddr = '0.0.0.0',xid =  0x01020304,flags= 1)
    dhcp = DHCP(options=[("message-type","discover"),"end"])
    packet = ethernet / ip / udp /  dhcp # after udp comes bootp
    print("the DHCP packet composed is:" + str(packet))


#    fd = open('/dev/net/tun','r+')
#    TUNSETIFF = 0x400454ca
#    IFF_TAP = 0x0002
#    IFF_NO_PI = 0x1000
#    mode = IFF_TAP | IFF_NO_PI
#    ifr = struct.pack('16sH', tap_interface, IFF_TAP | IFF_NO_PI)
#    fcntl.ioctl(fd,TUNSETIFF,ifr)


#   while True:
#       sendp(packet, iface = tap_interface)
#       time.sleep(10)


if __name__ == "__main__":
    src_port = str(sys.argv[1])
    dst_port = str(sys.argv[2])
    print("main - got src port:" + str(src_port) + ", dst port:" + str(dst_port))
    send_udp_datagram_2(int(src_port), int(dst_port))
    #send_datagram_packet(src_port, dst_port)
    print("main - end")

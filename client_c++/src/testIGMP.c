#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define GROUP "225.225.225.1"
#define PORT 1510

int main(int argc, char* argv[]) {
    int sdr;

    /* socket creation */
    sdr = socket(AF_INET, SOCK_DGRAM, 0);
    if (sdr < 0) {
        perror("error socket creation \n");
        exit(1);
    }

    /* init receiver struct */
    struct sockaddr_in addr_r;
    memset(&addr_r, 0, sizeof(addr_r));
    addr_r.sin_family = AF_INET;
    addr_r.sin_port = htons(PORT);
    addr_r.sin_addr.s_addr = htonl(INADDR_ANY);

    /* Init group struct */
    struct ip_mreq imr;
    imr.imr_multiaddr.s_addr = inet_addr(GROUP);
    imr.imr_interface.s_addr = INADDR_ANY;

    /* Request registering group */
    if (setsockopt(sdr, IPPROTO_IP, IP_ADD_MEMBERSHIP, &imr, sizeof(imr)) < 0) {
        perror("error setsockopt \n");
        exit(1);
    }

    /* If we reuse a port */
    unsigned int on = 1;
    if (setsockopt(sdr, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) < 0) {
        perror("error reuseaddr\n");
        exit(1);
    }

    /* Bind socket */
    if (bind(sdr, (struct sockaddr *)&addr_r, sizeof(addr_r)) < 0) {
        perror("error bind\n");
        exit(1);
    }

    /* Receive packets */
    int cnt, len_r = sizeof(addr_r);
    char buf[100];
    cnt = recvfrom(sdr, buf, sizeof(buf), 0, (struct sockaddr*)&addr_r, (socklen_t *)&len_r);
    if (cnt < 0) {
        perror("error receive from \n");
        exit(1);
    }

    /* Quit the group */
    if (setsockopt(sdr, IPPROTO_IP, IP_DROP_MEMBERSHIP, &imr, sizeof(imr)) < 0) {
        perror("error quit the group\n");
        exit(1);
    }

    return 0;
}

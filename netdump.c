

/* $Id: netdump.c,v 1.5 2001/09/19 06:15:22 m_sato Exp $ */
/* 
 * netdump.c -- dump all packets received from specified interface
 *
 * this is test program for "linux packet interface" 
 * 
 * see packet(7) and netdevice(7)
 */
#include <features.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <asm/types.h>
#include <sys/types.h>
#include <linux/if_packet.h>
#include <linux/if_ether.h> 
#include <linux/if_arcnet.h> 
#include <linux/version.h>
#include <net/if.h>
#include <net/if_arp.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <signal.h>

#define DEBUG printf

void print_ethaddr(const u_char *p);
void print_arcaddr(const u_char *p);
void hexdump(unsigned char *buf, int nbytes);
void sigint(int);

char *interface = NULL;
int pd = -1;

int 
main(int argc, char **argv)
{
	int c;
	unsigned char buf[2048];
	unsigned char *p;
	struct sockaddr_ll sll;
	int i;
	struct ifreq ifr;
	int ifindex;
	struct sockaddr myaddr;
	int addrlen;

	for (;;) {
		c = getopt(argc, argv, "i:");
		switch (c) {
		case 'i':
			interface = strdup(optarg);
			break;
		case -1:
			break;
		default:
			fprintf(stderr, "usage: rawsock -i interface\n");
			exit(1);
		}
		if (c == -1)
			break;
	}

	if (interface == NULL) {
		fprintf(stderr, "usage: rawsock -i interface\n");
		exit(1);
	}

	signal(SIGINT, sigint);
	
	pd = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
	if (pd == -1) {
		perror("socket():");
		exit(1);
	}

	DEBUG("get interface index: ");

	/* get interface index number */
	memset(&ifr, 0, sizeof(ifr));
	strncpy(ifr.ifr_name, interface, IFNAMSIZ);
	if (ioctl(pd, SIOCGIFINDEX, &ifr) == -1) {
		perror("SIOCGIFINDEX");
		exit(1);
	}
	ifindex = ifr.ifr_ifindex;
	DEBUG("%d\n", ifindex);

	/* get hardware address */
	DEBUG("get hardware address: ");
	memset(&ifr, 0, sizeof(ifr));
	strncpy(ifr.ifr_name, interface, IFNAMSIZ);
	if (ioctl(pd, SIOCGIFHWADDR, &ifr) == -1) {
		perror("SIOCGIFINDEX");
		exit(1);
	}
	myaddr = ifr.ifr_hwaddr;

	switch (myaddr.sa_family) {
	case ARPHRD_ARCNET:
		addrlen = 1;
		break;
	case ARPHRD_ETHER:
		addrlen = 6;
		break;
	default:
		addrlen = sizeof(myaddr.sa_data);
	}

	DEBUG("family = %d, address = ", myaddr.sa_family);

	p = myaddr.sa_data;
	for (i = 0; i < addrlen - 1; i++)
		DEBUG("%02x:", *p++);
	DEBUG("%02x\n", *p);

	DEBUG("set promiscous mode\n");
	memset(&ifr, 0, sizeof(ifr));
	strncpy(ifr.ifr_name, interface, IFNAMSIZ);
	ioctl(pd,SIOCGIFFLAGS,&ifr);
	ifr.ifr_flags|=IFF_PROMISC;
	ioctl(pd,SIOCSIFFLAGS,&ifr);

	DEBUG("bind to %s\n", interface);
	/*
	 * bind(2) uses only sll_protocol and sll_ifindex. see packet(7)
	 */
	memset(&sll, 0xff, sizeof(sll));
	sll.sll_family = AF_PACKET;	/* allways AF_PACKET */
	sll.sll_protocol = htons(ETH_P_ALL);
	sll.sll_ifindex = ifindex;
	if (bind(pd, (struct sockaddr *)&sll, sizeof sll) == -1) {
		perror("bind():");
		exit(1);
	}

	DEBUG("flush receive buffer\n");

	/* 
	 * flush all received packets. 
	 *
         * raw-socket receives packets from all interfaces,
	 * while the socket is not binded to a interface
         */
	do {
		fd_set fds;
		struct timeval t;
		FD_ZERO(&fds);	
		FD_SET(pd, &fds);
		memset(&t, 0, sizeof(t));
		i = select(FD_SETSIZE, &fds, NULL, NULL, &t);
		if (i > 0)
			recv(pd, buf, i, 0);
	} while (i);

	DEBUG("start receiving\n");

	for (;;) {
		i = recv(pd, buf, sizeof(buf), 0);
		if (i < 0) {
			perror("recv():");
			exit(1);
		}
		if (i == 0)
			continue;
		switch (myaddr.sa_family) {
		case ARPHRD_ETHER:
			print_ethaddr(buf);
			break;
		case ARPHRD_ARCNET:
			print_arcaddr(buf);
			break;
		}
		hexdump(buf, i);
	}
	/* NOT REACHED */
	exit(0);
}


void hexdump(unsigned char *p, int count)
{
	int i, j;

	for(i = 0; i < count; i += 16) {
		printf("%04x : ", i);
		for (j = 0; j < 16 && i + j < count; j++)
			printf("%2.2x ", p[i + j]);
		for (; j < 16; j++) {
			printf("   ");
		}
		printf(": ");
		for (j = 0; j < 16 && i + j < count; j++) {
			char c = toascii(p[i + j]);
			printf("%c", isalnum(c) ? c : '.');
		}
		printf("\n");
	}
}


void
print_ethaddr(p)
	const u_char *p;
{
	int i;
	struct ethhdr *eh;

	eh = (struct ethhdr *)p;

	for (i = 0; i < 5; ++i) 
		printf("%02x:", (int)eh->h_source[i]);
	printf("%02x -> ", (int)eh->h_source[i]);

	for (i = 0; i < 5; ++i) 
		printf("%02x:", (int)eh->h_dest[i]);
	printf("%02x", (int)eh->h_dest[i]);
	printf("\n");
}



void
print_arcaddr(p)
	const u_char *p; 
{
	int i;
#if LINUX_VERSION_CODE >= 0x020400
	struct arc_hardware *ah;
	ah = (struct arc_hardware *)p;
	printf("%02x->%02x ", (int)ah->source, (int)ah->dest);
	printf("length = %d\n",
		(ah->offset[0] != 0) ? 256 - ah->offset[0] : 512 - ah->offset[1]);
#else
	struct archdr *ah;
	ah = (struct archdr *)p;
	printf("%02x->%02x ", (int)ah->source, (int)ah->destination);
	printf("length = %d\n",
		(ah->offset1 != 0) ? 256 - ah->offset1 : 512 - ah->offset2);
#endif
}


void
sigint(signum)
	int signum;
{
	struct ifreq ifr;

	if (pd == -1)
		return;

	memset(&ifr, 0, sizeof(ifr));
	strncpy(ifr.ifr_name, interface, IFNAMSIZ);
	ioctl(pd, SIOCGIFFLAGS,&ifr);
	ifr.ifr_flags &= ~IFF_PROMISC;
	ioctl(pd, SIOCSIFFLAGS,&ifr);

	close(pd);
	exit(0);
}

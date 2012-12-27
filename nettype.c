

/* $Id: nettype.c,v 1.7 2001/09/19 06:15:22 m_sato Exp $ */
/* 
 * nettype.c -- chat with specified node
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

#define MAXPACKETLEN 0x10000	/* is it large enough ? */

#define DEBUG printf

void usage();
int buildpacket(unsigned char *buf, struct sockaddr *src, struct sockaddr *dst, const unsigned char *msg, int count);
int sendmessage(int pd, struct sockaddr *src, struct sockaddr *dst, const unsigned char *buf, int count);
int showmessage(struct sockaddr *myaddr, struct sockaddr *peeraddr, unsigned char *buf, int count);
void print_ethaddr(const u_char *p);
void print_arcaddr(const u_char *p);
void hexdump(unsigned char *buf, int nbytes);

int ifindex;
int showhexdump = 0;

int 
main(int argc, char **argv)
{
	int c;
	int pd;
	char *interface;
	unsigned char buf[2048];	/* must be larger than every MTU */
	unsigned char *p;
	struct sockaddr_ll sll;
	int i;
	struct ifreq ifr;
	struct sockaddr myaddr, peeraddr;
	int addrlen;
	int broadcast;
	extern char *optarg;
	char *node;
	char *pattern;
	int send_count, send_wait, send_size;
	int infinite;
	fd_set rfds, wfds;

	interface = NULL;
	broadcast = 0;
	node = NULL;
	pattern = NULL;
	send_count = 1;
	send_wait = 1;
	send_size = 0;
	infinite = 1;

	for (;;) {
		c = getopt(argc, argv, "bc:fi:p:s:xw:");
		switch (c) {
		case 'b':
			broadcast = 1;
			break;
		case 'i':
			interface = strdup(optarg);
			break;
		case 'x':
			showhexdump = 1;
			break;
		case 'p':
			pattern = strdup(optarg);
			break;
		case 'c':
			send_count = atoi(optarg);
			break;
		case 'w':
			send_wait = atoi(optarg);
			break;
		case 's':
			send_size = atoi(optarg);
			break;
                case -1:  
                        if (argv[optind] && *argv[optind] != '-') {
                                node = strdup(argv[optind]);
                                optind++;
                        } 
			/* FALL THROUGH */
                default:
			if (argv[optind] == NULL)
				goto next;
                        usage();
                        exit(1);
		}
	}

next:
	if (interface == NULL || (node == NULL && broadcast == 0)) {
		printf("xxx: no interface or node specified \n");
		usage();
		exit(1);
	}
	if (pattern) {
		if (send_count > 0)
			infinite = 0;
		if (send_size == 0)
			send_size = strlen(pattern);
		if (send_size > strlen(pattern)) {
			char *new_pattern = (char *)calloc(1, send_size);
			if (new_pattern) {
				strcpy(new_pattern, pattern);
				free(pattern);
				pattern = new_pattern;
			} else
				send_size = strlen(pattern);
		}
	}

	pd = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
	if (pd == -1) {
		perror("socket():");
		exit(1);
	}

	DEBUG("interface index: ");

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
	DEBUG("hardware address: ");
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

	p = myaddr.sa_data;
	for (i = 0; i < addrlen - 1; i++)
		DEBUG("%02x:", *p++);
	DEBUG("%02x\n", *p++);

	peeraddr.sa_family = myaddr.sa_family;
	if (broadcast == 0) {
		if (getpeeraddr(node, &peeraddr) == -1) {
			fprintf(stderr, "invalid peer address\n");
			exit(1);
		}
	} else {
		makebroadcast(&peeraddr);
	}

	DEBUG("peer hardware address: ");
	p = peeraddr.sa_data;
	for (i = 0; i < addrlen - 1; i++)
		DEBUG("%02x:", *p++);
	DEBUG("%02x\n", *p++);


	DEBUG("binding to the interface ifindex=%d\n", ifindex);
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
	 * first, flush all received packets. 
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


	while (infinite || send_count) {
		FD_ZERO(&rfds);	
		FD_ZERO(&wfds);	
		FD_SET(pd, &rfds);
		FD_SET(STDIN_FILENO, &rfds);
		if (pattern)
			FD_SET(pd, &wfds);
		i = select(FD_SETSIZE, &rfds, &wfds, NULL, NULL);
		if (i == 0)
			continue;
		if (i == -1) {
			perror("select");
			exit(1);
		}
		if (pattern == NULL) {
			if (FD_ISSET(STDIN_FILENO, &rfds) &&
			    fgets(buf, sizeof(buf), stdin)) {
				sendmessage(pd, &myaddr, &peeraddr, buf,
					strlen(buf));
			}
		} else {
			if (FD_ISSET(pd, &wfds)) {
				sendmessage(pd, &myaddr, &peeraddr, pattern,
					send_size);
				send_count--; 
				sleep(send_wait);
			}
		}
		if (FD_ISSET(pd, &rfds)) {
			i = recv(pd, buf, sizeof(buf), 0);
			if (i < 0) {
				perror("recv():");
				exit(1);
			}
			if (i == 0)
				continue;
			if (showhexdump)
				hexdump(buf, i);
			else
				showmessage(&myaddr, &peeraddr, buf, i);
		}
	}

	printf("done\n");
	exit(0);
}



int sendmessage(pd, src, dst, buf, count)
	int pd;
	struct sockaddr *src, *dst;
	const unsigned char *buf;
	int count;
	
{
	char tmp[MAXPACKETLEN];
	struct sockaddr_ll sll;
	int c;

	c = buildpacket(tmp, src, dst, buf, count);
	if (c == 0)
		return -1;
	memset(&sll, 0, sizeof(sll));
	sll.sll_ifindex = ifindex;
	c = sendto(pd, tmp, c, 0, (struct sockaddr *)&sll, sizeof(sll));
	if (c == -1)
		perror("sendto():");
	printf ("send %d bytes (including headers)\n", c);
	return c;
}
		

int buildpacket(buf, src, dst, msg, count)
	unsigned char *buf;
	struct sockaddr *src, *dst;
	const unsigned char *msg;
	int count;
{
	int c;

	c = 0;

	if (count == 0)
		return 0;

	switch (src->sa_family) {
	case ARPHRD_ARCNET:
		buf[c++] = src->sa_data[0];
		buf[c++] = dst->sa_data[0];
		buf[c++] = 0; /* offset for short packet */
		buf[c++] = 0; /* offset for long packet */
		if (count <= 253) {
			memcpy(&buf[c], msg, count);
			return c + count;
		} else {
			/* normal format */
			if (count <= 256)
				count = 257;
			if (count > 508)
				count = 508;
			memcpy(&buf[c], msg, count);
			return c + count;
		}
		/* NOTREACHED */
		break;
	case ARPHRD_ETHER:
		memcpy(buf + c, dst->sa_data, ETH_ALEN);
		c += ETH_ALEN;
		memcpy(buf + c, src->sa_data, ETH_ALEN);
		c += ETH_ALEN;
		buf[c++] = 0xde;	/* protocol = 0xdead -- dead :P */
		buf[c++] = 0xad;
		break;
	default:
		/* unknown hard ware */
		break;
	}
	memcpy(&buf[c], msg, count);
	return c + count;
}


int showmessage(struct sockaddr *myaddr, struct sockaddr *peeraddr, unsigned char *buf, int count)
{
	int i;

	switch (myaddr->sa_family) {
	case ARPHRD_ETHER:
		if (memcmp(myaddr->sa_data, buf, 6) != 0) 
			return -1;
		if (memcmp(peeraddr->sa_data, buf + 6, 6) != 0)
			return -1;
		if (buf[12] != 0xde || buf[13] != 0xad) 	/* protocl */
			return -1;
		print_ethaddr(buf);
		buf[count] = 0;	/* XXX the size of buf should be +1 large */
		printf("%s", buf + 14);
		break;
	case ARPHRD_ARCNET:
		/* destination id */
		if (buf[1] != 0 && myaddr->sa_data[0] != buf[1])
			return -1;
#if 0 		/* source id */
		if (peeraddr->sa_data[0] != buf[0])
			return -1;
#endif
		print_arcaddr(buf);
		buf[count] = 0;
		printf("%s\n", buf + 4);
		break;
	default:
		hexdump(buf, count);
		return -1;
	}
	return 0;
}

int getpeeraddr(char *name, struct sockaddr *addr)
{
	unsigned long n;
	char *p;
	int i;
	p = name;
	for (i = 0; i < 8; i++) {
		for (;*p; p++) {
			 if (isxdigit(*p))
				break;
		}
		if (*p == 0)
			break;
		n = strtol(p, &p, 16);
		if (n > 0xff)
			return -1;
		addr->sa_data[i] = (unsigned char)n;
	}
	return i;
}


int makebroadcast(struct sockaddr *addr)
{
	memset(addr->sa_data, 0, sizeof(addr->sa_data));
	switch (addr->sa_family) {
	case ARPHRD_ARCNET:
		addr->sa_data[0] = 0;
		return 1;
	case ARPHRD_ETHER:
		memset(addr->sa_data, 0xff, 6);
		return 6;
	default:
		/* unknown hardware */
		return 0;
	}
	/* NOT REACHED */
}

void usage()
{
	fprintf(stderr, "usage: nettype [-x] -i interface node [[-p pattern] [-w wait] [-c count] [-s size]]\n");
	fprintf(stderr, "       nettype [-x] -b -i interface [[-p pattern] [-w wait] [-c count] [-s size]]\n");
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

/*
 *    Protocol Monkey
 *    Copyright (C) 2007 - VijayaPriya, Sreevathsa, Senthil, Roshni, Gopal
 *
 *    This program is free software; you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation; either version 2 of the License, or
 *    (at your option) any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with this program; if not, write to the Free Software
 *    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

/*
 * install iptables-devel rpm to get libipq headers, library and the kernel 
 * module
 * set the following iptables rule: iptables -A OUTPUT -p icmp -j QUEUE to see
 * the icmp packet dump
 *
 * modprobe ip_queue before running the program
 */
#include <common.h>

static void clean_exit(struct ipq_handle *handle)
{
#ifdef DEBUG
        ipq_perror("passer");
#endif
        ipq_destroy_handle(handle);
        exit(1);
}

void usage()
{
	printf("ICMP Protocol Monkey: Version %s (Prototype)\n\n", PROG_VERSION);
	printf("Usage: %s [OPTIONS]\n\n", PROG_NAME);
	printf("Following options are supported:\n");
	printf("  -d\t\t dumps the captured icmp packets in readable form. This \
			\n\t\t flag is set by deafult.\n");
	printf("  -h\t\t display this help and exit\n");
	printf("  -r\t\t dumps the raw packet contents\n");
	printf("  -m\t\t mode the monkey should operate in. mode can be one of\
			\n \t\t NICE, WILD, ANALYZE, MANGLE, DROP, DUPLICATE, DELAY.\
			\n \t\t The default mode is NICE.\n");
}

/* Dumps the packet in hex on the screen
 */
void print_raw(ipq_packet_msg_t *pkt)
{
	int i=0, count=0;
	printf("\nRaw packet contents: \n");
	printf("\t");
	for(i=0;i<pkt->data_len;i++){
		printf("%x ", pkt->payload[i]);
		count++;
		if(count == 24) {
			count=0;
			printf("\n\t");
		}
   }
   printf("\n");
}

int main(int argc, char **argv)
{
    int status;
	int ch;
	bool_t bdump=0, bbadflag=0, bquit=0, brawdump=0, bmode=0;
    unsigned char buf[PKT_BUFSIZE];
    struct ipq_handle *handle;

	strcpy(PROG_NAME, argv[0]);
	while ((ch = getopt(argc, argv, "dhmr")) != -1) {
		switch (ch) {
			case 'd':
				debug(("%s: Packet dump flag set.\n", PROG_NAME));
				bdump = 1;
				break;
			case 'h':
				debug(("%s: Help flag set.\n", PROG_NAME));
				usage();
				bquit = 1;
				break;
			case 'm':
				debug(("%s: Mode flag set.\n", PROG_NAME));
				bmode = 1;
				break;
			case 'r':
				debug(("%s: Raw Packet dump flag set.\n", PROG_NAME));
				brawdump = 1;
				break;
			default:
				printf("%s: Invalid flag set.\n", PROG_NAME);
				printf ("Try '%s -h' for usage options\n", PROG_NAME);
				bbadflag = 1;
				break;
		}
	}

	if(bbadflag || bquit) {
		exit(1);
	}
	bquit = 0;

	printf("Team: MANGLERS\n");
	printf("ICMP Protocol Monkey: Version %s (Prototype)\n\n", PROG_VERSION);

	/* No flag specified. Turn bdump by default */
	if(argc == 1) {
		printf("%s: using the -d option by default\n", PROG_NAME);
		bdump = 1;
	}


    if(!(handle = ipq_create_handle(0, PF_INET))) {
            clean_exit(handle);
	}
	debug(("got handle\n"));


    status = ipq_set_mode(handle, IPQ_COPY_PACKET, PKT_BUFSIZE);
    if (status < 0) {
			printf("%s: Make sure the ip_queue module is inserted into the \
				\n\t  kernel. Use 'modprobe ip_queue' and then try again.\n", \
				PROG_NAME);
            clean_exit(handle);
	}
	debug(("got set_mode status\n"));

	init_icmphdr_size();	
    do{
            status = ipq_read(handle, buf, PKT_BUFSIZE, 0);
            if (status < 0)
                    clean_exit(handle);
			debug(("got read status\n"));
#if 0
			debug(("ipq_read status=%d\n", status));
#endif
            switch (ipq_message_type(buf)) {
                    case NLMSG_ERROR:
                            fprintf(stderr, "%s: received error message %d\n",
                                    PROG_NAME, ipq_get_msgerr(buf));
							fprintf(stderr, "%s: try running as root\n", 
											PROG_NAME);
							bquit = 1;
                            break;

                    case IPQM_PACKET: {
							debug(("rcvd ICMP packet...\n"));
							printf("------------------------------------\n");
                            ipq_packet_msg_t *pkt = ipq_get_packet(buf);

							if(brawdump) {
								print_raw(pkt);
							}
							parse_packet(pkt);
                            status = ipq_set_verdict(handle, pkt->packet_id,
                                                     NF_ACCEPT, 0, NULL);
                            if (status < 0) {
								usage();
                                clean_exit(handle);
							}
                            break;
                    }

                    default:
                            fprintf(stderr, "%s: Unknown message type!\n",
											PROG_NAME);
                            break;
            }
			if(bquit) {
				exit(1);
			}
    } while (1);

    ipq_destroy_handle(handle);
    return 0;
}

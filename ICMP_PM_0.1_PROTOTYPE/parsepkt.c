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

#include <parsepkt.h>

void parse_packet(ipq_packet_msg_t *pkt)
{
	/* Cast the IP Header from the raw packet */
	ip_t *iph = ((struct iphdr *)pkt->payload);
	
	/* Cast the ICMP Header from the raw packet */
	//struct tcphdr *tcp = (struct tcphdr *)(pkt->payload + (iph->ihl << 2));
	icmp_t *icmph = (struct icmphdr *)(pkt->payload + (iph->ihl << 2));
	
	print_ip_pkt(iph);
	print_icmp_pkt(icmph);
	/* get the payload offset from with the raw packet */
	//int unsigned payload_offset = ((iph->ihl << 2) + (tcp->doff << 2));
	
}

void print_ip_pkt(ip_t *iph)
{
	/* Calculate the size of the IP Header. iph->ihl contains the number of 32 bit
	words that represent the header size. Therfore to get the number of bytes
	multiple this number by 4 */
	int iphdr_size = (iph->ihl << 2);
	
	/* calculate the length of the payload */
	int unsigned payload_length = (unsigned int) ntohs(iph->tot_len) - iphdr_size;
	
	printf("\nIP Packet contents:\n");
	printf("\tTotal IP Packet size: %d\n", ntohs(iph->tot_len));
	printf("\tIP Header size: %d\n", iphdr_size);
	printf("\tIP Payload Size : %d\n", payload_length);
	printf("\tProtocol: %d\n", iph->protocol);
	printf("\tSource IP: %s\n", inet_ntoa(iph->saddr));
	printf("\tDest IP: %s\n", inet_ntoa(iph->daddr));
}

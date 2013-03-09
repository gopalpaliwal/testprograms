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

#include <pm_icmp.h>
#include <common.h>

int icmphdr_size[32];   // supports upto 32 types. We use only about 16 types
void init_icmphdr_size()
{
	int i;
	for (i=0 ; i< 32; i++) 
	    icmphdr_size[i]=0;

	icmphdr_size[ICMP_ECHOREPLY] = 8;
	icmphdr_size[ICMP_ECHO] = 8;
	icmphdr_size[ICMP_DEST_UNREACH] = 8;
	icmphdr_size[ICMP_SOURCE_QUENCH] = 8;
	icmphdr_size[ICMP_REDIRECT] = 8;
	icmphdr_size[ICMP_TIME_EXCEEDED] = 8;
	icmphdr_size[ICMP_PARAMETERPROB] = 8;
	icmphdr_size[ICMP_ROUTER_ADVERTISE] = 8;
	icmphdr_size[ICMP_ROUTER_SOLICIT] = 8;
	icmphdr_size[ICMP_INFO_REQUEST] =  
	icmphdr_size[ICMP_INFO_REPLY] = 8;
	icmphdr_size[ICMP_ADDRESS] = 12;
	icmphdr_size[ICMP_ADDRESSREPLY] = 12;
	icmphdr_size[ICMP_TIMESTAMP] = 12;
	icmphdr_size[ICMP_TIMESTAMPREPLY] = 20;

#if 0
	for (i=0 ; i< 32; i++) 
	    debug(("icmphdr[%d] = %d\n", i, icmphdr_size[i]));
#endif
}

void print_icmp_pkt(icmp_t* icmph)
{
	int i;
	int size_payload, size_ip, size_options;

	printf("\nICMP Packet contents:\n");
	printf("\tICMP header size: %d\n", icmphdr_size[icmph->icmp_type]);
	//printf("ICMP Payload size: %d\n", );
	

	printf("\tICMP message type: %02x\n",icmph->icmp_type);
	printf("\tICMP code: %02x\n", icmph->icmp_code);
	printf("\tICMP checksum: %04x\n", icmph->icmp_cksum);
	
	switch (icmph->icmp_type) {
		case 8: ;
		case 15: ;
		case 16: ; 
		case 0:
			printf ("\tICMP id: %04x\n", icmph->icmp_id);
			printf ("\tICMP sequence: %04x\n", icmph->icmp_seq);
			break;
		case 3: ;
		case 4: ;
		case 10: ;
		case 11: 
			printf("\tUnused : %08x\n", icmph->icmp_void);
			break;
		case 5: 
			printf("\tGateway address:%x\n", (icmph->icmp_gwaddr));
			break;
		case 12:
			printf("\tPointer :%x\n", icmph->icmp_pptr);
			printf("\tUnused: %02x%04x\n",icmph->icmp_pptr_unused1,icmph->icmp_pptr_unused2);
			break;	
		case 9:
			printf("\tNum addrs: %02x\n", icmph->icmp_adv_count);
			printf("\tAddr entry size: %02x\n", icmph->icmp_adv_entry_size);
			printf("\tLIfetime: %04x\n", icmph->icmp_adv_lifetime);
			break;	
		case 17: ;
		case 18: 
			printf("\tIdentifier: %04x\n", icmph->icmp_id);
			printf("\tSequence number: %04x\n", icmph->icmp_seq);
			printf("\tMask: %08x\n" , icmph->icmp_mask);
			break;
		case 13: ;
		case 14:
			printf("\tIdentifier: %04x\n", icmph->icmp_id);
			printf("\tSequence number: %04x\n", icmph->icmp_seq);
			printf("\tOriginate timestamp : %x\n", icmph->icmp_otime);
			printf("\tReceive timestamp : %x\n", icmph->icmp_rtime);
			printf("\tTransit timestamp: %x\n", icmph->icmp_ttime);
			break;
	}

#if 0
	printf ("\nPayload\n");
	for (i=0; i<header->payload_size; i++)
	        printf ("%02x ", *(header->payload+i));
	printf("\n");
#endif
}


/* Error Message mangling functions */

/*
 * Destination Unreachable Type 3
 */
retcode_t mangle_dest_unreach(icmp_t* icmp_pkt)
{
	return PM_SUCCESS;
}

/*
 * Source Quench Type 4
 */
retcode_t mangle_src_quench(icmp_t* icmp_pkt)
{
	return PM_SUCCESS;
}

/*
 * Redirect Type 5
 */
retcode_t mangle_redirect(icmp_t* icmp_pkt)
{
	return PM_SUCCESS;
}

/*
 * Time Exceeded Type 11
 */
retcode_t mangle_time_exceeded(icmp_t* icmp_pkt)
{
	return PM_SUCCESS;
}

/*
 * Parameter Problem Type 12
 */
retcode_t mangle_param_prob(icmp_t* icmp_pkt)
{
	return PM_SUCCESS;
}


/* Informational Message mangling functions */

/*
 * Echo Request Type 8
 */
retcode_t mangle_echo_request(icmp_t* icmp_pkt)
{
	return PM_SUCCESS;
}

/*
 * Echo Reply Type 0
 */
retcode_t  mangle_echo_reply(icmp_t* icmp_pkt)
{
	return PM_SUCCESS;
}

/*
 * Router Advertise Type 9
 */
retcode_t mangle_router_advertise(icmp_t* icmp_pkt)
{
	return PM_SUCCESS;
}

/*
 * Router Solicit Type 10
 */
retcode_t mangle_router_solicit(icmp_t* icmp_pkt)
{
	return PM_SUCCESS;
}

/*
 * Timerstamp Request Type 15
 */
retcode_t mangle_timestamp_request(icmp_t* icmp_pkt)
{
	return PM_SUCCESS;
}

/*
 * Timestamp Reply Type 14
 */
retcode_t mangle_timestamp_reply(icmp_t* icmp_pkt)
{
	return PM_SUCCESS;
}

/*
 * Information request Type 15
 */
retcode_t mangle_info_request(icmp_t* icmp_pkt)
{
	return PM_SUCCESS;
}

/*
 * Information Reply Type 16
 */
retcode_t mangle_info_reply(icmp_t* icmp_pkt)
{
	return PM_SUCCESS;
}

/*
 * Address Mask Request Type 17
 */
retcode_t mangle_addr_mask_request(icmp_t* icmp_pkt)
{
	return PM_SUCCESS;
}

/*
 * Address Mask Reply Type 18
 */
retcode_t mangle_addr_mask_reply(icmp_t* icmp_pkt)
{
	return PM_SUCCESS;
}

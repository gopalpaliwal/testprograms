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

#ifndef __PM_ICMP_H__
#define __PM_ICMP_H__

#include <pm_types.h>
#include <pm_errors.h>
#include <common.h>

/*
 * Structure of an icmp header.
 */
typedef struct icmphdr {
	u_int8_t  icmp_type;		/* type of message, see below */
	u_int8_t  icmp_code;		/* type sub code */
	u_int16_t icmp_cksum;		/* ones complement cksum of struct */
	union {
	
		struct  ih_pptrunused {	
			u_int8_t ih_pptr;          		 /* ICMP_PARAMPROB */
			u_int8_t ih_unused1;
			u_int16_t ih_unused2;
	      	} ih_pptrunused;

		struct in_addr ih_gwaddr;	/* ICMP_REDIRECT */
		struct ih_idseq {
			u_int16_t icd_id;
			u_int16_t icd_seq;
		} ih_idseq;

		struct id_ra {
                        u_int8_t adv_count;
                        u_int8_t adv_entry_size;
                        u_int16_t adv_lifetime;
                }id_ra;

		u_int32_t ih_void;

		/* ICMP_UNREACH_NEEDFRAG -- Path MTU Discovery (RFC1191) */
		struct ih_pmtu {
			u_int16_t ipm_void;
			u_int16_t ipm_nextmtu;
		} ih_pmtu;
	} icmp_hun;
#define icmp_pptr       icmp_hun.ih_pptrunused.ih_pptr
#define icmp_pptr_unused1 icmp_hun.ih_pptrunused.ih_unused1
#define icmp_pptr_unused2 icmp_hun.ih_pptrunused.ih_unused2
#define	icmp_gwaddr	icmp_hun.ih_gwaddr
#define	icmp_id		icmp_hun.ih_idseq.icd_id
#define	icmp_seq	icmp_hun.ih_idseq.icd_seq
#define	icmp_void	icmp_hun.ih_void
#define	icmp_pmvoid	icmp_hun.ih_pmtu.ipm_void
#define	icmp_nextmtu	icmp_hun.ih_pmtu.ipm_nextmtu
#define icmp_adv_count icmp_hun.id_ra.adv_count
#define icmp_adv_entry_size icmp_hun.id_ra.adv_entry_size
#define icmp_adv_lifetime icmp_hun.id_ra.adv_lifetime
	union {
		struct id_ts {
			u_int32_t its_otime;
			u_int32_t its_rtime;
			u_int32_t its_ttime;
		} id_ts;

		/*struct id_ip  {
			ip_t idi_ip;
			 //options and then 64 bits of data 
		} id_ip;*/
                /*struct mpls_ext {
                    u_int8_t legacy_header[128]; // extension header starts 128 bytes after ICMP header 
                    u_int8_t version_res[2];
                    u_int8_t checksum[2];
                    u_int8_t data[1];
                } mpls_ext;*/
		u_int32_t id_mask;
		//u_int8_t id_data[1];
	} icmp_dun;
#define	icmp_otime	icmp_dun.id_ts.its_otime
#define	icmp_rtime	icmp_dun.id_ts.its_rtime
#define	icmp_ttime	icmp_dun.id_ts.its_ttime
#define	icmp_ip		icmp_dun.id_ip.idi_ip
#define	icmp_mask	icmp_dun.id_mask
#define	icmp_data	icmp_dun.id_data
#define	icmp_mpls_ext_version	icmp_dun.mpls_ext.version_res
#define	icmp_mpls_ext_checksum	icmp_dun.mpls_ext.checksum
#define	icmp_mpls_ext_data	icmp_dun.mpls_ext.data
} icmp_t;

/* A wrapper around the default icmp struct to accomodate the beginning of ICMP payload
 * and the ICMP payload length
 */
typedef struct pm_icmp {
	icmp_t *icmp;
	u_char* payload;	/* pointer to the beginning of the ICMP payload */
	int payload_size;
} pm_icmp_t;

#define ICMP_ECHOREPLY		0	/* Echo Reply			*/
#define ICMP_DEST_UNREACH	3	/* Destination Unreachable	*/
#define ICMP_SOURCE_QUENCH	4	/* Source Quench		*/
#define ICMP_REDIRECT		5	/* Redirect (change route)	*/
#define ICMP_ECHO			8	/* Echo Request			*/
#define ICMP_TIME_EXCEEDED	11	/* Time Exceeded		*/
#define ICMP_PARAMETERPROB	12	/* Parameter Problem		*/
#define ICMP_TIMESTAMP		13	/* Timestamp Request		*/
#define ICMP_TIMESTAMPREPLY	14	/* Timestamp Reply		*/
#define ICMP_INFO_REQUEST	15	/* Information Request		*/
#define ICMP_INFO_REPLY		16	/* Information Reply		*/
#define ICMP_ADDRESS		17	/* Address Mask Request		*/
#define ICMP_ADDRESSREPLY	18	/* Address Mask Reply		*/
#define NR_ICMP_TYPES		18
#define ICMP_ROUTER_ADVERTISE	9	/* Router Advertisement		*/
#define ICMP_ROUTER_SOLICIT	10	/* Router Solicitation		*/


/* Codes for UNREACH. */
#define ICMP_NET_UNREACH	0	/* Network Unreachable		*/
#define ICMP_HOST_UNREACH	1	/* Host Unreachable		*/
#define ICMP_PROT_UNREACH	2	/* Protocol Unreachable		*/
#define ICMP_PORT_UNREACH	3	/* Port Unreachable		*/
#define ICMP_FRAG_NEEDED	4	/* Fragmentation Needed/DF set	*/
#define ICMP_SR_FAILED		5	/* Source Route failed		*/
#define ICMP_NET_UNKNOWN	6
#define ICMP_HOST_UNKNOWN	7
#define ICMP_HOST_ISOLATED	8
#define ICMP_NET_ANO		9
#define ICMP_HOST_ANO		10
#define ICMP_NET_UNR_TOS	11
#define ICMP_HOST_UNR_TOS	12
#define ICMP_PKT_FILTERED	13	/* Packet filtered */
#define ICMP_PREC_VIOLATION	14	/* Precedence violation */
#define ICMP_PREC_CUTOFF	15	/* Precedence cut off */
#define NR_ICMP_UNREACH		15	/* instead of hardcoding immediate value */

/* Codes for REDIRECT. */
#define ICMP_REDIR_NET		0	/* Redirect Net			*/
#define ICMP_REDIR_HOST		1	/* Redirect Host		*/
#define ICMP_REDIR_NETTOS	2	/* Redirect Net for TOS		*/
#define ICMP_REDIR_HOSTTOS	3	/* Redirect Host for TOS	*/

/* Codes for TIME_EXCEEDED. */
#define ICMP_EXC_TTL		0	/* TTL count exceeded		*/
#define ICMP_EXC_FRAGTIME	1	/* Fragment Reass time exceeded	*/

/* PARAMPROB code */
#define	ICMP_PARAMPROB_OPTABSENT 1		/* req. opt. absent */


/* Error Message mangling functions */
retcode_t mangle_dest_unreach(icmp_t* icmp_pkt);
retcode_t mangle_src_quench(icmp_t* icmp_pkt);
retcode_t mangle_redirect(icmp_t* icmp_pkt);
retcode_t mangle_time_exceeded(icmp_t* icmp_pkt);
retcode_t mangle_param_prob(icmp_t* icmp_pkt);

/* Informational Message mangling functions */

retcode_t mangle_echo_request(icmp_t* icmp_pkt);
retcode_t  mangle_echo_reply(icmp_t* icmp_pkt);
/*
retcode_t mangle_router_advertise(icmp_t* icmp_pkt);
retcode_t mangle_router_solicit(icmp_t* icmp_pkt);
*/
retcode_t mangle_timestamp_request(icmp_t* icmp_pkt);
retcode_t mangle_timestamp_reply(icmp_t* icmp_pkt);
retcode_t mangle_info_request(icmp_t* icmp_pkt);
retcode_t mangle_info_reply(icmp_t* icmp_pkt);
retcode_t mangle_addr_mask_request(icmp_t* icmp_pkt);
retcode_t mangle_addr_mask_reply(icmp_t* icmp_pkt);



#endif

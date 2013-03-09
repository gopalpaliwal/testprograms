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

#ifndef __PM_COMMON_H__
#define __PM_COMMON_H__

#include <linux/netfilter.h>
#include <libipq.h>
#include <netinet/ip.h>
//#include <netinet/ip_icmp.h>
//#include <netinet/tcp.h>
#include <pm_icmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <pm_errors.h>
#include <pm_types.h>

#define PROG_VERSION	"0.1"
//#define PROG_NAME		"pm"
#define PKT_BUFSIZE 2048

char PROG_NAME[256];


#ifdef DEBUG
#define debug(msg) printf msg
#else
#define debug(msg)
#endif

#endif

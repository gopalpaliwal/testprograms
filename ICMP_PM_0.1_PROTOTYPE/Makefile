#
#    ICMP Protocol Monkey
#    Copyright (C) 2007 - Vijaya Priya, Sreevathsa, Senthil, Roshni, Gopal
#
#    This program is free software; you can redistribute it and/or modify
#    it under the terms of the GNU General Public License as published by
#    the Free Software Foundation; either version 2 of the License, or
#    (at your option) any later version.
#
#    This program is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU General Public License for more details.
#
#    You should have received a copy of the GNU General Public License
#    along with this program; if not, write to the Free Software
#    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
#


#
# Makefile for building Protocol Monkey (pm) - vathsa
#

#
# General Flags
#

CC = gcc
CFLAGS =
DEBUG_CFLAGS = -g -DDEBUG
PROGRAM = pm
LIBS = -lipq
OBJECTS = main  parsepkt pm_icmp


#
# Directories and commands used while building pm
#

OBJDIR = obj
BINDIR = bin
INCDIR = include 
MKDIR = /bin/mkdir -p
RM = /bin/rm -rf


#
# Rules
#

all:    dirs $(PROGRAM)

dirs:
	$(MKDIR) $(OBJDIR)
	$(MKDIR) $(BINDIR)

$(PROGRAM):		$(foreach i,$(OBJECTS),$(OBJDIR)/$(i).o)
			$(CC) $(CFLAGS) $(DEBUG_CFLAGS) -o $(BINDIR)/$@ $(foreach i,$(OBJECTS),$(OBJDIR)/$(i).o) $(LIBS)

$(OBJDIR)/main.o:	main.c
			$(CC) $(CFLAGS) $(DEBUG_CFLAGS) -c $< -o $@ -I$(INCDIR) 

$(OBJDIR)/parsepkt.o:	parsepkt.c
			$(CC) $(CFLAGS) $(DEBUG_CFLAGS) -c $< -o $@ -I$(INCDIR) 

$(OBJDIR)/pm_icmp.o:	pm_icmp.c
			$(CC) $(CFLAGS) $(DEBUG_CFLAGS) -c $< -o $@ -I$(INCDIR) 

clean:
			$(RM) $(OBJDIR) $(BINDIR)

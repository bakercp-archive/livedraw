/*
Written by John MacCallum, The Center for New Music and Audio Technologies,
University of California, Berkeley.  Copyright (c) 2009, The Regents of
the University of California (Regents). 
Permission to use, copy, modify, distribute, and distribute modified versions
of this software and its documentation without fee and without a signed
licensing agreement, is hereby granted, provided that the above copyright
notice, this paragraph and the following two paragraphs appear in all copies,
modifications, and distributions.

IN NO EVENT SHALL REGENTS BE LIABLE TO ANY PARTY FOR DIRECT, INDIRECT,
SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES, INCLUDING LOST PROFITS, ARISING
OUT OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION, EVEN IF REGENTS HAS
BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

REGENTS SPECIFICALLY DISCLAIMS ANY WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
PURPOSE. THE SOFTWARE AND ACCOMPANYING DOCUMENTATION, IF ANY, PROVIDED
HEREUNDER IS PROVIDED "AS IS". REGENTS HAS NO OBLIGATION TO PROVIDE
MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS.
*/

#define OSC_MATCH_ENABLE_2STARS		1
#define OSC_MATCH_ENABLE_NSTARS		1

#define OSC_MATCH_ADDRESS_COMPLETE	1
#define OSC_MATCH_PATTERN_COMPLETE	2
#define OSC_MATCH_ADDRESS_AND_PATTERN_COMPLETE 3 // bakercp

/*
typedef struct _osc_callback {
	const char* address;			// Address
	struct _osc_callback *child;		// RAM
	struct _osc_callback *sibling;		// RAM
	struct _osc_callback *parent;		// RAM
	int callback;				// ROM
} osc_callback;
*/

int osc_match(const char *pattern, const char *address, int *pattern_offset, int *address_offset);
int osc_match_star(const char *pattern, const char *address);
int osc_match_star_r(const char *pattern, const char *address);
int osc_match_single_char(const char *pattern, const char *address);
int osc_match_bracket(const char *pattern, const char *address);
int osc_match_curly_brace(const char *pattern, const char *address);

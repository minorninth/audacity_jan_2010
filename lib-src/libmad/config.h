/* config.h.  Generated automatically by configure.  */
/* config.h.in.  Generated automatically from configure.in by autoheader.  */
/*
 * libmad - MPEG audio decoder library
 * Copyright (C) 2000-2001 Robert Leslie
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * $Id: acconfig.h,v 1.12 2001/10/17 19:12:05 rob Exp $
 */

# ifndef LIBMAD_CONFIG_H
# define LIBMAD_CONFIG_H

/*****************************************************************************
 * Definitions selected automatically by `configure'                         *
 *****************************************************************************/


/* Define to optimize for speed over accuracy. */
/* #undef OPT_SPEED */

/* Define to optimize for accuracy over speed. */
/* #undef OPT_ACCURACY */

/* Define to enable a fast subband synthesis approximation optimization. */
/* #undef OPT_SSO */

/* Define to influence a strict interpretation of the ISO/IEC standards,
   even if this is in opposition with best accepted practices. */
/* #undef OPT_STRICT */

/* Define if your MIPS CPU supports a 2-operand MADD instruction. */
/* #undef HAVE_MADD_ASM */

/* Define if your MIPS CPU supports a 2-operand MADD16 instruction. */
/* #undef HAVE_MADD16_ASM */

/* Define to enable diagnostic debugging support. */
/* #undef DEBUG */

/* Define to disable debugging assertions. */
/* #undef NDEBUG */

/* Define to enable experimental code. */
/* #undef EXPERIMENTAL */


/* Define if you have the <inttypes.h> header file. */
/* #undef HAVE_INTTYPES_H */

/* Define if you have the <limits.h> header file. */
#define HAVE_LIMITS_H 1

/* Define if you have the <memory.h> header file. */
/* #undef HAVE_MEMORY_H */

/* Define if you have the <stdint.h> header file. */
/* #undef HAVE_STDINT_H */

/* Define if you have the <stdlib.h> header file. */
/* #undef HAVE_STDLIB_H */

/* Define if you have the <strings.h> header file. */
/* #undef HAVE_STRINGS_H */

/* Define if you have the <string.h> header file. */
/* #undef HAVE_STRING_H */

/* Define if you have the <sys/stat.h> header file. */
/* #undef HAVE_SYS_STAT_H */

/* Define if you have the <sys/types.h> header file. */
/* #undef HAVE_SYS_TYPES_H */

/* Define if you have <sys/wait.h> that is POSIX.1 compatible. */
#define HAVE_SYS_WAIT_H 1

/* Define if you have the <unistd.h> header file. */
#define HAVE_UNISTD_H 1

/* Name of package */
#define PACKAGE "libmad"

/* The size of a `int', as computed by sizeof. */
#define SIZEOF_INT 4

/* The size of a `long', as computed by sizeof. */
#define SIZEOF_LONG 4

/* The size of a `long long', as computed by sizeof. */
#define SIZEOF_LONG_LONG 8

/* Define if you have the ANSI C header files. */
#define STDC_HEADERS 1

/* Version number of package */
#define VERSION "0.14.0b"

/* Define to empty if `const' does not conform to ANSI C. */
/* #undef const */

/* Define as `__inline' if that's what the C compiler calls it, or to nothing
   if it is not supported. */
/* #undef inline */

/* Define to `int' if <sys/types.h> does not define. */
/* #undef pid_t */
/*****************************************************************************
 * End of automatically configured definitions                               *
 *****************************************************************************/

# endif

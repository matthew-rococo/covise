/*
 * Copyright 1997, Regents of the University of Minnesota
 *
 * metis.h
 *
 * This file includes all necessary header files
 *
 * Started 8/27/94
 * George
 *
 * $Id: metis.h,v 1.1 1998/11/27 17:59:21 karypis Exp $
 */

#include <stdio.h>
#if _MSC_VER >= 1900
#include <stdlib.h>
#endif
#ifdef __STDC__
#include <stdlib.h>
#else
#include <malloc.h>
#endif
#ifndef WIN32
#include <strings.h>
#endif
#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdarg.h>
#include <time.h>

#ifdef DMALLOC
#include <dmalloc.h>
#endif

#include "defs.h"
#include "struct.h"
#include "macros.h"
#include "rename.h"
#include "proto.h"

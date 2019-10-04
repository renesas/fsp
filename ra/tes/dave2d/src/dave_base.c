//--------------------------------------------------------------------------
// Project: D/AVE
// File:    dave_base.c (%version: 2 %)
//          created Mon Aug 22 12:46:12 2005 by hh04027
//
// Description:
//  %date_modified: Wed Aug 31 14:06:47 2005 %  (%derived_by:  hh04027 %)
//
//--------------------------------------------------------------------------

#include "dave_base.h"

//---------------------------------------------------------------------------
// These helper macros are used to stringify a given macro
#define D1_STR(s)           # s
#define D1_XSTR(s)          D1_STR(s)

// These helper macros are used to concat two strings with a dot.
#ifdef __CA850__
#define D1_DOT(a,b)         a.b
#else
#define D1_DOT(a,b)         a ## . ## b
#endif
#define D1_XDOT(a,b)        D1_DOT(a,b)

//---------------------------------------------------------------------------
// Define the D1_VERSION and D1_VERSION_STRING macros

// Build up the D1_VERSION macro 
#define D1_VERSION ((D1_VERSION_MAJOR << 16) | D1_VERSION_MINOR )    

// Create the D1_VERSION_STRING macro
#define D1_VERSION_STRING  D1_XSTR( D1_XDOT( D1_VERSION_MAJOR, D1_VERSION_MINOR) )

//--------------------------------------------------------------------------

static const char g_versionid[] = "V" D1_VERSION_STRING ;

//--------------------------------------------------------------------------
//
const char * d1_getversionstring()
{
	return g_versionid; 
}

//--------------------------------------------------------------------------
//
int d1_getversion()
{
	return D1_VERSION; 
}


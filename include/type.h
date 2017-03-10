#ifndef TYPE_H
#define TYPE_H


#include <string.h>
#include <stdio.h>




#ifndef WIN32
	#undef __STL_USE_EXCEPTIONS
	#undef __EXCEPTIONS
	#ifdef __THROW_BAD_ALLOC
	#undef __THROW_BAD_ALLOC
	#endif
	#ifndef __THROW_BAD_ALLOC
		#define __THROW_BAD_ALLOC throw bad_alloc()
	#endif

	//#define ASSERT(exp)     ((void)0)
	#define ASSERT(exp) {if (!(exp)) printf("***********Assert failed.file=%s,line=%d,exp=%s\n",__FILE__,__LINE__,#exp);}
	#define ASSERT_TRIP(exp,str) {if (!(exp)) printf("***********Assert failed.file=%s,line=%d,exp=%s,exp=%s\n",__FILE__,__LINE__,#exp,#str);}
#else
	#include "assert.h"
	#define ASSERT assert
#endif

#define YEAR_21CENT_BEGIN 2000
#define TM_YEAR_BEGIN     1900
#define TM_MONTH_BEGIN    1




#endif



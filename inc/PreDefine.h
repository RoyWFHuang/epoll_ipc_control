#ifndef __PreDefine_H__
#define __PreDefine_H__

#include <stdio.h>




extern FILE *logfile_pfile;
#ifdef LogMsg
#define PRINT_OUTFILE logfile_pfile
#else
#define PRINT_OUTFILE stderr
#endif




#ifdef ErrMsg
#define PRINT_ERRMSG(fmt, str...) fprintf(PRINT_OUTFILE,"Error(%s - %s) [%d] : " fmt, __FILE__, __func__, __LINE__, ##str)
#else
#define PRINT_ERRMSG(fmt, str...)
#endif

#ifdef DebugMsg
#define PRINT_DBGMSG(fmt, str...) fprintf(PRINT_OUTFILE,"DBG  (%s - %s) [%d] : " fmt, __FILE__, __func__, __LINE__, ##str)
#else
#define PRINT_DBGMSG(fmt, str...)
#endif

#define PRINT_ERR PRINT_ERRMSG
#define PRINT_DBG PRINT_DBGMSG




extern int __g_debug_lv_int;

#define PRINT_ERR_LV(fmt, str...)  \
do { \
	if(logfile_pfile !=NULL){\
		if (__g_debug_lv_int > 0) \
			fprintf(logfile_pfile,"Error(%s - %s) [%d] : " \
				fmt, __FILE__, __func__, __LINE__, ##str); \
	} \
	else { \
		if (__g_debug_lv_int > 0) \
			fprintf(stderr,"Error(%s - %s) [%d] : " \
				fmt, __FILE__, __func__, __LINE__, ##str);  \
	}\
} while (0)





#define PRINT_DBG_LV(debug_lv,fmt,str...) \
	do { \
		if(logfile_pfile !=NULL){\
			if (__g_debug_lv_int > debug_lv)\
				fprintf(logfile_pfile,"DBG(%s - %s) [%d] : " \
					fmt, __FILE__, __func__, __LINE__, ##str); \
		}\
		else {\
			if (__g_debug_lv_int > debug_lv) \
				fprintf(stderr,"DBG(%s - %s) [%d] : " \
					fmt, __FILE__, __func__, __LINE__, ##str); \
		}\
	} while (0)
#endif




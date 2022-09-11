/*
 *  stress.h    Stress-testing functions
 *
 * =========================================================================
 *
 *                          Open Watcom Project
 *
 * Copyright (c) 2004-2022 The Open Watcom Contributors. All Rights Reserved.
 *
 *    This file is automatically generated. Do not edit directly.
 *
 * =========================================================================
 */

#ifndef _INC_STRESS
#define _INC_STRESS

#ifndef _ENABLE_AUTODEPEND
 #pragma read_only_file
#endif

#ifndef _INC_WINDOWS
    #include <windows.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

#pragma pack( __push, 1 )

/* Partition identifiers */
#define EDS_WIN     1
#define EDS_CUR     2
#define EDS_TEMP    3

int WINAPI  AllocDiskSpace( long, UINT );
int WINAPI  AllocFileHandles( int );
BOOL WINAPI AllocGDIMem( UINT );
BOOL WINAPI AllocMem( DWORD );
BOOL WINAPI AllocUserMem( UINT );
void WINAPI FreeAllMem( void );
void WINAPI FreeAllGDIMem( void );
void WINAPI FreeAllUserMem( void );
int WINAPI  GetFreeFileHandles( void );
void WINAPI UnAllocDiskSpace( UINT );
void WINAPI UnAllocFileHandles( void );

#pragma pack( __pop )

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* _INC_STRESS */

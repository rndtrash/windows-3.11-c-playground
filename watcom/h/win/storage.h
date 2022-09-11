/*
 *  storage.h   Structured storage interfaces and functions
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

#ifndef _STORAGE_H_
#define _STORAGE_H_

#ifndef _ENABLE_AUTODEPEND
 #pragma read_only_file
#endif

#include <compobj.h>

/* Primitive data types */
typedef char            TCHAR;
typedef char FAR * FAR  *SNB;

/* Structured storage error codes */
#define STG_E_INVALIDFUNCTION   MAKE_SCODE( SEVERITY_ERROR, FACILITY_STORAGE, 0x0001 )
#define STG_E_FILENOTFOUND      MAKE_SCODE( SEVERITY_ERROR, FACILITY_STORAGE, 0x0002 )
#define STG_E_PATHNOTFOUND      MAKE_SCODE( SEVERITY_ERROR, FACILITY_STORAGE, 0x0003 )
#define STG_E_TOOMANYOPENFILES  MAKE_SCODE( SEVERITY_ERROR, FACILITY_STORAGE, 0x0004 )
#define STG_E_ACCESSDENIED      MAKE_SCODE( SEVERITY_ERROR, FACILITY_STORAGE, 0x0005 )
#define STG_E_INVALIDHANDLE     MAKE_SCODE( SEVERITY_ERROR, FACILITY_STORAGE, 0x0006 )
#define STG_E_INSUFFICIENTMEMORY \
    MAKE_SCODE( SEVERITY_ERROR, FACILITY_STORAGE, 0x0008 )
#define STG_E_INVALIDPOINTER    MAKE_SCODE( SEVERITY_ERROR, FACILITY_STORAGE, 0x0009 )
#define STG_E_NOMOREFILES       MAKE_SCODE( SEVERITY_ERROR, FACILITY_STORAGE, 0x0012 )
#define STG_E_DISKISWRITEPROTECTED \
    MAKE_SCODE( SEVERITY_ERROR, FACILITY_STORAGE, 0x0013 )
#define STG_E_SEEKERROR         MAKE_SCODE( SEVERITY_ERROR, FACILITY_STORAGE, 0x0019 )
#define STG_E_WRITEFAULT        MAKE_SCODE( SEVERITY_ERROR, FACILITY_STORAGE, 0x001D )
#define STG_E_READFAULT         MAKE_SCODE( SEVERITY_ERROR, FACILITY_STORAGE, 0x001E )
#define STG_E_SHAREVIOLATION    MAKE_SCODE( SEVERITY_ERROR, FACILITY_STORAGE, 0x0020 )
#define STG_E_LOCKVIOLATION     MAKE_SCODE( SEVERITY_ERROR, FACILITY_STORAGE, 0x0021 )
#define STG_E_FILEALREADYEXISTS MAKE_SCODE( SEVERITY_ERROR, FACILITY_STORAGE, 0x0050 )
#define STG_E_INVALIDPARAMETER  MAKE_SCODE( SEVERITY_ERROR, FACILITY_STORAGE, 0x0057 )
#define STG_E_MEDIUMFULL        MAKE_SCODE( SEVERITY_ERROR, FACILITY_STORAGE, 0x0070 )
#define STG_E_ABNORMALAPIEXIT   MAKE_SCODE( SEVERITY_ERROR, FACILITY_STORAGE, 0x00FA )
#define STG_E_INVALIDHEADER     MAKE_SCODE( SEVERITY_ERROR, FACILITY_STORAGE, 0x00FB )
#define STG_E_INVALIDNAME       MAKE_SCODE( SEVERITY_ERROR, FACILITY_STORAGE, 0x00FC )
#define STG_E_UNKNOWN           MAKE_SCODE( SEVERITY_ERROR, FACILITY_STORAGE, 0x00FD )
#define STG_E_UNIMPLEMENTEDFUNCTION \
    MAKE_SCODE( SEVERITY_ERROR, FACILITY_STORAGE, 0x00FE )
#define STG_E_INVALIDFLAG       MAKE_SCODE( SEVERITY_ERROR, FACILITY_STORAGE, 0x00FF )
#define STG_E_INUSE             MAKE_SCODE( SEVERITY_ERROR, FACILITY_STORAGE, 0x0100 )
#define STG_E_NOTCURRENT        MAKE_SCODE( SEVERITY_ERROR, FACILITY_STORAGE, 0x0101 )
#define STG_E_REVERTED          MAKE_SCODE( SEVERITY_ERROR, FACILITY_STORAGE, 0x0102 )
#define STG_E_CANTSAVE          MAKE_SCODE( SEVERITY_ERROR, FACILITY_STORAGE, 0x0103 )
#define STG_E_OLDFORMAT         MAKE_SCODE( SEVERITY_ERROR, FACILITY_STORAGE, 0x0104 )
#define STG_E_OLDDLL            MAKE_SCODE( SEVERITY_ERROR, FACILITY_STORAGE, 0x0105 )
#define STG_E_SHAREREQUIRED     MAKE_SCODE( SEVERITY_ERROR, FACILITY_STORAGE, 0x0106 )
#define STG_E_NOTFILEBASEDSTORAGE \
    MAKE_SCODE( SEVERITY_ERROR, FACILITY_STORAGE, 0x0107 )
#define STG_E_EXTANTMARSHALLINGS \
    MAKE_SCODE( SEVERITY_ERROR, FACILITY_STORAGE, 0x0108 )
#define STG_S_CONVERTED         MAKE_SCODE( SEVERITY_SUCCESS, FACILITY_STORAGE, 0x0200 )

/* Maximum storage name length */
#define CWCSTORAGENAME  32

/* Storage modes */
#define STGM_DIRECT             0x00000000L
#define STGM_TRANSACTED         0x00010000L
#define STGM_READ               0x00000000L
#define STGM_WRITE              0x00000001L
#define STGM_READWRITE          0x00000002L
#define STGM_SHARE_DENY_NONE    0x00000040L
#define STGM_SHARE_DENY_READ    0x00000030L
#define STGM_SHARE_DENY_WRITE   0x00000020L
#define STGM_SHARE_EXCLUSIVE    0x00000010L
#define STGM_PRIORITY           0x00040000L
#define STGM_DELETEONRELEASE    0x04000000L
#define STGM_CREATE             0x00001000L
#define STGM_CONVERT            0x00020000L
#define STGM_FAILIFTHERE        0x00000000L

/* Storage commit types */
typedef enum tagSTGC {
    STGC_DEFAULT                            = 0,
    STGC_OVERWRITE                          = 1,
    STGC_ONLYIFCURRENT                      = 2,
    STGC_DANGEROUSLYCOMMITMERELYTODISKCACHE = 4
} STGC;

/* Static storage */
typedef struct FARSTRUCT tagSTATSTG {
    char FAR        *pwcsName;
    DWORD           type;
    ULARGE_INTEGER  cbSize;
    FILETIME        mtime;
    FILETIME        ctime;
    FILETIME        atime;
    DWORD           grfMode;
    DWORD           grfLocksSupported;
    CLSID           clsid;
    DWORD           grfStateBits;
    DWORD           reserved;
} STATSTG;

/* Storage types */
typedef enum tagSTGTY {
    STGTY_STORAGE   = 1,
    STGTY_STREAM    = 2,
    STGTY_LOCKBYTES = 3,
    STGTY_PROPERTY  = 4
} STGTY;

/* Stream seek values */
typedef enum tagSTREAM_SEEK {
    STREAM_SEEK_SET = 0,
    STREAM_SEEK_CUR = 1,
    STREAM_SEEK_END = 2
} STREAM_SEEK;

/* Lock types */
typedef enum tagLOCKTYPE {
    LOCK_WRITE      = 1,
    LOCK_EXCLUSIVE  = 2,
    LOCK_ONLYONCE   = 4
} LOCKTYPE;

/* Storage moves */
typedef enum tagSTGMOVE {
    STGMOVE_MOVE    = 0,
    STGMOVE_COPY    = 1
} STGMOVE;

/* Statistical flags */
typedef enum tagSTATFLAG {
    STATFLAG_DEFAULT    = 0,
    STATFLAG_NONAME     = 1
} STATFLAG;

/* IEnumSTATSTG interface */
#undef INTERFACE
#define INTERFACE   IEnumSTATSTG
DECLARE_INTERFACE_( IEnumSTATSTG, IUnknown ) {
    /* IUnknown methods */
    STDMETHOD( QueryInterface )( THIS_ REFIID, LPVOID FAR * ) PURE;
    STDMETHOD_( ULONG, AddRef )( THIS ) PURE;
    STDMETHOD_( ULONG, Release )( THIS ) PURE;

    /* IEnumSTATSTG methods */
    STDMETHOD( Next )( THIS_ ULONG, STATSTG FAR *, ULONG FAR * ) PURE;
    STDMETHOD( Skip )( THIS_ ULONG ) PURE;
    STDMETHOD( Reset )( THIS ) PURE;
    STDMETHOD( Clone )( THIS_ IEnumSTATSTG FAR * FAR * ) PURE;
};
typedef IEnumSTATSTG FAR    *LPENUMSTATSTG;

/* ILockBytes interface */
#undef INTERFACE
#define INTERFACE   ILockBytes
DECLARE_INTERFACE_( ILockBytes, IUnknown ) {
    /* IUnknown methods */
    STDMETHOD( QueryInterface )( THIS_ REFIID, LPVOID FAR * ) PURE;
    STDMETHOD_( ULONG, AddRef )( THIS ) PURE;
    STDMETHOD_( ULONG, Release )( THIS ) PURE;

    /* ILockBytes methods */
    STDMETHOD( ReadAt )( THIS_ ULARGE_INTEGER, VOID HUGEP *, ULONG, ULONG FAR * ) PURE;
    STDMETHOD( WriteAt )( THIS_ ULARGE_INTEGER, VOID const HUGEP *, ULONG, ULONG FAR * ) PURE;
    STDMETHOD( Flush )( THIS ) PURE;
    STDMETHOD( SetSize )( THIS_ ULARGE_INTEGER ) PURE;
    STDMETHOD( LockRegion )( THIS_ ULARGE_INTEGER, ULARGE_INTEGER, DWORD ) PURE;
    STDMETHOD( UnlockRegion )( THIS_ ULARGE_INTEGER, ULARGE_INTEGER, DWORD ) PURE;
    STDMETHOD( Stat )( THIS_ STATSTG FAR *, DWORD ) PURE;
};
typedef ILockBytes FAR  *LPLOCKBYTES;

/* IStream interface */
#undef INTERFACE
#define INTERFACE   IStream
DECLARE_INTERFACE_( IStream, IUnknown ) {
    /* IUnknown methods */
    STDMETHOD( QueryInterface )( THIS_ REFIID, LPVOID FAR * ) PURE;
    STDMETHOD_( ULONG, AddRef )( THIS ) PURE;
    STDMETHOD_( ULONG, Release )( THIS ) PURE;

    /* IStream methods */
    STDMETHOD( Read )( THIS_ VOID HUGEP *, ULONG, ULONG FAR * ) PURE;
    STDMETHOD( Write )( THIS_ VOID const HUGEP *, ULONG, ULONG FAR * ) PURE;
    STDMETHOD( Seek )( THIS_ LARGE_INTEGER, DWORD, ULARGE_INTEGER FAR * ) PURE;
    STDMETHOD( SetSize )( THIS_ ULARGE_INTEGER ) PURE;
    STDMETHOD( CopyTo )( THIS_ IStream FAR *, ULARGE_INTEGER, ULARGE_INTEGER FAR *, ULARGE_INTEGER FAR * ) PURE;
    STDMETHOD( Commit )( THIS_ DWORD ) PURE;
    STDMETHOD( Revert )( THIS ) PURE;
    STDMETHOD( LockRegion )( THIS_ ULARGE_INTEGER, ULARGE_INTEGER, DWORD ) PURE;
    STDMETHOD( UnlockRegion )( THIS_ ULARGE_INTEGER, ULARGE_INTEGER, DWORD ) PURE;
    STDMETHOD( Stat )( THIS_ STATSTG FAR *, DWORD ) PURE;
    STDMETHOD( Clone )( THIS_ IStream FAR * FAR * ) PURE;
};
typedef IStream FAR *LPSTREAM;

/* IStorage interface */
#undef INTERFACE
#define INTERFACE   IStorage
DECLARE_INTERFACE_( IStorage, IUnknown ) {
    /* IUnknown methods */
    STDMETHOD( QueryInterface )( THIS_ REFIID, LPVOID FAR * ) PURE;
    STDMETHOD_( ULONG, AddRef )( THIS ) PURE;
    STDMETHOD_( ULONG, Release )( THIS ) PURE;

    /* IStorage methods */
    STDMETHOD( CreateStream )( THIS_ const char FAR *, DWORD, DWORD, DWORD, IStream FAR * FAR * ) PURE;
    STDMETHOD( OpenStream )( THIS_ const char FAR *, void FAR *, DWORD, DWORD, IStream FAR * FAR * ) PURE;
    STDMETHOD( CreateStorage )( THIS_ const char FAR *, DWORD, DWORD, DWORD, IStorage FAR * FAR * ) PURE;
    STDMETHOD( OpenStorage )( THIS_ const char FAR *, IStorage FAR *, DWORD, SNB, DWORD, IStorage FAR * FAR * ) PURE;
    STDMETHOD( CopyTo )( THIS_ DWORD, IID const FAR *, SNB, IStorage FAR * ) PURE;
    STDMETHOD( MoveElementTo )( THIS_ const char FAR *, IStorage FAR *, const char FAR *, DWORD ) PURE;
    STDMETHOD( Commit )( THIS_ DWORD ) PURE;
    STDMETHOD( Revert )( THIS ) PURE;
    STDMETHOD( EnumElements )( THIS_ DWORD, void FAR *, DWORD, IEnumSTATSTG FAR * FAR * ) PURE;
    STDMETHOD( DestroyElement )( THIS_ const char FAR * ) PURE;
    STDMETHOD( RenameElement )( THIS_ const char FAR *, const char FAR * ) PURE;
    STDMETHOD( SetElementTimes )( THIS_ const char FAR *, FILETIME const FAR *, FILETIME const FAR *, FILETIME const FAR * ) PURE;
    STDMETHOD( SetClass )( THIS_ REFCLSID ) PURE;
    STDMETHOD( SetStateBits )( THIS_ DWORD, DWORD ) PURE;
    STDMETHOD( Stat )( THIS_ STATSTG FAR *, DWORD ) PURE;
};
typedef IStorage FAR    *LPSTORAGE;

/* IRootStorage interface */
#undef INTERFACE
#define INTERFACE   IRootStorage
DECLARE_INTERFACE_( IRootStorage, IUnknown ) {
    /* IUnknown methods */
    STDMETHOD( QueryInterface )( THIS_ REFIID, LPVOID FAR * ) PURE;
    STDMETHOD_( ULONG, AddRef )( THIS ) PURE;
    STDMETHOD_( ULONG, Release )( THIS ) PURE;

    /* IRootStorage methods */
    STDMETHOD( SwitchToFile )( THIS_ LPSTR ) PURE;
};
typedef IRootStorage FAR    *LPROOTSTORAGE;

/* Functions in STORAGE.DLL */
STDAPI  StgCreateDocfile( const char FAR *, DWORD, DWORD, IStorage FAR * FAR * );
STDAPI  StgCreateDocfileOnILockBytes( ILockBytes FAR *, DWORD, DWORD, IStorage FAR * FAR * );
STDAPI  StgIsStorageFile( const char FAR * );
STDAPI  StgIsStorageILockBytes( ILockBytes FAR * );
STDAPI  StgOpenStorage( const char FAR *, IStorage FAR *, DWORD, SNB, DWORD, IStorage FAR * FAR * );
STDAPI  StgOpenStorageOnILockBytes( ILockBytes FAR *, IStorage FAR *, DWORD, SNB, DWORD, IStorage FAR * FAR * );
STDAPI  StgSetTimes( const char FAR *, FILETIME const FAR *, FILETIME const FAR *, FILETIME const FAR * );

#endif /* _STORAGE_H_ */

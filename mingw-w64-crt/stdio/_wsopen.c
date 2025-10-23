/**
 * This file has no copyright assigned and is placed in the Public Domain.
 * This file is part of the mingw-w64 runtime package.
 * No warranty is given; refer to the file DISCLAIMER.PD within this package.
 */

#include <stdarg.h>
#include <errno.h>
#include <share.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <io.h>
#include <windows.h>

int __cdecl _wsopen(const wchar_t *filename, int flags, int shflag, ...)
{
    int fd;
    int mode;
    HANDLE handle;
    DWORD access;
    DWORD share;
    DWORD disposition;
    DWORD attributes;
    SECURITY_ATTRIBUTES security;

    if (flags & O_CREAT) {
        va_list ap;
        va_start(ap, shflag);
        mode = va_arg(ap, int);
        va_end(ap);
    }

    if ((flags & O_ACCMODE) == O_RDONLY)
        access = GENERIC_READ;
    else if ((flags & O_ACCMODE) == O_WRONLY)
        access = GENERIC_WRITE;
    else
        access = GENERIC_READ | GENERIC_WRITE;
    if (flags & O_TEMPORARY)
        access |= DELETE;

    if (shflag == SH_DENYRW)
        share = 0;
    else if (shflag == SH_DENYWR)
        share = FILE_SHARE_READ;
    else if (shflag == SH_DENYRD)
        share = FILE_SHARE_WRITE;
    else if (shflag == SH_DENYNO)
        share = FILE_SHARE_READ | FILE_SHARE_WRITE;
    else {
        errno = EINVAL;
        return -1;
    }

    if ((flags & (O_CREAT | O_TRUNC | O_EXCL)) == O_CREAT)
        disposition = OPEN_ALWAYS;
    else if ((flags & (O_CREAT | O_TRUNC | O_EXCL)) == (O_CREAT | O_TRUNC))
        disposition = CREATE_ALWAYS;
    else if ((flags & (O_CREAT | O_EXCL)) == (O_CREAT | O_EXCL))
        disposition = CREATE_NEW;
    else if ((flags & O_TRUNC) == O_TRUNC)
        disposition = TRUNCATE_EXISTING;
    else
        disposition = OPEN_EXISTING;

    attributes = 0;
    if (flags & O_TEMPORARY)
        attributes |= FILE_FLAG_DELETE_ON_CLOSE;
    if (flags & _O_SHORT_LIVED)
        attributes |= FILE_ATTRIBUTE_TEMPORARY;
    if (flags & O_SEQUENTIAL)
        attributes |= FILE_FLAG_SEQUENTIAL_SCAN;
    if (flags & O_RANDOM)
        attributes |= FILE_FLAG_RANDOM_ACCESS;
    if ((flags & O_CREAT) && !(mode & S_IWRITE))
        attributes |= FILE_ATTRIBUTE_READONLY;
    if (attributes == 0)
        attributes = FILE_ATTRIBUTE_NORMAL;

    security.nLength = sizeof(security);
    security.lpSecurityDescriptor = NULL;
    security.bInheritHandle = !(flags & O_NOINHERIT);

    handle = CreateFileW(filename, access, share, &security, disposition, attributes, NULL);
    if (handle == NULL || handle == INVALID_HANDLE_VALUE) {
        switch (GetLastError()) {
        case ERROR_PATH_NOT_FOUND:
        case ERROR_FILE_NOT_FOUND:
            errno = ENOENT;
            break;
        case ERROR_FILE_EXISTS:
        case ERROR_ALREADY_EXISTS:
            errno = EEXIST;
            break;
        case ERROR_ACCESS_DENIED:
        case ERROR_WRITE_PROTECT...ERROR_SHARING_BUFFER_EXCEEDED:
            errno = EACCES;
            break;
        case ERROR_NOT_ENOUGH_MEMORY:
            errno = ENOMEM;
            break;
        default:
            errno = EINVAL;
            break;
        }
        return -1;
    }

    fd = _open_osfhandle((intptr_t)handle, flags);
    if (fd < 0)
        CloseHandle(handle);
    return fd;
}
int __cdecl (*__MINGW_IMP_SYMBOL(_wsopen))(const wchar_t *, int, int, ...) = _wsopen;

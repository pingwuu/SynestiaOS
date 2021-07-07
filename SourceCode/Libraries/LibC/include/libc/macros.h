//
// Created by Shifu Wu  on 2020/11/10.
//

#ifndef __LIBRARY_LIBC_MACROS_H
#define __LIBRARY_LIBC_MACROS_H

#ifndef __STRINGIFY__
#define __INTERNAL_STRINGIFY_HELPER__(x) #x
#define __STRINGIFY__(x) __INTERNAL_STRINGIFY_HELPER__(x)
#endif

#ifdef __cplusplus
#ifndef extern_C
#define extern_C extern "C"
#endif
#else
#ifndef extern_C
#define extern_C
#endif
#endif


#endif//__LIBRARY_LIBC_MACROS_H

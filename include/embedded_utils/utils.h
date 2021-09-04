//
// Created by harshil on 03/09/21.
//

#ifndef INCLUDE_EMBEDDED_UTILS_UTILS_H
#define INCLUDE_EMBEDDED_UTILS_UTILS_H

#ifndef BUFFER_SIZE
#define BUFFER_SIZE (32)
#endif
#if BUFFER_SIZE < 2
#error Buffer Size must be minimum length of 2
#endif
#define BUFFER_MASK (BUFFER_SIZE - 1)
#if (BUFFER_SIZE & BUFFER_MASK)
#error Buffer Size is not a power of 2
#endif

#endif //INCLUDE_EMBEDDED_UTILS_UTILS_H

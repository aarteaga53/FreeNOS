#ifndef __LIBPOSIX_RENICE_H
#define __LIBPOSIX_RENICE_H

#include <Macros.h>
#include "types.h"

/**
 * @brief 
 * 
 * @param pid Process ID of child to wait for.
 * @param stat_loc Points to an integer for storing the exit status.
 * @param priority Priority level to set process to.
 * @param options Optional flags.
 * @return C 
 */
extern C pid_t renicepid(pid_t pid, int priority, int *stat_loc, int options);

/**
 * @}
 * @}
 */

#endif /* __LIBPOSIX_RENICE_H */
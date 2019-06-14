#ifndef __ASSERT_H__
#define __ASSERT_H__

#ifdef __cplusplus
extern "C" {
#endif

#define DEBUG_ASSERT(x) \
    do {                \
    } while (0)
#endif

#define assert(e) DEBUG_ASSERT(e)

#ifdef __cplusplus
}
#endif

#endif  // __ASSERT_H__
#ifndef KB_LOG_H_
#define KB_LOG_H_

#define LOGD(fmt, ...)                   \
        do {                             \
            printf(fmt, ## __VA_ARGS__); \
        } while (0)

#define LOGE(fmt, ...)                   \
        do {                             \
            printf(fmt, ## __VA_ARGS__); \
        } while (0)

#endif /* KB_LOG_H_ */


#if !defined(_XLOG_H)
#define _XLOG_H

#include <cutils/log.h>
#include <cutils/alelog.h>

#ifdef __cplusplus
extern "C" {
#endif

int xlogf_java_tag_is_on(const char *name, int level);
int xlogf_native_tag_is_on(const char *name, int level);

int xlogf_java_xtag_is_on(const char *name, int level);
int xlogf_native_xtag_is_on(const char *name, int level);

#ifndef XLOG_TAG
#define XLOG_TAG NULL
#endif

#ifndef SXLOGV
#define SXLOGV(...) ((void)SXLOG_PRI(ANDROID_LOG_VERBOSE, LOG_TAG, __VA_ARGS__))
#endif
#ifndef SXLOGD
#define SXLOGD(...) ((void)SXLOG_PRI(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__))
#endif
#ifndef SXLOGI
#define SXLOGI(...) ((void)SXLOG_PRI(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__))
#endif
#ifndef SXLOGW
#define SXLOGW(...) ((void)SXLOG_PRI(ANDROID_LOG_WARN, LOG_TAG, __VA_ARGS__))
#endif
#ifndef SXLOGE
#define SXLOGE(...) ((void)SXLOG_PRI(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__))
#endif
#ifndef SXLOGF
#define SXLOGF(...) ((void)SXLOG_PRI(ANDROID_LOG_FATAL, LOG_TAG, __VA_ARGS__))
#endif
#if LOG_NDEBUG
#define SXLOG_ASSERT(cond, ...)			\
    ( (CONDITION(cond))				\
      ? ((void)SXLOGF(LOG_TAG, __VA_ARGS__))	\
      : (void)0 )
#else
#define SXLOG_ASSERT(cond, ...) ((void)0)
#endif

#define SXLOG_ALWAYS_ASSERT(cond,...)                    \
  ( (CONDITION(cond))					 \
    ? ((void)SXLOGF(LOG_TAG, __VA_ARGS__))		 \
      : (void)0 )

#ifndef XLOGV
#define XLOGV(...) ((void)XLOG_PRI(ANDROID_LOG_VERBOSE, LOG_TAG, __VA_ARGS__))
#endif
#ifndef XLOGD
#define XLOGD(...) ((void)XLOG_PRI(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__))
#endif
#ifndef XLOGI
#define XLOGI(...) ((void)XLOG_PRI(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__))
#endif
#ifndef XLOGW
#define XLOGW(...) ((void)XLOG_PRI(ANDROID_LOG_WARN, LOG_TAG, __VA_ARGS__))
#endif
#ifndef XLOGE
#define XLOGE(...) ((void)XLOG_PRI(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__))
#endif
#ifndef XLOGF
#define XLOGF(...) ((void)XLOG_PRI(ANDROID_LOG_FATAL, LOG_TAG, __VA_ARGS__))
#endif

#if LOG_NDEBUG
#define XLOG_ASSERT(cond, ...)                  \
    (!(cond)                                    \
     ? ((void)XLOGF(__VA_ARGS__))		\
     : (void)0)
#else
#define XLOG_ASSERT(cond, ...) ((void)0)
#endif

#define XLOG_ALWAY_ASSERT(cond, ...)                    \
    (!(cond)                                            \
     ? ((void)XLOGF(__VA_ARGS__))			\
     : (void)0)


#ifndef SXLOGV2
#define SXLOGV2(...) ((void)SXLOG_PRI(ANDROID_LOG_VERBOSE, XLOG_TAG, __VA_ARGS__))
#endif
#ifndef SXLOGD2
#define SXLOGD2(...) ((void)SXLOG_PRI(ANDROID_LOG_DEBUG, XLOG_TAG, __VA_ARGS__))
#endif
#ifndef SXLOGI2
#define SXLOGI2(...) ((void)SXLOG_PRI(ANDROID_LOG_INFO, XLOG_TAG, __VA_ARGS__))
#endif
#ifndef SXLOGW2
#define SXLOGW2(...) ((void)SXLOG_PRI(ANDROID_LOG_WARN, XLOG_TAG, __VA_ARGS__))
#endif
#ifndef SXLOGE2
#define SXLOGE2(...) ((void)SXLOG_PRI(ANDROID_LOG_ERROR, XLOG_TAG, __VA_ARGS__))
#endif
#ifndef SXLOGF2
#define SXLOGF2(...) ((void)SXLOG_PRI(ANDROID_LOG_FATAL, XLOG_TAG, __VA_ARGS__))
#endif

#ifndef XLOGV2
#define XLOGV2(...) ((void)XLOG_PRI(ANDROID_LOG_VERBOSE, XLOG_TAG, __VA_ARGS__))
#endif
#ifndef XLOGD2
#define XLOGD2(...) ((void)XLOG_PRI(ANDROID_LOG_DEBUG, XLOG_TAG, __VA_ARGS__))
#endif
#ifndef XLOGI2
#define XLOGI2(...) ((void)XLOG_PRI(ANDROID_LOG_INFO, XLOG_TAG, __VA_ARGS__))
#endif
#ifndef XLOGW2
#define XLOGW2(...) ((void)XLOG_PRI(ANDROID_LOG_WARN, XLOG_TAG, __VA_ARGS__))
#endif
#ifndef XLOGE2
#define XLOGE2(...) ((void)XLOG_PRI(ANDROID_LOG_ERROR, XLOG_TAG, __VA_ARGS__))
#endif
#ifndef XLOGF2
#define XLOGF2(...) ((void)XLOG_PRI(ANDROID_LOG_FATAL, XLOG_TAG, __VA_ARGS__))
#endif

struct xlog_record {
	const char *tag_str;
	const char *fmt_str;
	int prio;
};

#if defined(__cplusplus)
extern "C" {
#endif

int __xlog_buf_printf(int bufid, const struct xlog_record *rec, ...);

#if defined(__cplusplus)
}
#endif

#if !defined(HAVE_ALE_FEATURE)

#define xlog_buf_printf(bufid, prio, tag, fmt, ...)			\
	({								\
		static const struct xlog_record _xlog_rec =		\
			{tag, fmt, prio};				\
		__xlog_buf_printf(bufid, &_xlog_rec, ##__VA_ARGS__);	\
	})

#else

#define xlog_buf_printf(bufid, prio, tag, fmt, ...)			\
  ({									\
      static const struct ale_convert ____xlog_ale_rec____ =		\
          { tag, fmt, __FILE__, prio, 0, "" };				\
      ale_log_output(bufid, prio, &____xlog_ale_rec____,		\
                     ##__VA_ARGS__);                                    \
  })

#endif

#define XLOG_PRI(priority, tag, ...)                            \
    xlog_buf_printf(LOG_ID_MAIN, priority, tag, __VA_ARGS__)

#define SXLOG_PRI(priority, tag, ...)                           \
    xlog_buf_printf(LOG_ID_MAIN, priority, tag, __VA_ARGS__)

#define xlog_printf(priority, tag, ...)                         \
    xlog_buf_printf(LOG_ID_MAIN, priority, tag, __VA_ARGS__)

#define sxlog_printf(priority, tag, ...)                        \
    xlog_buf_printf(LOG_ID_SYSTEM, priority, tag, __VA_ARGS__)


#ifdef __cplusplus
}
#endif

#endif

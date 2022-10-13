/*this is the file "my_log.h"*/
#ifndef _MY_LOG_H_
#define _MY_LOG_H_
 
#include "stdio.h"
#include "stdlib.h"
#include "time.h"
 
/*[LOG_ABLE_EN]:enable log 
**[LOG_ABLE_DIS]:disenable log
*/
#define LOG_ABLE_DIS 0
#define LOG_ABLE_EN 1
#define LOG_ABLE LOG_ABLE_EN 
 
/*[LOG_REDIRECT_CONSOLE]:log ourput to console  
**[LOG_REDIRECT_FILE]:log output to "specific file".
**[LOG_FILE_PATH]:previous line mentions "specific file".
*/
#define LOG_REDIRECT_CONSOLE 0
#define LOG_REDIRECT_FILE 1
#define LOG_REDIRECT LOG_REDIRECT_FILE
#define LOG_FILE_PATH "/home/user/test/syslog_test/log"
 
#define COLOR_END "\033[0m"
#define COLOR_BLUE "\033[34m"
#define COLOR_YELLOW "\033[33m"
#define COLOR_RED "\033[31m"
 
#define COLOR_INF COLOR_BLUE
#define COLOR_DBG COLOR_BLUE
#define COLOR_WAR COLOR_YELLOW
#define COLOR_ERR COLOR_RED
#define COLOR_FER COLOR_RED
 
#if LOG_REDIRECT==LOG_REDIRECT_FILE
#define LOG_OUT_REDIRECT(log_type, f, ...)                           \
    time_t time_re;                                                  \
    time(&time_re);                                                  \
    struct tm time_ex;                                               \
    localtime_r(&time_re, &time_ex);                                 \
    char time_str[100] = {0};                                        \
    sprintf(time_str, "%d-%d-%d-%d:%d:%d",                           \
            time_ex.tm_year + 1900, time_ex.tm_mon, time_ex.tm_mday, \
            time_ex.tm_hour, time_ex.tm_min, time_ex.tm_sec);        \
    FILE *file = fopen(LOG_FILE_PATH, "a");                          \
    if (file == NULL)                                                \
        break;                                                       \
    fprintf(file,                                                    \
            "[" #log_type "]-"                                       \
            "[%s]-"                                                  \
            "[%s]:" f,                                               \
            time_str,                                                \
            __func__, ##__VA_ARGS__);                                \
    fclose(file);
 
#else
#define LOG_OUT_REDIRECT(log_type, f, ...)                           \
    time_t time_re;                                                  \
    time(&time_re);                                                  \
    struct tm time_ex;                                               \
    localtime_r(&time_re, &time_ex);                                 \
    char time_str[100] = {0};                                        \
    sprintf(time_str, "%d-%d-%d-%d:%d:%d",                           \
            time_ex.tm_year + 1900, time_ex.tm_mon, time_ex.tm_mday, \
            time_ex.tm_hour, time_ex.tm_min, time_ex.tm_sec);        \
    printf(COLOR_##log_type                                          \
           "[" #log_type "]-"                                        \
           "[%s]-"                                                   \
           "[%s]:" f COLOR_END,                                      \
           time_str,                                                 \
           __func__, ##__VA_ARGS__);
#endif
 
#if LOG_ABLE==LOG_ABLE_EN 
#define LOG(log_type, r, f, ...)                     \
    do                                               \
    {                                                \
        LOG_OUT_REDIRECT(log_type, f, ##__VA_ARGS__) \
        r;                                           \
    } while (0)
#else
#define LOG(log_type, r, f, ...)
#endif
 
#define INF(f, ...) LOG(INF, break, f, ##__VA_ARGS__)
#define DBG(f, ...) LOG(DBG, break, f, ##__VA_ARGS__)
#define WAR(f, ...) LOG(WAR, break, f, ##__VA_ARGS__)
#define ERR(f, ...) LOG(ERR, break, f, ##__VA_ARGS__)
#define FER(f, ...) LOG(FER, abort(), f, ##__VA_ARGS__)
 
#endif
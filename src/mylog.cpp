/***************************************************************************
 * 
 * Copyright (c) 2013 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file mylog.cpp
 * @author liujun05(com@baidu.com)
 * @date 2013/12/14 15:38:04
 * @brief 
 *  
 **/

#include "mylog.h"

//写日志文件锁
pthread_mutex_t log_mutex_normal = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t log_mutex_wf = PTHREAD_MUTEX_INITIALIZER;

//全局log结构体
mylog_info_t g_log_ins;

/*
 *全局日志初始化函数
 */
int my_log_init(const char* log_path, const char* normal_file, const char* warn_fatal_file, const int log_level)
{
    //先查看是否有这个文件夹
    if( access(log_path, F_OK) != 0 )
    {
        if (mkdir("flow", 0777))
        {
            fprintf(stderr, "the logpath[%s] not exist, and create fail", log_path);
            return -1;
        }
    }

    g_log_ins.log_level = log_level;

    //打开正常文件句柄
    snprintf(g_log_ins.normal_log_file, sizeof(g_log_ins.normal_log_file),
            "%s/%s", log_path, normal_file );
    g_log_ins.normal_log_fd = fopen(g_log_ins.normal_log_file, "a+");
    if( NULL == g_log_ins.normal_log_fd) 
    {
        fprintf(stderr, "open noraml log path[%s] fail", g_log_ins.normal_log_file);
        return -1;
    }
    //打开异常文件句柄
    snprintf(g_log_ins.warn_fatal_log_file, sizeof(g_log_ins.warn_fatal_log_file),
            "%s/%s", log_path, warn_fatal_file);
    g_log_ins.warn_fatal_log_fd = fopen(g_log_ins.warn_fatal_log_file, "a+");

    if(NULL == g_log_ins.warn_fatal_log_fd ) 
    {
        fprintf(stderr, "open wf log path[%s] fail", g_log_ins.warn_fatal_log_file);
        fclose(g_log_ins.normal_log_fd);
        return -1;
    }
    lj_log_pecific_init();
    return 0;
}

/*
 *初始化线程数据
 */
int my_log_thread_init()
{
    return lj_log_pecific_init();
}

/*
 * 按照level打印日志
 */
int my_log_print(const int log_level, const char* logfmt, ...)
{
    //如果日志级别不需要输出日志
    if( log_level > g_log_ins.log_level)
    {
        return 0;
    }
    //如果loglevel不对
    if( g_log_ins.normal_log_fd == NULL || g_log_ins.warn_fatal_log_fd == NULL)
    {
        fprintf(stderr,"your fd is null\n");
        return -1;
    }

    //加写锁
    //如果是写正常日志，加正常日志锁
    if(log_level > MY_LOG_LEVEL_WARNNING )
    {
        pthread_mutex_lock(&log_mutex_normal);
    }
    else
    {
        pthread_mutex_lock(&log_mutex_wf);
    }
    //执行参数列表
    va_list argp;
    va_start(argp, logfmt);
    
    //log_str
    char log_str[MAX_LOG_LEN];
    if( -1 == vsnprintf(log_str, sizeof(log_str), logfmt, argp) )
    {
        log_str[0] = '\0';
    }

    FILE* current_fd;

    //打印日志级别
    switch(log_level)
    {
        case MY_LOG_LEVEL_FATAL:
            fprintf(g_log_ins.warn_fatal_log_fd, "FATAL: ");
            current_fd = g_log_ins.warn_fatal_log_fd;
            break;
        case MY_LOG_LEVEL_WARNNING:
            fprintf(g_log_ins.warn_fatal_log_fd, "WARNING: ");
            current_fd = g_log_ins.warn_fatal_log_fd;
            break;
        case MY_LOG_LEVEL_NOTICE:
            fprintf(g_log_ins.normal_log_fd, "NOTICE: ");
            current_fd = g_log_ins.normal_log_fd;
            break;
        case MY_LOG_LEVEL_TRACE:
            fprintf(g_log_ins.normal_log_fd, "TRACE: ");
            current_fd = g_log_ins.normal_log_fd;
            break;
        case MY_LOG_LEVEL_DEBUG:
            fprintf(g_log_ins.normal_log_fd, "DEBUG: ");
            current_fd = g_log_ins.normal_log_fd;
            break;
        default:
            fprintf(g_log_ins.normal_log_fd, "DEBUG: ");
            current_fd = g_log_ins.normal_log_fd;
            break;
    }

    //获得当前时间
    struct tm *now;
    struct timeb tb;

    //当前月份
    ftime(&tb);
    now=localtime(&tb.time);
    char tmp_data_str[1024];
    sprintf(tmp_data_str,"%04d-%02d-%02d",now->tm_year+1900,now->tm_mon+1,now->tm_mday);
    //当前时间
    char tmp_time_str[1024];
    sprintf(tmp_time_str,"%02d:%02d:%02d",now->tm_hour ,now->tm_min  ,now->tm_sec );
    //打印参数
    fprintf(current_fd ,"%s %s %s\n", tmp_data_str, tmp_time_str, log_str);
    //立即写入磁盘
    fflush(current_fd);
    //结束列表
    va_end(argp);
    //解锁
    if(log_level > MY_LOG_LEVEL_WARNNING )
    {
        pthread_mutex_unlock(&log_mutex_normal);
    }
    else
    {
        pthread_mutex_unlock(&log_mutex_wf);
    }
    return 0;
}

/*
 *关闭日志句柄
 */
int my_log_close()
{
    fclose(g_log_ins.normal_log_fd);
    fclose(g_log_ins.warn_fatal_log_fd);
    return 0;
}

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */

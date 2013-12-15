/***************************************************************************
 * 
 * Copyright (c) 2013 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file mylog.h
 * @author liujun05(com@baidu.com)
 * @date 2013/12/14 15:35:27
 * @brief log头文件 
 *  
 **/
#ifndef  __MYLOG_H_
#define  __MYLOG_H_

#include "mylog_define.h"
#include "log.h"
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/timeb.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdarg.h>
#include <stdio.h>

//全局日志信息
typedef struct _mylog_info_t
{
    FILE* normal_log_fd;
    FILE* warn_fatal_log_fd;
    char normal_log_file[MAX_FILE_NAME_LEN];
    char warn_fatal_log_file[MAX_FILE_NAME_LEN];
    int log_level;
}mylog_info_t, *mylog_info;

//打印线程日志
#define MY_LOG_FATAL(logfmt, arg...) \
    do { \
        my_log_print(MY_LOG_LEVEL_FATAL, "[%s:%d] logid[%u] reqid[%s] mod[%s] exec_time[%s] " logfmt,  \
                 __FILE__, __LINE__, lj_log_get_logid() , lj_log_get_reqip(), lj_log_get_mod(), lj_log_get_exec_time(), ## arg); \
    }while(0)

//打印线程WARNING日志
#define MY_LOG_WARNNING(logfmt, arg...) \
    do { \
        my_log_print(MY_LOG_LEVEL_WARNNING, "[%s:%d] logid[%u] reqid[%s] mod[%s] exec_time[%s] " logfmt,  \
                 __FILE__, __LINE__, lj_log_get_logid() , lj_log_get_reqip(), lj_log_get_mod(), lj_log_get_exec_time(), ## arg); \
    }while(0)

//打印线程NOTICE日志
#define MY_LOG_NOTICE(logfmt, arg...) \
    do { \
        my_log_print(MY_LOG_LEVEL_NOTICE, "[%s:%d] logid[%u] reqid[%s] mod[%s] exec_time[%s] " logfmt,  \
                 __FILE__, __LINE__, lj_log_get_logid() , lj_log_get_reqip(), lj_log_get_mod(), lj_log_get_exec_time(), ## arg); \
    }while(0)

//打印线程TRACE日志
#define MY_LOG_TRACE(logfmt, arg...) \
    do { \
        my_log_print(MY_LOG_LEVEL_TRACE, "[%s:%d] logid[%u] reqid[%s] mod[%s] exec_time[%s] " logfmt,  \
                 __FILE__, __LINE__, lj_log_get_logid() , lj_log_get_reqip(), lj_log_get_mod(), lj_log_get_exec_time(), ## arg); \
    }while(0)

//打印线程DEBUG日志
#define MY_LOG_DEBUG(logfmt, arg...) \
    do { \
        my_log_print(MY_LOG_LEVEL_DEBUG, "[%s:%d] logid[%u] reqid[%s] mod[%s] exec_time[%s] " logfmt,  \
                 __FILE__, __LINE__, lj_log_get_logid() , lj_log_get_reqip(), lj_log_get_mod(), lj_log_get_exec_time(), ## arg); \
    }while(0)

/* 设置logid */
#define my_log_set_logid(logid) lj_log_set_logid(logid)

/* 设置请求ip: reqip */
#define my_log_set_reqip(reqip) lj_log_set_reqip(reqip)

/* 设置模块名mod */
#define my_log_set_mod(mod) lj_log_set_mod(mod)

/* 设置打印执行时间计算方式 0:ms, 1: us */
#define my_log_set_time_type(time_type) lj_log_set_time_type(time_type)

/*
 *按照日志level打印日志(定义logcheck则需要显式去检验格式是否正确)
 */
#ifdef MY_LOG_CHECK
int my_log_print(const int log_level, const char* logfmt ...) __attribute__ ((format (printf,2,3)));
#else
int my_log_print(const int log_level, const char* logfmt ...);
#endif

/*
 *全局日志初始化函数
 */
int my_log_init(const char* log_path, const char* normal_path, const char* warn_fatal_path, const int log_level);

/*
 *线程初始化函数
 */
int my_log_thread_init();

#endif  //__MYLOG_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */

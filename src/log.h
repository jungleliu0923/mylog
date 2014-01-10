/***************************************************************************
 * 
 * Copyright (c) 2013 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file log.h
 * @author liujun05(com@baidu.com)
 * @date 2013/12/14 16:39:57
 * @brief log定义 
 *  
 **/


#ifndef  __LOG_H_
#define  __LOG_H_

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include "mylog_define.h"
#include "pthread.h"

#define TIME_TYPE_MSEC 0
#define TIME_TYPE_USEC  1


//线程私有数据结构体
typedef struct _log_info_t
{
    long m_logid;
    char m_reqip[MAX_LITTLE_LEN];
    char m_time_str[MAX_LITTLE_LEN];
    struct timeval m_start_time;
    int m_time_type;
    char m_mod[MAX_LITTLE_LEN];
}log_info_t, *log_info;

/*
 * 线程私有数据初始化
 */
int lj_log_pecific_init();

/*
 * 重新设置logid
 */
int lj_log_set_logid(uint32 log_id);

/*
 *获取logid
 */
long lj_log_get_logid() ;

/*
 *设置请求的ip
 */
int lj_log_set_reqip(const char* reqip);

/*
 *获得请求的ip
 */
char* lj_log_get_reqip();

/*
 *获得执行时间
 */
char* lj_log_get_exec_time();

/*
 *设置执行时间的type， 0:ms, 1us
 */
int lj_log_set_time_type(int time_type);

/* 设置线程计时时间 */
int lj_log_reset_start_time();

/*
 *获得执行时间的type
 */
int lj_log_get_time_type();

/*
 *设置当前线程模块名称
 */
int lj_log_set_mod(const char* mod);

/*
 *获得当前线程模块名称
 */
char* lj_log_get_mod();

#endif  //__LOG_H

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */

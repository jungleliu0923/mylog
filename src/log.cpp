/***************************************************************************
 * 
 * Copyright (c) 2013 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file log.cpp
 * @author liujun05(com@baidu.com)
 * @date 2013/12/14 16:58:22
 * @brief 
 *  
 **/

#include "log.h"
#include <iostream>
using namespace std;

static pthread_key_t g_log_key;
static pthread_once_t  g_log_once=PTHREAD_ONCE_INIT;

/*
 *线程析构
 */
static void lj_log_data_destroy(void *plog_ins)
{
	log_info plog;
    plog = (log_info)plog_ins;
    if(NULL != plog)
    {
        free(plog);
    }
}

/*
 *线程初始化函数
 */
static void gen_key()
{
    pthread_key_create(&g_log_key, lj_log_data_destroy);
}

/*
 * 线程私有数据初始化
 */
int lj_log_pecific_init()
{
    pthread_once(&g_log_once, gen_key);

    log_info plog;
    plog = (log_info)pthread_getspecific(g_log_key);
    if( NULL == plog)
    {
        plog = (log_info)malloc(sizeof(log_info_t));
        if( NULL == plog)
        {
            return -1;
        }
    }
    gettimeofday(&plog->m_start_time,NULL);
    plog->m_logid = 0;
	plog->m_reqip[0] = '\0';
	plog->m_mod[0] = '\0';
	plog->m_time_type = TIME_TYPE_USEC;
	//设置变量
	pthread_setspecific(g_log_key, (const void*)plog);
    return 0;
}


/*
 * 线程私有数据初始化
 */
int lj_log_set_logid(uint32 log_id)
{
    log_info plog;
    plog = (log_info)pthread_getspecific(g_log_key);
    if(NULL == plog)
    {
        return 0;
    }
    plog->m_logid = log_id;
    return log_id;
}

/*
 * 设置线程计时时间
 */
int lj_log_reset_start_time()
{
    log_info plog;
    plog = (log_info)pthread_getspecific(g_log_key);
    if(NULL == plog)
    {
        return 0;
    }
    gettimeofday(&plog->m_start_time,NULL);
	return 0;
}


/*
 *获取logid
 */
long lj_log_get_logid()
{
    log_info plog;
    plog = (log_info)pthread_getspecific(g_log_key);
    if(NULL == plog)
    {
        return 0;
    }
    return plog->m_logid;
}


/*
 *设置请求的ip
 */
int lj_log_set_reqip(const char* reqip)
{
    log_info plog;
    plog = (log_info)pthread_getspecific(g_log_key);
    if(NULL == plog)
    {
        return 0;
    }
    strncpy(plog->m_reqip, reqip, sizeof(plog->m_reqip) );
    return 0;
}

/*
 *获得请求的ip
 */
char* lj_log_get_reqip()
{
    log_info plog;
    plog = (log_info)pthread_getspecific(g_log_key);
    if(NULL == plog)
    {
        return "";
    }
	return plog->m_reqip;
}

/*
 *设置当前线程模块名称
 */
int lj_log_set_mod(const char* mod)
{
    log_info plog;
    plog = (log_info)pthread_getspecific(g_log_key);
    if(NULL == plog)
    {
        return 0;
    }
    strncpy(plog->m_mod, mod, sizeof(plog->m_mod) );
    return 0;
}

/*
 *获得当前线程模块名称
 */
char* lj_log_get_mod()
{
    log_info plog;
    plog = (log_info)pthread_getspecific(g_log_key);
    if(NULL == plog)
    {
        return "";
    }
	return plog->m_mod;
}

/*
 *获得执行时间
 */
char* lj_log_get_exec_time()
{
    log_info plog;
    plog = (log_info)pthread_getspecific(g_log_key);
    if(NULL == plog)
    {
        return 0;
	}
	struct timeval end_time;
	gettimeofday(&end_time, NULL);
	uint32 time_diff = 0;
	time_diff =  1000000 * (end_time.tv_sec- plog->m_start_time.tv_sec) + end_time.tv_usec - plog->m_start_time.tv_usec;

	if(plog->m_time_type == TIME_TYPE_MSEC )
	{
		snprintf(plog->m_time_str, sizeof(plog->m_time_str), "%lf(ms)", 1.0 * time_diff / 1000);
	}
	else 
	{
		snprintf(plog->m_time_str, sizeof(plog->m_time_str), "%u(us)", time_diff);
	}
	return plog->m_time_str;
}

/*
 *设置执行时间的type， 0:ms, 1us
 */
int lj_log_set_time_type(int time_type)
{
    log_info plog;
    plog = (log_info)pthread_getspecific(g_log_key);
    if(NULL == plog)
    {
        return 0;
    }
    plog->m_time_type = time_type;
	return 0;
}

/*
 *获得执行时间的type
 */
int lj_log_get_time_type()
{
    log_info plog;
    plog = (log_info)pthread_getspecific(g_log_key);
    if(NULL == plog)
    {
        return 0;
    }
    return plog->m_time_type;
}

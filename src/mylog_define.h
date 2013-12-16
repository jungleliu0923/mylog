/***************************************************************************
 * 
 * Copyright (c) 2013 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file mylog_define.h
 * @author liujun05(com@baidu.com)
 * @date 2013/12/14 16:43:16
 * @brief 
 *  
 **/

#ifndef  __MYLOG_DEFINE_H_
#define  __MYLOG_DEFINE_H_

#ifndef UNSIGNED_LONG
#define uint32 unsigned int
#endif

#ifndef UNSIGNED_LONG_LONG
#define uint64 unsigned long long
#endif

#define MAX_FILE_NAME_LEN 1024
#define MAX_LITTLE_LEN 1024
#define MAX_LOG_LEN 10240

#define MY_LOG_LEVEL_FATAL 1
#define MY_LOG_LEVEL_WARNNING 2
#define MY_LOG_LEVEL_NOTICE 4
#define MY_LOG_LEVEL_TRACE 8
#define MY_LOG_LEVEL_DEBUG 16


#endif  
//__MYLOG_DEFINE_H_
/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */

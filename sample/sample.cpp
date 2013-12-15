/***************************************************************************
 * 
 * Copyright (c) 2013 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file sample.cpp
 * @author liujun05(com@baidu.com)
 * @date 2013/12/14 22:51:02
 * @brief 
 *  
 **/

#include "mylog.h"

void* test_thread1(void*)
{
    my_log_thread_init();
    my_log_set_reqip("10.10.10.31");
    my_log_set_time_type(TIME_TYPE_MSEC);
    for(int i=0; i<100; i++)
    {
        my_log_set_logid(i);
        MY_LOG_FATAL("thread 1 fatal is at %d, it's %s", i , "OK");
        MY_LOG_WARNNING("thread 1 warning is at %d, it's %s", i , "OK");
        MY_LOG_NOTICE("thread 1 notice is at %d, it's %s", i , "OK");
        MY_LOG_TRACE("thread 1 trace is at %d, it's %s", i , "OK");
        MY_LOG_DEBUG("thread 1 debug is at %d, it's %s", i , "OK");
        sleep(1);
    
    }
}

void* test_thread2(void*)
{
    my_log_thread_init();
    for(int i=0; i<3; i++)
    {
        my_log_set_mod("test2");
        MY_LOG_FATAL("thread 2 fatal is at %d, it's %s", i , "OK");
        MY_LOG_WARNNING("thread 2 warning is at %d, it's %s", i , "OK");
        MY_LOG_NOTICE("thread 2 notice is at %d, it's %s", i , "OK");
        MY_LOG_TRACE("thread 2 trace is at %d, it's %s", i , "OK");
        MY_LOG_DEBUG("thread 2 debug is at %d, it's %s", i , "OK");
        sleep(1);
    }
}

int main()
{
    my_log_init(".", "test.log", "test.log.wf", 16);
    MY_LOG_DEBUG("main begin");

    pthread_t t1, t2;
    pthread_create(&t1, NULL, test_thread1, NULL);
    pthread_create(&t2, NULL, test_thread2, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    MY_LOG_DEBUG("main end");
}






/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */

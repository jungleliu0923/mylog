1 说明<br>
1) 本文件夹包含源码src以及示例文件sample<br>
2) 编译src生成output(包括iånclude和lib)<br>
3) 使用output的lib和include,具体可以查看sample的Makefile和code<br>
4) 日志级别为FATAL, WARNING, NOTICE, TRACE, DEBUG，以此级别变低<br>
5) 使用MY_LOG_FATAL等打印日志，和printf使用方式类似，非常简单。<br>

2 使用API(查看mylog.h)<br>

1) 初始化日志目录
```c
my_log_init(const char* log_path, const char* normal_path, const char* warn_fatal_path, const int log_level)
```
   log_path ： log路径
   normal_path : 正常日志目录
   warn_fatal_path ： 异常日志目录
   log_level : 日志级别

2) 初始化线程日志数据
```c
    my_log_thread_init() 
```
多线程使用

3) 设置一个线程的logid
```c
my_log_set_logid(logid)
```
必须在my_log_thread_init() 之后使用。

4) 设置一个线程的reqip <br>
```c
my_log_set_reqip(reqip)
```

必须在my_log_thread_init() 之后使用.

5) 设置一个线程的reqip
```c
my_log_set_mod(mod)
```
设置一个线程的reqip, 必须在单线程中使用或者my_log_thread_init() 之后使用.

6)设置计算执行时间的类型（打印时间是ms还是us)
```c
 my_log_set_time_type(time_type)
```
必须在单线程中使用或者my_log_thread_init() 之后使用.

7) 打印FATAL日志
```c
MY_LOG_FATAL(logfmt, arg...) 
```
日记级别 >=1会打印 FATAL日志。

8)打印WARNNING日志
```c
MY_LOG_WARNING(logfmt, arg...) 
```
日记级别 >=2会打印 WARNING日志。

9) 打印NOTICE日志
```c
MY_LOG_NOTICE(logfmt, arg...) 
```
日记级别 >=4会打印 NOTICE日志。

10)打印TRACE日志
```c
MY_LOG_TRACE(logfmt, arg...) 
```
日记级别 >=8会打印TRACE日志。

11) 打印DEBUG日志
```c
MY_LOG_DEBUG(logfmt, arg...) 
```
日记级别 >=16会打印DEBUG日志。

3 范例<br>

   1) code<br>
```c
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
```
2) 执行结果

![blob](http://git.oschina.net/uploads/images/2013/1215/152929_2bce7fcf_60197.png)


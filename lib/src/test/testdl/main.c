#include <stdio.h>  
#include <stdlib.h>  
#include <dlfcn.h>  
#include <signal.h>  
#include <errno.h>  
  
//输出错误信息并退出        
void error_quit(const char *str)        
{        
    fprintf(stderr, "%s\n", str);     
    exit(1);        
}    
  
int main(int argc, char *argv [])  
{  
    void *plib;                     //指向so文件的指针  
    typedef void (*FUN_HELLO)();  
    typedef int (*FUN_ADD)(int, int);  
    FUN_HELLO funHello = NULL;      //函数指针  
    FUN_ADD funAdd = NULL;  
  
    //打开so文件  
    //为了方便演示，我将库文件和可执行文件放在同一个目录下  
    plib = dlopen("./libtest.so", RTLD_NOW | RTLD_GLOBAL);  
    if( NULL == plib )  
        error_quit("Can't open the libtest.so");  
  
    //加载函数void Hello()  
    funHello = dlsym(plib, "Hello");  
    if( NULL == funHello )  
        error_quit("Can't load function 'Hello'");  
      
    //加载函数int Add(int a, int b)  
    funAdd = dlsym(plib, "Add");  
    if( NULL == funAdd )  
        error_quit("Can't load function 'Add'");  
  
    //调用成功加载的函数  
    funHello();  
    printf("5 + 8 = %d\n", funAdd(5, 8));  
  
    //关闭so文件  
    dlclose(plib);  
  
    return 0;  
}  
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <regex.h>

/* 取子串的函数 */ 
static char* substr(const char*str,unsigned start, unsigned end)
{
    unsigned n = end - start;
    static char stbuf[256];
    strncpy(stbuf, str + start, n);
    stbuf[n] = 0;
    return stbuf;
}

int main(int argc, char** argv)
{
    char *pattern = NULL; 
    int x, z, lno = 0, cflags = 0; 
    char ebuf[128], lbuf[256]; 
    regex_t reg; 

    /* 编译正则表达式*/ 
    pattern = argv[1]; 
    z = regcomp(&reg, pattern, cflags); 

    if (z != 0)
    {
            regerror(z, &reg, ebuf, sizeof(ebuf)); 
            fprintf(stderr, "%s: pattern '%s' \n",ebuf, pattern); 
            exit(1); 
    }

    regmatch_t *pm = NULL; 
    size_t nmatch = reg.re_nsub + 1;
    pm = (regmatch_t*)malloc(sizeof(regmatch_t) * nmatch);

    /* 逐行处理输入的数据 */ 
    while(fgets(lbuf, sizeof(lbuf), stdin))
    {
            ++lno;
            if((z = strlen(lbuf)) > 0 && lbuf[z-1] == '\n')
	    {
		    lbuf[z - 1] = 0;
	    }
    
            /* 对每一行应用正则表达式进行匹配 */
            z = regexec(&reg, lbuf, nmatch, pm, 0);
            if(z == REG_NOMATCH)
	    {
		    continue;
	    }
            else if(z != 0)
            {
	                regerror(z, &reg, ebuf, sizeof(ebuf));
	                fprintf(stderr, "%s: regcom('%s')\n",ebuf, lbuf);
			exit(1);
	    }

            /* 输出处理结果 */
            for(x = 0; x < nmatch; ++x)
            {
	                printf("%04d: %s\n", lno, lbuf);
	                printf("$%d='%s'\n", x, substr(lbuf, pm[x].rm_so,pm[x].rm_eo));
	    }
    }

    free(pm);
    /* 释放正则表达式 */ 
    regfree(&reg);     
    return 0;
}

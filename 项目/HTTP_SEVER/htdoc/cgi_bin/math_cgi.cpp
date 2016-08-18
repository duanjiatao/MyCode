//math_cgi.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define METHOD "REQUEST_METHOD"
#define QUERY "QUERY_STRING"
#define CONTLEN "CONTENT_LENGTH"
#define _SIZE_ 1024

void math_add(char* data_string)
{
    if(!data_string)
    {
        return;
    }

    //data1=xxx&data2=xxx
    char* data1 = NULL;
    char* data2 = NULL;
    char* ptr = data_string;

    while(*ptr != '\0')
    {
        if(*ptr == '=' && data1 == NULL)
        {
            data1 =  ptr + 1;
            ++ptr;
            continue;
        }
        if(*ptr == '=' && data2 == NULL && data1 != NULL)
        {
            data2 =  ptr + 1;
            break;
        }
        if(*ptr == '&')
        {
            *ptr = '\0';
        }

        ++ptr;
    }

    int data1_int = atoi(data1);
    int data2_int = atoi(data2);
    int add_res = data1_int + data2_int;

    printf("<html>\n");
    printf("<center>\n<h1>\n");

    printf("%d + %d = %d\n", data1_int, data2_int, add_res);

    printf("</h1>\n</center>\n");
    printf("</html>");

}

int main()
{
    char method[_SIZE_/10];
    char query_string[_SIZE_];
    int content_length = -1;
    memset(method, '\0', sizeof(method));
    memset(query_string, '\0', sizeof(query_string));

    if(getenv(METHOD))
    {
        strcpy(method, getenv(METHOD));
    }

    if(strcasecmp(method, "GET") == 0) //GET
    {
        if(getenv(QUERY))
        {
            strcpy(query_string, getenv(QUERY));
        }
        math_add(query_string);
    }
    else if (strcasecmp(method, "POST") == 0) //POST
    {
        if(getenv(CONTLEN))
        {
            content_length = atoi(getenv(CONTLEN));
        }

        if(content_length != -1)
        {
            int i = 0;
            char c = '\0';
            for(; i < content_length; ++i)
            {
                read(0, &c, 1);
                query_string[i] = c;
            }
            query_string[i] = '\0'; //can cancel
            math_add(query_string);
        }
    }
    else
    {
        return 1;
    }

    return 0;
}

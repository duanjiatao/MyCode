//httpd.c

#include "httpd.h"

 

void usage(const char* proc)
{
    printf("%s usage: [IP] [PORT]\n", proc);
}

void print_log(const char* fun, int line, int err_no, const char* err_str)
{
    printf("%s : %d  %d : %s\n", fun, line, err_no, err_str);
}

void print_debug(const char* info, const char* msg)
{
#ifdef _DEBUG_
    printf("%s  %s\n", info, msg);
#endif
}

void clear_head(int sock)
{
    char buf[_SIZE_];
    memset(buf, '\0', sizeof(buf));
    int num_chars = 0;

    do
    {
        num_chars = get_line(sock, buf, sizeof(buf));
    }
    while(num_chars > 0 && strcmp(buf, "\n") != 0);
}

int get_line(int sock, char* buf, int max_len)
{
    if(!buf || max_len < 0)
    {
        return -1;
    }

    int i = 0;
    int n = 0;
    char c = '\0';
    while(i < max_len-1 && c != '\n')
    {
        n = recv(sock, &c, 1, 0);
        if(n > 0) //success
        {
            if(c == '\r')
            {
                n = recv(sock, &c, 1, MSG_PEEK);
                if(n > 0 && c == '\n')
                {
                    recv(sock, &c, 1, 0);  //delete '\n'
                }
                else
                {
                    c = '\n';
                }
            }

            buf[i++] = c;
        }
        else
        {
            c = '\n';  //break
        }
    }

    buf[i] = '\0';
    return i;
}


void echo_html(int client,const char* path, size_t file_size)
{
    if(!path)
    {
        print_debug("path not exist", "");
        return;
    }

    int fd = open(path, O_RDONLY);
    if(fd < 0)
    {
        print_log(__FUNCTION__, __LINE__, errno, strerror(errno));
        return;
    }

    print_debug("file open success", "");

    char echo_line[_SIZE_];
    memset(echo_line, '\0', sizeof(echo_line));
    strcat(echo_line, HTTP_VERSION);
    strcat(echo_line, " 200 OK");
    strcat(echo_line, "\r\n\r\n");

    if(send(client, echo_line, strlen(echo_line), 0) < 0)
    {
        print_log(__FUNCTION__, __LINE__, errno, strerror(errno));
        return;
    }
    print_debug("send echo head success", "");

    int send_bytes = -1;
    if((send_bytes = sendfile(client, fd, NULL, file_size)) < 0)
    {
        print_log(__FUNCTION__, __LINE__, errno, strerror(errno));
        close(fd);
        return;
    }
    printf("send file success, size : %d byte\n", send_bytes);

}

void exe_cgi(int client, const char* method, const char* path, const char* query_string)
{
   if(!method || !path) 
   {
       print_debug("exe_cgi argument error", "");
       return;
   }

   char buf[_SIZE_];
   memset(buf, '\0', sizeof(buf));
   int content_length = -1;
   int num_chars = -1;

   if(strcasecmp(method, "GET") == 0)
   {
       clear_head(client);
   }
   else // POST
   {
       do
       {
           num_chars = get_line(client, buf, sizeof(buf));
           if(num_chars > 0 && strncasecmp(buf, "Content-Length: ", 16) == 0)
           {
               content_length = atoi(&buf[16]);
               //not break,just like clear head
           }
       }
       while(num_chars > 0 && strcmp(buf, "\n") != 0);

       if(content_length == -1)
       {
           print_debug("no content length", "");
           return;
       }

   }

   char echo_line[_SIZE_];
   memset(echo_line, '\0', sizeof(echo_line));
   strcat(echo_line, HTTP_VERSION);
   strcat(echo_line, " 200 OK");
   strcat(echo_line, "\r\n\r\n");

   if(send(client, echo_line, strlen(echo_line), 0) < 0)
   {
       print_log(__FUNCTION__, __LINE__, errno, strerror(errno));
       return;
   }
   print_debug("send echo head success", "");

   int cgi_input[2];
   int cgi_output[2];

   if(pipe(cgi_input) < 0)
   {
       print_log(__FUNCTION__, __LINE__, errno, strerror(errno));
       return;
   }

   if(pipe(cgi_output) < 0)
   {
       close(cgi_input[0]);
       close(cgi_input[1]);
       print_log(__FUNCTION__, __LINE__, errno, strerror(errno));
       return;
   }
   
   pid_t id = fork();
   if(id < 0)
   {
       close(cgi_input[0]);
       close(cgi_input[1]);
       close(cgi_output[0]);
       close(cgi_output[1]);
       print_log(__FUNCTION__, __LINE__, errno, strerror(errno));
       return;
   }
   else if(id == 0) //child
   {
       char method_env[_SIZE_/10];
       char query_env[_SIZE_/10];
       char content_len_env[_SIZE_/10];
       memset (method_env, '\0', sizeof(method_env));
       memset (query_env, '\0', sizeof(query_env));
       memset (content_len_env, '\0', sizeof(content_len_env));

       close(cgi_input[1]);
       close(cgi_output[0]);
       
       //redir
       dup2(cgi_input[0], 0);
       dup2(cgi_output[1], 1);

       sprintf(method_env, "REQUEST_METHOD=%s", method);
       putenv(method_env);

       if(strcasecmp(method, "GET") == 0) //GET
       {
           sprintf(query_env, "QUERY_STRING=%s", query_string);
           putenv(query_env);
       }
       else //POST
       {
           sprintf(content_len_env, "CONTENT_LENGTH=%d", content_length);
           putenv(content_len_env);
       }

       execl(path, path, NULL);
       
       close(cgi_input[0]);
       close(cgi_output[1]);
       exit(1);
   }
   else //father
   {
       close(cgi_input[0]);
       close(cgi_output[1]);

       int i = 0;
       char c = '\0';
       if(strcasecmp(method, "POST") == 0)
       {
           for(; i < content_length; ++i)
           {
               recv(client, &c, 1, 0);
               write(cgi_input[1], &c, 1); //send post data to child
           }
       }

       while(read(cgi_output[0], &c, 1) > 0)
       {
           send(client, &c, 1, 0); //read result from child
       }
       
       close(cgi_input[1]);
       close(cgi_output[0]);

       waitpid(id, NULL, 0);
   }
}

void* accept_request(void* arg)
{
    int sock_client = *(int*)arg;

    int cgi = 0;
    char* query_string = NULL;
    char buf[_SIZE_];        //to save a line
    char method[_SIZE_/10];
    char url[_SIZE_];
    char path[_SIZE_];

    memset(buf, '\0', sizeof(buf));
    memset(method, '\0', sizeof(method));
    memset(url, '\0', sizeof(url));
    memset(path, '\0', sizeof(path));

//#ifdef _DEBUG_
//    while(get_line(sock_client, buf, sizeof(buf)) > 0)
//    {
//        printf("%s", buf);
//        fflush(stdout);
//    }
//    printf("\n");
//#endif

    if(get_line(sock_client, buf, _SIZE_) < 0)
    {
        print_debug("request line get faild", "");
        return NULL;
    }

    printf("get a line : %s", buf);
    int buf_len = strlen(buf);
    //printf("line length: %d\n", buf_len);

    //get method
    int index = 0;
    int i = 0;
    while(!isspace(buf[i]) && i < buf_len && index < sizeof(method))
    {
        method[index] = buf[i];
        ++i;
        ++index;
    }
    method[index] = '\0';

    if(strcasecmp(method, "GET") && strcasecmp(method, "POST"))
    {
        return NULL;
    }

    //delete space
    while(isspace(buf[i]) && i < buf_len)
    {
        ++i;
    }

    //get url
    index = 0;
    while(!isspace(buf[i]) && i < buf_len && index < sizeof(url))
    {
        url[index] = buf[i];
        ++index;
        ++i;
    }
    url[index] = '\0';

    print_debug("method :", method);
    print_debug("url :", url);

    if(strcasecmp(method, "POST") == 0)
    {
        cgi = 1;
    }

    if(strcasecmp(method, "GET") == 0)
    {
        query_string = url;
        while(*query_string != '?' && *query_string != '\0')
        {
            ++query_string;
        }

        if(*query_string == '?')
        {
            cgi = 1;
            *query_string = '\0';
            ++query_string;
        }
    }

    sprintf(path, "htdoc%s", url);
    if(path[strlen(path)-1] == '/')
    {
        strcat(path, INDEX_PAGE);
        strcat(path, "\0");
    }
    print_debug("path :", path);
    print_debug("arg :", query_string);

    struct stat st;
    if(stat(path, &st) < 0)
    {
        print_log(__FUNCTION__, __LINE__, errno, strerror(errno));
        exit(5);
    }

    if(S_ISDIR(st.st_mode))  //is directory?
    {
        strcat(path, "/");
        strcat(path, INDEX_PAGE);
    }
    else if(st.st_mode & S_IXUSR ||\
            st.st_mode & S_IXGRP ||\
            st.st_mode & S_IXOTH)
    {
        cgi = 1;
    }
    else
    {}  //do nothing

    if(cgi)
    { 
        print_debug("begin ecectue cig ", "");
        exe_cgi(sock_client, method, path, query_string);
    }
    else
    {
        clear_head(sock_client);
        print_debug("begin echo html ", "");
        echo_html(sock_client, path, st.st_size);
    }

    close(sock_client);

    print_debug("this connection is closed", "");
    printf("========================  end  ========================\n\n");
    return NULL;
}

int startup(const char* _ip, const char* _port)
{
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock < 0)
    {
        print_log(__FUNCTION__, __LINE__, errno, strerror(errno));
        exit(1);
    }

    int opt = 1;
    if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) 
    {
        print_log(__FUNCTION__, __LINE__, errno, strerror(errno));
        exit(2);
    }  

    struct sockaddr_in local;
    local.sin_family = AF_INET;
    local.sin_port = htons(atoi(_port));
    local.sin_addr.s_addr = inet_addr(_ip);
    if(bind(sock, (struct sockaddr*)&local, sizeof(local)) < 0)
    {
        print_log(__FUNCTION__, __LINE__, errno, strerror(errno));
        exit(3);
    }

    if(listen(sock, _MAX_LISTEN_) < 0)
    {
        print_log(__FUNCTION__, __LINE__, errno, strerror(errno));
        exit(4);
    }

    return sock;
}

int main(int argc, char* argv[])
{
    if(argc != 3)
    {
        usage(argv[0]);
        return 1;
    }

    int listen_sock = startup(argv[1], argv[2]);

    struct sockaddr_in client;
    socklen_t len = sizeof(client);

    int done = 0;
    while(!done)
    {
        int new_sock = accept(listen_sock, (struct sockaddr*)&client, &len);
        if(new_sock < 0)
        {
            print_log(__FUNCTION__, __LINE__, errno, strerror(errno));
            continue;
        }
        printf("######################## begin ########################\n");
        printf("get a new connection: %d IP: %s PORT: %d\n", \
                new_sock, inet_ntoa(client.sin_addr), ntohs(client.sin_port));

        pthread_t new_thread;
        pthread_create(&new_thread, NULL, accept_request, (void*)&new_sock);
        pthread_detach(new_thread);
    }

    close(listen_sock);

    return 0;
}

//mysql_api.cpp

#include "mysql_api.h"

mysql_api::mysql_api(const std::string& _host,\
                const std::string& _user,\
                const std::string& _passwd,\
                const std::string& _db,\
                size_t _port)
    :host(_host)
    ,user(_user)
    ,passwd(_passwd)
    ,db(_db)
    ,port(_port)
{
    res = NULL;
    conn = mysql_init(NULL);
}

mysql_api::~mysql_api()
{
    conn = NULL;
    res = NULL;
    mysql_close(conn);
}

int mysql_api::my_connect()
{
    conn = mysql_real_connect(conn, host.c_str(),\
            user.c_str(), passwd.c_str(), db.c_str(), port, NULL, 0);

    int ret = -1;
    if(conn == NULL)
    {
        std::cerr<<"connect failed"<<std::endl;
    }
    else
    {
        std::cout<<"connect success"<<std::endl;
        ret = 0;
    }

    return ret;
}


int mysql_api::my_insert(const std::string& cols, const std::string& values)
{
    //INSERT INTO person_info (NAME, SEX) VALUES("laowang", "F");

    int ret = -1;
    std::string sql;
    sql = "INSERT INTO person_info ";
    sql += cols;
    sql += " VALUES ";
    sql += values;

    //std::cout<<sql.c_str()<<std::endl;
    if(mysql_query(conn, sql.c_str()) == 0)
    {
        std::cout<<"insert success"<<std::endl;
        ret = 0;
    }
    else
    {
        std::cerr<<"insert failed"<<std::endl;
    }

    return ret;
}

int mysql_api::my_delete(const std::string& which, const std::string& value) 
{
    //DELETE FROM person_info WHERE NAME="zhangsan";

    int ret = -1;
    std::string sql;
    sql = "DELETE FROM person_info WHERE ";
    sql += which;
    sql += "=\"";
    sql += value;
    sql += "\"";

    //std::cout<<sql.c_str()<<std::endl;
    if(mysql_query(conn, sql.c_str()) == 0)
    {
        std::cout<<"delete success"<<std::endl;
        ret = 0;
    }
    else
    {
        std::cerr<<"delete failed"<<std::endl;
    }

    return ret;
}

int mysql_api::my_update(const std::string& which1, const std::string& value1,\
                         const std::string& which2, const std::string& value2)
{
    // UODATE person_info set xxx=xxx WHERE xxx=xxx

    int ret = -1;
    std::string sql = "UPDATE person_info SET ";
    sql += which1;
    sql += "=\"";
    sql += value1;
    sql += "\" WHERE ";
    sql += which2;
    sql += "=\"";
    sql += value2;
    sql += "\"";

    //std::cout<<sql.c_str()<<std::endl;
    if(mysql_query(conn, sql.c_str()) == 0)
    {
        std::cout<<"update success"<<std::endl;
        ret = 0;
    }
    else
    {
        std::cerr<<"update failed"<<std::endl;
    }

    return ret;

}

int mysql_api::my_select(std::string header[],\
                         std::string data[][3],\
                         int& row_num,\
                         int& col_num)
{
    // SELECT * FROM person_info

    std::string sql = "SELECT * FROM person_info";

    //std::cout<<sql.c_str()<<std::endl;
    if(mysql_query(conn, sql.c_str()) == 0)
    {
        std::cout<<"select success"<<std::endl;
    }
    else
    {
        std::cerr<<"select failed"<<std::endl;
        return -1;
    }

    res = mysql_store_result(conn);
    if(!res)
    {
        std::cerr<<"select failed"<<std::endl;
        return -1;
    }

    int rows = mysql_num_rows(res);
    int cols = mysql_num_fields(res);
    row_num = rows;
    col_num = cols;
    //std::cout<<"rows : "<<rows<<std::endl;
    //std::cout<<"cols : "<<cols<<std::endl;

    MYSQL_FIELD* _fn = NULL;
    size_t index = 0;
    for(; _fn = mysql_fetch_field(res); )
    {
        //std::cout<<_fn->name<<"\t\t";
        header[index++] = _fn->name;
    }
    //std::cout<<std::endl;

    int i = 0;
    for(; i < rows; ++i)
    {
        MYSQL_ROW line_data = mysql_fetch_row(res);
        int j = 0;
        for(; j < cols; ++j)
        {
            //std::cout<<line_data[j]<<"\t\t";
            data[i][j] = line_data[j];
        }
        //std::cout<<std::endl;
    }

    return 0;
}


//#ifdef _DEBUG_
//int main()
//{
//    //std::cout<<"mysql_get_client_info: "<<mysql_get_client_info()<<std::endl;
//
//    mysql_api* conn = new mysql_api();
//    conn->my_connect();
//
//    //const std::string cols = "(NAME, SEX)";
//    //const std::string  values = "(\"zhaoliu\", \"F\")";
//    //const std::string  name = "zhangsan";
//    //const std::string sex = "F";
//
//    //conn->my_insert(cols, values);
//    //conn->my_delete("NAME", "laowang");
//    //conn->my_update("SEX", sex, "NAME", name);
//    //conn->my_select();
//
//    std::string header[3];
//    std::string data[1024][3];
//    int rows = -1;
//    int cols = -1;
//    conn->my_select(header, data, rows, cols);
//
//    int i = -1;
//    int j = 0;
//    for(; i < rows; ++i)
//    {
//        for(j = 0; j < cols; ++j)
//        {
//            if(i == -1)
//            {
//                std::cout<<header[j].c_str()<<"\t\t";
//            }
//            else
//            {
//                std::cout<<data[i][j].c_str()<<"\t\t";
//            }
//        }
//        std::cout<<std::endl;
//    }
//    
//
//    delete conn;
//    return 0;
//}
//#endif
//
//
//

#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql.h> 
#include <iostream>
using namespace std;

int main()
{
    const char user[] = "root";         //username
    const char pswd[] = "root";         //password
    const char host[] = "localhost";    //or"127.0.0.1"
    const char table[] = "test";        //database
    unsigned int port = 3306;           //server port        
    MYSQL myCont;
    MYSQL_RES *result;
    MYSQL_ROW sql_row;
    MYSQL_FIELD *fd;
    char column[32][32];
    int res;
    mysql_init(&myCont);
    if(mysql_real_connect(&myCont,host,user,pswd,table,port,NULL,0))
    {
        cout<<"connect succeed!"<<endl;
        mysql_query(&myCont, "SET NAMES GBK"); //设置编码格式,否则在cmd下无法显示中文
        res=mysql_query(&myCont,"select * from samples");//查询
        if(!res)
        {
            result=mysql_store_result(&myCont);//保存查询到的数据到result
            if(result)
            {
                int i,j;
                cout<<"number of result: "<<(unsigned long)mysql_num_rows(result)<<endl;
                for(i=0;fd=mysql_fetch_field(result);i++)//获取列名
                {
                    strcpy(column[i],fd->name);
                }
                j=mysql_num_fields(result);
                for(i=0;i<j;i++)
                {
                    printf("%s\t",column[i]);
                }
                printf("\n");
                while(sql_row=mysql_fetch_row(result))//获取具体的数据
                {
                    for(i=0;i<j;i++)
                    {
                        printf("%s\n",sql_row[i]);
                    }
                    printf("\n");
                }
            }
        }
        else
        {
            cout<<"query sql failed!"<<endl;
        }
    }
    else
    {
        cout<<"connect failed!"<<endl;
    }
    if(result!=NULL) mysql_free_result(result);//释放结果资源
    mysql_close(&myCont);//断开连接
    return 0;
}
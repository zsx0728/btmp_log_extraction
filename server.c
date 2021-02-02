#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <utmp.h>

int main(){
    //创建套接字
    int serv_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    //将套接字和IP、端口绑定
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));  //每个字节都用0填充
    serv_addr.sin_family = AF_INET;  //使用IPv4地址
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");  //具体的IP地址
    serv_addr.sin_port = htons(1234);  //端口
    bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

    //进入监听状态，等待用户发起请求
    listen(serv_sock, 20);

    //接收客户端请求
    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_size = sizeof(clnt_addr);
    int clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);

    //向客户端发送数据
    struct  utmp str;
    FILE    *fp_open_btmp;
    fp_open_btmp = fopen("./file.txt", "r");

    while (fread(&str, sizeof(str), 1, fp_open_btmp) > 0)
    {
    	write(clnt_sock, &str, sizeof(str));
	printf("%d      %d      %d      %s      %s\n", str.ut_tv.tv_sec, str.ut_type,
			                                str.ut_addr_v6[4], str.ut_user, str.ut_host);
    }
    fclose(fp_open_btmp);

    //关闭套接字
    close(clnt_sock);
    close(serv_sock);

    return 0;
}

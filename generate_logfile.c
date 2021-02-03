/* 如果需要分析的btmp文件路径不是/var/log/btmp，请按照如下格式自定义
 * # define _PATH_BTMP             "/root/last_tmp/btmp"
 */

#include	<stdio.h>
#include	<utmp.h>
#include	"btmp.h"

int main(void)
{
	FILE	*fp_open_btmp, *fp_write_result;
	struct	utmp buffer;
	int32_t	starttime, endtime;
	
	//输入提取数据的起始和终止时间，timestamp格式
	printf("Please input the starttime(timestamp) :");
	scanf("%d", &starttime);
	printf("Please input the endtime(timestamp) :");
	scanf("%d", &endtime);

	//调用btmp.h内函数，打印时间段内日志数据并将二进制数据写入binlog.txt文件
	generate_binlog(starttime, endtime);
	//调用btmp.h内函数，打印时间段内日志数据并将文本数据写入filelog.txt文件
	generate_filelog(starttime, endtime);
}

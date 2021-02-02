#include	<stdio.h>
#include	<utmp.h>

int main(void)
{
	FILE	*fp_open_btmp, *fp_write_result;
	struct	utmp buffer;
	int32_t	starttime, endtime;
	
	printf("Please input the starttime:");
	scanf("%d", &starttime);
	printf("Please input the endtime:");
	scanf("%d", &endtime);

	fp_open_btmp = fopen("/root/last_tmp/btmp", "r");
	fp_write_result = fopen( "./file.txt" , "w");

	printf("type	user	hostname	time	IP\n");
	while (fread(&buffer, sizeof(buffer), 1, fp_open_btmp))
	{
    		if (buffer.ut_tv.tv_sec >= starttime && buffer.ut_tv.tv_sec <= endtime)
    		{
    			printf("%d	%d	%d	%s	%s\n", buffer.ut_tv.tv_sec, buffer.ut_type, 
    				buffer.ut_addr_v6[4], buffer.ut_user, buffer.ut_host);
			//大于starttime的条目以二进制形式写入文件
			fwrite(&buffer, sizeof(buffer), 1, fp_write_result);

    		}
    		else
    			continue;
	}

	fclose(fp_open_btmp);
	fclose(fp_write_result);
}

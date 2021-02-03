
#ifndef _PATH_BTMP
# define _PATH_BTMP             "/var/log/btmp"
#endif

/* 关于utmp的结构及各部分含义，详见/usr/include/bits/utmp.h */
  
/* 根据starttime和endtime，从btmp日志中提取相应时间段的数据，并
 * 将二进制数据写入新生成的文件
 */
void	generate_binlog(int32_t starttime, int32_t endtime)
{
	FILE    *fp_open_btmp, *fp_write_result;
	struct  utmp buffer;

	fp_open_btmp = fopen( _PATH_BTMP, "r");
	fp_write_result = fopen( "./binlog.txt" , "w");

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

/* 根据starttime和endtime，从btmp日志中提取相应时间段的数据，并
 * 将文本数据写入新生成的文件
 */
void	generate_filelog(int32_t starttime, int32_t endtime)
{
	FILE    *fp_open_btmp, *fp_write_result;
	struct  utmp buffer;

	fp_open_btmp = fopen( _PATH_BTMP, "r");
	fp_write_result = fopen( "./filelog.txt" , "w");

	while (fread(&buffer, sizeof(buffer), 1, fp_open_btmp))
	{
    		if (buffer.ut_tv.tv_sec >= starttime && buffer.ut_tv.tv_sec <= endtime)
    		{
    			printf("%d	%d	%d	%s	%s\n", buffer.ut_tv.tv_sec, buffer.ut_type, 
    				buffer.ut_addr_v6[4], buffer.ut_user, buffer.ut_host);
			//大于starttime的条目以二进制形式写入文件
    			fprintf(fp_write_result, "%d	%d	%d	%s	%s\n", buffer.ut_tv.tv_sec, buffer.ut_type, 
    				buffer.ut_addr_v6[4], buffer.ut_user, buffer.ut_host);

    		}
    		else
    			continue;
	}

	fclose(fp_open_btmp);
	fclose(fp_write_result);
}

#include	<stdio.h>
#include	<utmp.h>

int main(void)
{
	FILE *fp;
	struct utmp buffer;
	
	fp = fopen("/var/log/btmp", "r");

	fread(&buffer, sizeof(buffer),1, fp);
	printf("type:%d ID:%s user:%s hostname:%s IP:%d time:%d\n", buffer.ut_type, buffer.ut_id, buffer.ut_user, 
			buffer.ut_host, buffer.ut_addr_v6[4], buffer.ut_tv.tv_sec);
	fclose(fp);
}

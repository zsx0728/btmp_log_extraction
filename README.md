# btmp_log_extraction
#### 工具作用
如果需要提取特定时间段的btmp日志，可以使用该工具。
#### 使用方法
1.确认btmp日志的路径，默认为/var/log/btmp，如不为该路径，在generate_logfile.c中自定义路径；
2.编译运行，输入timestamp格式的起止时间
```python
# gcc generate_logfile.c -o generate_logfile
# ./generate_logfile 
Please input the starttime(timestamp) :1612165251
Please input the endtime(timestamp) :1612165427
1612165251      6       0       ba      181.48.46.195
1612165292      6       0       root    v118-27-6-78.3eg2.static.cnode.io
1612165313      6       0       root    199.195.253.25
1612165383      6       0       jf      postfix11.itp.net
1612165385      6       0       jf      postfix11.itp.net
1612165401      6       0       pashm   118.25.27.67
1612165403      6       0       pashm   118.25.27.67
1612165424      6       0       db      182.254.168.205
1612165425      6       0       qe      181.48.46.195
1612165426      6       0       db      182.254.168.205
1612165427      6       0       qe      181.48.46.195
1612165251      6       0       ba      181.48.46.195
1612165292      6       0       root    v118-27-6-78.3eg2.static.cnode.io
1612165313      6       0       root    199.195.253.25
1612165383      6       0       jf      postfix11.itp.net
1612165385      6       0       jf      postfix11.itp.net
1612165401      6       0       pashm   118.25.27.67
1612165403      6       0       pashm   118.25.27.67
1612165424      6       0       db      182.254.168.205
1612165425      6       0       qe      181.48.46.195
1612165426      6       0       db      182.254.168.205
1612165427      6       0       qe      181.48.46.195
```
可以看到，由于btmp的两个函数分别都使用了printf，所以最终结果打印了两遍。
3.生成binlog.txt和filelog.txt。
```python
# cat filelog.txt 
1612165251      6       0       ba      181.48.46.195
1612165292      6       0       root    v118-27-6-78.3eg2.static.cnode.io
1612165313      6       0       root    199.195.253.25
1612165383      6       0       jf      postfix11.itp.net
1612165385      6       0       jf      postfix11.itp.net
1612165401      6       0       pashm   118.25.27.67
1612165403      6       0       pashm   118.25.27.67
1612165424      6       0       db      182.254.168.205
1612165425      6       0       qe      181.48.46.195
1612165426      6       0       db      182.254.168.205
1612165427      6       0       qe      181.48.46.195
```
binlog.txt的内容是二进制数据，跟btmp日志内容一样，filelog.txt的内容便于阅读了。第1列表示timestamp时间；第2列表示utmp结构体的类型，其中6表示登录会话，详情参考/usr/include/bits/utmp.h；第3列表示远程主机的Internet地址，我也不知道为什么总是0；第4列表示登陆用户名；第5列表示主机名。

#### 更新记录
20210201 读btmp首行内容<br>
20210202 socket网络传输btmp内容偶尔失败，需要继续测试排查 <br>
20210203 btmp内容转换为文本数据，完成v1版本。

1 查找一个网络设备
pcap_lookupdev

2 打开网络设备
pcap_create  pcap_activate  pcap_open_live

3 获取数据包
pcap_next 读取下一个包（通过调用pcap_dispatch，将cnt设置为1），并且返回一个指向包数据的u_char指针。
		这个包数据不能由调用者释放，不保证在下次调用pcap_next, pcap_next_ex, pcap_loop, pcap_dispatch
		时候包数据还有效， 如果代码需要这个包数据有效， 必须对这个包数据进行拷贝。

pcap_next_ex 这个包数据不能由调用者释放，不保证在下次调用pcap_next, pcap_next_ex, pcap_loop, pcap_dispatch
		时候包数据还有效， 如果代码需要这个包数据有效， 必须对这个包数据进行拷贝。
pcap_loop
pcap_dispatch

/*
 
 * ============================================================
 
 *       Filename:  oreo.cpp
 *    Description:  
 *         Author:  liuyoubin@baidu.com
 *        Company:  Baidu.com, Inc
 *        Created:  2015-03-24 14:59:20
 
 * ============================================================
 
 */


#include "oreo_tcp_server.h"

int main(int , char **){

	oreo::OreoTcpServer *server = new oreo::OreoTcpServer(8765);
	server->init();
	server->run();
	server->join();
	return 0;
}

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

void hello(void *req, void *res){
	char *request = (char *)req;
	char *response = (char *)res;

	sprintf(response, "hi,%s",request);
}

int main(int , char **){

	oreo::OreoTcpServer *server = new oreo::OreoTcpServer(8765);
	server->init();
	server->registerReadCallback(&hello);
	server->run();
	server->join();
	return 0;
}

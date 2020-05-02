/****************************************************/
/************* datetime Example Server **************/
/****************************************************/
#include "datetime.h"
#include <sys/time.h>

int
main( int argc , char * * argv )
{
	int listenfd , connfd;
	struct sockaddr_in servaddr;
	char buff[ MAXLINE ];
	time_t ticks;

	listenfd = socket( AF_INET , SOCK_STREAM , 0 );

	memset( &servaddr , 0 , sizeof( servaddr ) );
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl( INADDR_ANY );
	servaddr.sin_port = htons( 13 );

	bind( listenfd , (struct sockaddr *)&servaddr , sizeof( servaddr ) );
	listen( listenfd , 1024 );

	for( ; ; )
	{
		connfd = accept( listenfd , (struct sockaddr *)NULL , NULL );
		ticks = time( NULL );
		snprintf( buff , sizeof( buff ) , "%.24s\r\n" , ctime( &ticks ) );
		write( connfd , buff , strlen( buff ) );
		close( connfd );
	} 
}

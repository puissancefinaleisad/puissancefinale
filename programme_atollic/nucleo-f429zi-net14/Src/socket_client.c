/*
 * connect.c
 *
 *  Created on: 16 mai 2019
 *      Author: isabelle
 */
#include "main.h"
#include "cmsis_os.h"
#include "lwip.h"
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <inet.h>
#include <errno.h>
#include <string.h>
#define IP_SERVEUR "10.1.0.126"
#define PORT 5001
#define TAILLE_MAX 2000


//int g_socket_desc =-1;
char *message;
char *g_server_reply[TAILLE_MAX];


/*  RETURN -1 en cas d'erreur et

    RETURN=0 : si ok
*/


/*fonction qui crée un socket puis établie une connexion*/
/* return - 1 en cas d'erreur
 * Return le socket si connexion
 */

int connexion (const char *addr, int port)
{

	struct sockaddr_in server;

	//Create socket
	int socket_desc = socket(AF_INET, SOCK_STREAM, 0);
	//int ret = socket_desc;
	if (socket_desc == -1)
	{
		printf("Socket ne peut se faire - le code d'erreur est (n° %d)-%s\n",
				errno, strerror(errno));
		return -1;
	}

	server.sin_addr.s_addr = inet_addr(IP_SERVEUR);
	server.sin_family = AF_INET;   // domain AF_INET pour protocole TCP/IP
	server.sin_port = htons(PORT);

	//Connect to remote server
	int ret = connect(socket_desc, (struct sockaddr * )&server, sizeof(server));
	if (ret < 0)
	{
		printf("La connexion avec l'ip %s sur le port %d ne peut se faire - le code d'erreur est (n° %d)-%s\n",
				IP_SERVEUR, PORT, errno, strerror(errno));

		close(socket_desc);
		return -1;
	}

	printf("Connexion avec le serveur qui a l'ip %s et le port %d\n", IP_SERVEUR, PORT);

	return socket_desc;
}


/* Fonction qui envoie le message
 *return -1 si erreur et
*return le nombre d'octets si ok, on envoie le message du buffer
*/
int send_msg(int socket_desc, const char *message, int in_longueur)
{
 int ret = send(socket_desc , message , in_longueur , 0);
	if( ret< 0)
	{
		printf("Envoi échoué; le code d'erreur est (n° %d)-%s\n", errno, strerror(errno));
		return -1;
	}
	printf("Message envoyé\n");

	return ret;
}


/* fonction qui reçoit le message d'une socket
 *return -1 si erreur et
 *return le nombre d'octets si ok, on reçoit le message du buffer
 */
int receivemessage (int socket_desc, char *out_server_reply ,int in_longueur)
{


	int ret = recv(socket_desc, out_server_reply, in_longueur-1, 0); //recv: reçoit les messages d'une socket

	if(ret>=0){
		printf("Message reçu : %d, \n", ret);
		out_server_reply[ret]= '\0';
		printf("%s",out_server_reply);
	}
	else if (ret < 0)
	{
		printf("Réception échouée; le code d'erreur est (n° %d)-%s\n", errno, strerror(errno));
		return -1;
	}

	printf("Bonne réception \n");
	printf(out_server_reply);

	return ret;
}


/*
 * connect.h
 *
 *  Created on: 23 mai 2019
 *      Author: isabelle
 */
#ifndef SOCKET_SERVEUR_H_
#define SOCKET_SERVEUR_H_

#define IP_SERVEUR "10.1.0.126"
#define PORT 5001
#define KLISTEN_PORT 5002
#define IP_NUCLEO "10.1.101.101"

int connexion_tcp_server_wait(const char *, int);
extern int ssend_msg (int, const char *, int);
extern int sreceivemessage (int, char *, int);

#endif /* SOCKET_SERVEUR_H_ */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raaga <raaga@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 06:27:20 by brhajji-          #+#    #+#             */
/*   Updated: 2023/03/03 16:28:04 by raaga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define 	SERVER_HPP

# define 	MAX_USERS		10
# define 	IRCOpwd			"admin"
# define SERVER_NAME		"42IRC"

# include "irc.hpp"
# include "User.hpp"
# include "Command.hpp"
# include "Channel.hpp"

class User;
class Channel;

class Server
{
	public:
	
		Server(char *port, std::string pass);
		Server(void);
		~Server();
		Server &operator=(const Server &server);
		
		void	BuildServer();
		// void new_users();

		struct sockaddr_in	get_struct_sockaddr(void) const;
		void				sendToChan(Command cmd, User *user);
		int					get_server_socket(void) const;
		std::string			getNameServer(void) const;
		std::string			getPortNum(void) const;
		int					getRc(void) const;
		std::map<std::string, User *>	getUsers(void) const;
		void 				add_user(int server, int epoll_instance, int *num_sockets, epoll_event event);
		User				*get_user_by_fd(int fd);
		int					execute_cmd(Command cmd, User *user, struct epoll_event event, int rc, int *num_event);
		// void				join(Command cmd, User *user, std::string response);
		// void				part(Command cmd, User *user, std::string response);
		static void			signal_handler(int);
		void 				checkDeath(int *num_event);
		void 				pingAll();


		int		cap(Command cmd, User *user, struct epoll_event event, int rc, int *num_event);
		int		pass(Command cmd, User *user, struct epoll_event event, int rc, int *num_event);
		int		nick(Command cmd, User *user, struct epoll_event event, int rc, int *num_event);

		int		user(Command cmd, User *user, struct epoll_event event, int rc, int *num_event);
		int		oper(Command cmd, User *user, struct epoll_event event, int rc, int *num_event);
		int		mode(Command cmd, User *user, struct epoll_event event, int rc, int *num_event);
		int     quit(Command cmd, User *user, struct epoll_event event, int rc, int *num_event);
		int		privMsg(Command cmd, User *user, struct epoll_event event, int rc, int *num_event);
		int		join(Command cmd, User *user, struct epoll_event event, int rc, int *num_event);
		int		part(Command cmd, User *user, struct epoll_event event, int rc, int *num_event);
		int		ping(Command cmd, User *user, struct epoll_event event, int rc, int *num_event);
		int		pong(Command cmd, User *user, struct epoll_event event, int rc, int *num_event);
		//int		topic();
		//int		list();
		int		invite(Command cmd, User *user, struct epoll_event event, int rc, int *num_event);
		//int		kick();
		int		whois(Command cmd, User *user, struct epoll_event event, int rc, int *num_event);
		int		kill(Command cmd, User *user, struct epoll_event event, int rc, int *num_event);
		//int		wallops();
		int		notice(Command cmd, User *user, struct epoll_event event, int rc, int *num_event);
		//int		whois();
		
		int	executee_cmd(Command cmd, User *user, struct epoll_event event, int rc, int *num_event);
		void	bot(std::string std);
		int	bot_bool(Command cmd, User *user, struct epoll_event event, int rc, int *num_event);
		
	private:
	
		bool _tmp_fds[100];
		std::map<std::string, User *>	_users;
		std::map<std::string, Channel *> channels;
		struct sockaddr_in	_server_addr;
		int					_server_socket;
		std::string			_portNum;
		std::string			_password;
		const std::string 	_name;
		int					_rc;
};

// Commands


// int		cap(Command cmd, User user);
// int		pass(Command cmd, User user);
// int		nick(Command cmd, User user);

// int		user(Command cmd, User user);
// int		oper(Command cmd, User user);
// int		mode(Command cmd, User user);
// //int     quit();
// int		priMsg(Command cmd, User user);
// int		join(Command cmd, User user);
// int		part(Command cmd, User user);
// int		ping(Command cmd, User user);
// int		pong(Command cmd, User user);
// //int		topic();
// //int		list();
// int		invite(Command cmd, User user);
// //int		kick();
// int		whois(Command cmd, User user);
// int		kill(Command cmd, User user);
// //int		wallops();
// int		notice(Command cmd, User user);
// //int		whois();


#define 	PING	0
#define		PONG	1
#define		CAP		3
#define		PASS	4
#define		NICK	5
#define		USER	6
#define		QUIT	7
#define		PART	8
#define		JOIN	9
#define		OPER	10
#define		WHOIS	11
#define		MODE	12
#define		PRIVMSG	13
#define		NOTICE	14
#define		KILL	15


#define		RPL_WELCOME					001
#define		RPL_YOURHOST				002
#define		RPL_CREATED					003
#define		RPL_MYINFO					004
#define     RPL_ISUPPORT                005
#define     RPL_UMODEIS                 221
#define     RPL_WHOISUSER               311
#define     RPL_ENDOFWHO                315
#define     RPL_ENDOFWHOIS              318
#define     RPL_LISTSTART               321
#define     RPL_LIST                    322
#define     RPL_LISTEND                 323
#define     RPL_CHANNELMODEIS           324
#define     RPL_NOTOPIC                 331
#define     RPL_TOPIC                   332
#define     RPL_TOPICWHOTIME            333
#define     RPL_INVITING                341
#define     RPL_WHOREPLY                352
#define     RPL_NAMREPLY                353
#define     RPL_ENDOFNAMES              366
#define     RPL_BANLIST                 367
#define     RPL_ENDOFBANLIST            368
#define     RPL_YOUREOPER               381

#define     ERR_NOSUCHNICK              401
#define     ERR_NOSUCHCHANNEL           403
#define     ERR_CANNOTSENDTOCHAN        404
#define     ERR_TOOMANYCHANNELS         405
#define     ERR_TOOMANYTARGETS          407
#define     ERR_NORECIPIENT             411
#define     ERR_NOTEXTTOSEND            412
#define     ERR_UNKNOWNCOMMAND          421
#define     ERR_NONICKNAMEGIVEN         431
#define     ERR_ERRONEUSNICKNAME        432
#define     ERR_NICKNAMEINUSE           433
#define     ERR_USERNOTINCHANNEL        441
#define     ERR_NOTONCHANNEL            442
#define     ERR_USERONCHANNEL           443
#define     ERR_NEEDMOREPARAMS          461
#define     ERR_ALREADYREGISTERED       462
#define     ERR_PASSWDMISMATCH          464
#define     ERR_CHANNELISFULL           471
#define     ERR_INVITEONLYCHAN          473
#define     ERR_BANNEDFROMCHAN          474
#define     ERR_BADCHANNELKEY           475
#define     ERR_NOPRIVILEGES            481
#define     ERR_CHANOPRIVISNEEDED       482
#define     ERR_UMODEUNKNOWNFLAG        501
#define     ERR_USERSDONTMATCH          502

#endif
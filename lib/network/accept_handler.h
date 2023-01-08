#pragma once
#include <memory>
#include "lib/network/type_alias.h"

namespace cebreiro::network
{
	class Acceptor;
	class Socket;

	class AcceptHandler
	{
	public:
		virtual ~AcceptHandler() {}

		virtual void OnAccept(Acceptor& acceptor, std::shared_ptr<Socket> socket) = 0;
		virtual void OnError(Acceptor& acceptor, const error_t& error) = 0;
		virtual void UnhandledException(Acceptor& acceptor, const std::exception& exception) = 0;
	};
}
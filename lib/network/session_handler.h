#pragma once
#include "lib/network/type_alias.h"

namespace cebreiro::network
{
	class Buffer;
	class Session;

	class SessionHandler
	{
	public:
		virtual ~SessionHandler() {}

		virtual void OnSend(Session& session, Buffer& buffer) = 0;
		virtual void OnReceive(Session& session, Buffer& buffer) = 0;
		virtual void OnError(Session& session, const error_t& error) = 0;
		virtual void UnhandledException(Session& session, const std::exception& exception) = 0;
	};
}
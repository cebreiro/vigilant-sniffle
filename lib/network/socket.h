#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <span>
#include "lib/common/execution/future.h"
#include "lib/network/type_alias.h"

namespace cebreiro::network
{
	class Socket : public std::enable_shared_from_this<Socket>
	{
	public:
		explicit Socket(raw_socket_t rawSocket);
		~Socket();

		auto WriteAsync(std::span<char> buffer) -> Future<std::pair<error_t, size_t>>;
		auto ReadAsync(std::span<char> buffer) -> Future<std::pair<error_t, size_t>>;
		void Close();

		auto LocalAddress() const -> const std::string&;
		auto LocalPort() const -> uint16_t;
		auto RemoteAddress() const -> const std::string&;
		auto RemotePort() const -> uint16_t;

	private:
		raw_socket_t _rawSocket;
		strand_t _strand;

		std::string _localAddress;
		uint16_t _localPort = 0;
		std::string _remoteAddress;
		uint16_t _remotePort = 0;
	};
}
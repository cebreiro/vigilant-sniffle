#pragma once
#include <expected>
#include <boost/asio.hpp>

namespace cebreiro
{
	namespace network
	{
		namespace _asio = boost::asio;
		
		using io_context_t = _asio::io_context;
		using raw_socket_t = _asio::ip::tcp::socket;
		using raw_acceptor_t = _asio::ip::tcp::acceptor;

		using endpoint_t = _asio::ip::tcp::endpoint;

		using error_t = boost::system::error_code;
		using strand_t = _asio::strand<_asio::any_io_executor>;

		template <typename T>
		using Expected = std::expected<T, error_t>;
	}
}
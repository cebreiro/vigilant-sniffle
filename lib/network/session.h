#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <queue>
#include <mutex>
#include "lib/common/execution/future.h"
#include "lib/common/execution/thread_pool.h"
#include "lib/common/identifier_type.h"
#include "lib/network/receive_buffer.h"

namespace cebreiro::network
{
	class Decoder;
	class Encoder;

	class Socket;
	class SessionHandler;

	class Session : public std::enable_shared_from_this<Session>
	{
	public:
		using Id_t = Identifier<uint64_t, Session>;
		static constexpr size_t RECEIVE_BUFFER_MIN_SIZE = 1024;
		static constexpr size_t RECEIVE_BUFFER_MAX_SIZE = 65536;

	public:
		Session(Id_t id, 
			std::shared_ptr<Socket> socket,
			std::unique_ptr<Decoder> decoder,
			std::unique_ptr<Encoder> encoder,
			SessionHandler& handler);
		~Session();

		void StartReceive();
		void Close();

		void Send(Buffer buffer, bool encode = true);

		auto Id() const -> Id_t;
		auto LocalAddress() const -> const std::string&;
		auto LocalPort() const -> uint16_t;
		auto RemoteAddress() const -> const std::string&;
		auto RemotePort() const -> uint16_t;

	private:
		void StartSend(Buffer buffer);
		auto SendOperation() -> Future<void>;
		auto ReceiveOperation() -> Future<void>;

	private:
		Id_t _id;
		std::shared_ptr<Socket> _socket;
		std::unique_ptr<Decoder> _decoder;
		std::unique_ptr<Encoder> _encoder;
		SessionHandler& _handler;

		std::atomic<bool> _shutdown = false;

		std::atomic<bool> _receiveStarted = false;
		ReceiveBuffer _receiveBuffer;

		std::mutex _sendMutex;
		bool _sendLock = false;
		std::queue<Buffer> _sendBuffers;

		ThreadPool::Strand _strand;
	};
}
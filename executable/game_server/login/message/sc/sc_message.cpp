#include "sc_message.h"

#include "lib/common/stream/stream_writer.h"

namespace cebreiro::login
{
	SCMessage::~SCMessage()
	{
	}

	auto SCMessage::Serialize() const -> network::Buffer
	{
		constexpr size_t headSize = 2;
		constexpr size_t opcodeSize = 1;
		size_t bodySize = this->GetBodySize();

		size_t bufferSize = headSize + opcodeSize + bodySize;
		network::Buffer buffer(std::make_shared<char[]>(bufferSize), 0, bufferSize);

		StreamWriter writer(buffer.Data(), buffer.Size(), 0);

		writer.WriteUInt16(static_cast<uint16_t>(bodySize));
		writer.WriteUInt8(static_cast<uint8_t>(this->GetType()));

		this->SerializeBody(writer);

		return buffer;
	}
}

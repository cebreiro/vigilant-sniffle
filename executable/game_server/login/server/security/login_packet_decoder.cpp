#include "login_packet_decoder.h"

namespace cebreiro::login
{
	using head_type = uint16_t;

	LoginPacketDecoder::LoginPacketDecoder(uint32_t key1, uint32_t key2)
		: _keys({ key1, key2 })
	{
		if (_keys[0] >= 0x80000000)
		{
			_keys[1] = 0xFFFFFFFF;
		}
	}

	auto LoginPacketDecoder::GetPacketSize(const std::span<const char>& buffer) const
		-> std::expected<size_t, DecodeError>
	{
		if (buffer.size() < sizeof(head_type))
		{
			return std::unexpected(DecodeError::ErrorShortLength);
		}

		return *reinterpret_cast<const head_type*>(buffer.data()) + 3;
	}

	void LoginPacketDecoder::Decode(const std::span<char>& buffer)
	{
		if (_keys[0] | _keys[1])
		{
			const char* key = reinterpret_cast<const char*>(_keys.data());

			char AL = buffer[2];
			buffer[2] = buffer[2] ^ key[0];

			for (size_t i = 3; i < buffer.size(); ++i)
			{
				char BL = buffer[i] ^ (AL ^ key[(i - 2) & 7]);
				AL = buffer[i];
				buffer[i] = BL;
			}
		}

		_keys[0] += static_cast<int32_t>(buffer.size() - sizeof(head_type));

		if (_keys[0] >= 0x80000000)
		{
			_keys[1] = 0xFFFFFFFF;
		}
	}
}

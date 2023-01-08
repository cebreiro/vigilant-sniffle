#include "login_packet_encoder.h"

namespace cebreiro::login
{
	LoginPacketEncoder::LoginPacketEncoder(uint32_t key1, uint32_t key2)
		: _keys({ key1, key2 })
	{
		if (_keys[0] >= 0x80000000)
		{
			_keys[1] = 0xFFFFFFFF;
		}
	}

	void LoginPacketEncoder::Encode(const std::span<char>& buffer)
	{
		if (_keys[0] | _keys[1])
		{
			const char* key = reinterpret_cast<const char*>(_keys.data());

			if (buffer.size() < 3)
			{
				assert(false);
				return;
			}

			buffer[2] = (buffer[2] ^ key[0]);
			char CL = buffer[2];

			for (size_t i = 3; i < buffer.size(); ++i)
			{
				char BL = CL ^ (buffer[i] ^ key[(i - 2) & 7]);
				buffer[i] = BL;
				CL = buffer[i];
			}
		}

		_keys[0] += static_cast<uint32_t>(buffer.size() - sizeof(uint16_t));

		if (_keys[0] >= 0x80000000)
		{
			_keys[1] = 0xFFFFFFFF;
		}
	}
}

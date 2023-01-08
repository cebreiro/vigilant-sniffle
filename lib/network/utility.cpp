#include "utility.h"

#include <WinSock2.h>
#include <ws2tcpip.h>

namespace cebreiro::network
{
	auto AddressToBinaryForm(std::string_view address) -> int32_t
	{
		SOCKADDR_IN sa = {};
		if (!::inet_pton(AF_INET, address.data(), &sa.sin_addr.s_addr))
		{
			return -1;
		}

		return sa.sin_addr.s_addr;
	}
}

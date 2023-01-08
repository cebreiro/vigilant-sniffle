#include "login_request.h"

#include <boost/algorithm/string.hpp>
#include "lib/common/stream/stream_reader.h"

namespace cebreiro::login
{
	void LoginRequest::Deserialize(StreamReader& reader)
	{
		account = reader.ReadString(14);
		password = reader.ReadString(16);

		auto isSpace = [](char c) {return c == '\0'; };
		boost::algorithm::trim_right_if(account, isSpace);
		boost::algorithm::trim_right_if(password, isSpace);
	}
}

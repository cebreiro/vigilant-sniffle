#include "duplicate_login.h"

#include "lib/common/stream/stream_reader.h"
#include "lib/common/stream/stream_writer.h"

namespace cebreiro
{
	DuplicateLogin::DuplicateLogin(int64_t accountId)
		: accountId(accountId)
	{
	}

	void DuplicateLogin::Deserialize(StreamReader& reader)
	{
		accountId = reader.ReadInt64();
	}

	void DuplicateLogin::Serialize(StreamWriter& writer) const
	{
		writer.WriteInt64(accountId);
	}

	auto DuplicateLogin::Type() const -> LoginServiceEventType
	{
		return LoginServiceEventType::DuplicateLogin;
	}
}

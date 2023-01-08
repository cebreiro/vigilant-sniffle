#pragma once
#include "login/message/sc/sc_message.h"

namespace cebreiro::login
{
	enum class LoginFailReason : int32_t
	{
		CantConnectServer = 1,
		InvalidIDPassword = 2,
		ReleaseExistingConnection = 7,
		AgeRestriction = 12,
		TooMuchUser = 15,
		NotPaidAccount = 18,
	};

	class LoginFailResponse : public SCMessage
	{
	public:
		explicit LoginFailResponse(LoginFailReason reason);

	private:
		auto GetType() const -> SCMessageType override;
		auto GetBodySize() const -> size_t override;
		void SerializeBody(StreamWriter& writer) const override;

	private:
		LoginFailReason _reason;
	};
}
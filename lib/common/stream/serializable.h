#pragma once

namespace cebreiro
{
	class StreamWriter;

	class ISerializable
	{
	public:
		virtual ~ISerializable() = default;

		virtual void Serialize(StreamWriter& writer) const = 0;
	};

}

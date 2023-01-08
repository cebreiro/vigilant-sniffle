#pragma once

namespace cebreiro
{
	class StreamReader;

	class IDeserializable
	{
	public:
		virtual ~IDeserializable() = default;

		virtual void Deserialize(StreamReader& reader) = 0;
	};
}

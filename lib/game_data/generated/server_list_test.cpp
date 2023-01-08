/**********************************************************
         AUTO GENERATED FILE BY sox_code_generator
                   DO NOT EDIT THIS FILE
**********************************************************/
#include "server_list_test.h"

#include "lib/common/stream/stream_reader.h"
#include "lib/game_base/data/sox/sox_file.h"
#include "lib/game_data/game_data_registry.h"

namespace cebreiro::gamedata
{
	[[maybe_unused]]
	static GameDataRegistry<ServerListTestTable> registry;

	ServerListTest::ServerListTest(StreamReader& reader)
	{
		index = reader.ReadInt32();
		name = reader.ReadString(reader.ReadUInt16());
		desc = reader.ReadString(reader.ReadUInt16());
		ip = reader.ReadString(reader.ReadUInt16());
	}

	void ServerListTestTable::LoadFromFile(const std::filesystem::path& path)
	{
		gamebase::SoxFile fileData(path / "SERVER_LIST_TEST.sox");
		StreamReader reader(fileData.gameData.data(), fileData.gameData.size());

		_vector.reserve(fileData.rowCount);
		for (int32_t i = 0; i < fileData.rowCount; ++i)
		{
			_vector.emplace_back(reader);
		}

		for (const ServerListTest& data : _vector)
		{
			_umap[data.index] = &data;
		}
	}

	auto ServerListTestTable::Find(int32_t index) const -> const ServerListTest*
	{
		auto iter = _umap.find(index);
		return iter != _umap.end() ? iter->second : nullptr;
	}

	auto ServerListTestTable::Get() const -> const std::vector<ServerListTest>&
	{
		return _vector;
	}
}
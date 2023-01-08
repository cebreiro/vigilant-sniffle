#include "game_server.h"

int main(int argc, char* argv[])
{
	using cebreiro::GameServer;

	return GameServer{}.Run(std::span(argv, argc));
}
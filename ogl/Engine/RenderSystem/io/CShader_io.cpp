#include "io/io.h"
#include "Shader.h"
#include "Types.h"
#include "Logger\Logger.h"

#include <flatbuffers/idl.h>
#include <flatbuffers/util.h>

#include "monster_generated.h" // Already includes "flatbuffers/flatbuffers.h".

namespace iris { namespace io {

	template <> bool Serialize(const CShader& aObject)
	{
		// load FlatBuffer schema (.fbs) and JSON from disk
		std::string schemafile;
		std::string jsonfile;
		bool ok = flatbuffers::LoadFile("../data/shaders/monster.fbs", false, &schemafile) &&
			flatbuffers::LoadFile("../data/shaders/monsterdata.json", false, &jsonfile);
		if (!ok) {
			printf("couldn't load files!\n");
			return 1;
		}

		// parse schema first, so we can use it to parse the data after
		flatbuffers::Parser parser;
		const char *include_directories[] = { "../data/shaders/", nullptr };
		ok = parser.Parse(schemafile.c_str(), include_directories) &&
			parser.Parse(jsonfile.c_str(), include_directories);
		assert(ok);

		auto monster = MyGame::Sample::GetMonster(parser.builder_.GetBufferPointer());

		IRIS_LOG_APPLICATION(monster->name()->c_str());

		printf("%d\n", monster->hp());            // `80`
		printf("%d\n", monster->mana());          // default value of `150`
		printf("%s\n", monster->name()->c_str()); // "MyMonster"

		// here, parser.builder_ contains a binary buffer that is the parsed data.
        /*
		// to ensure it is correct, we now generate text back from the binary,
		// and compare the two:
		std::string jsongen;
		GenerateText(parser, parser.builder_.GetBufferPointer(), &jsongen);

		if (jsongen != jsonfile) {
			printf("%s----------------\n%s", jsongen.c_str(), jsonfile.c_str());
		}*/

		printf("The FlatBuffer has been parsed from JSON successfully.\n");
		return true;
	}

	template <> bool Unserialize(CShader& aObject)
	{
		return true;
	}
}}
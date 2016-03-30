#include "io.h"

#include "Logger/Logger.h"

#include <flatbuffers/idl.h>
#include <flatbuffers/util.h>
#include <flatbuffers/flatbuffers.h>

#include <stdio.h>
#include <cstdio>

using namespace flatbuffers;

namespace iris
{
    namespace io
    {
        bool GetBufferPtr(const CResource& aResource, uint8*& aBufferPtr)
        {
            aBufferPtr = nullptr;

            bool lOk = true;

            /* // Read a json
            Parser parser;
            const char *include_directories[] = { aResource.GetDirectory().c_str(), nullptr };
            std::string lFBS, lJson;

            // load FlatBuffer schema (.fbs) and JSON from disk
            lOk = LoadFile(aResource.GetFullFilenameSchema().c_str(), false, &lFBS) && LoadFile(aResource.GetFullFilename().c_str(), false, &lJson);

            // parse schema first, so we can use it to parse the data after
            lOk &= parser.Parse(lFBS.c_str(), include_directories) && parser.Parse(lJson.c_str(), include_directories);

            LOG_ERROR_IF(!lOk, "Error parsing file %s \n %s", aResource.GetFullFilename().c_str(), parser.error_.c_str());

            uint32 lSize = parser.builder_.GetSize();
            aBufferPtr = (uint8*)malloc(lSize);
            memcpy(aBufferPtr, parser.builder_.GetBufferPointer(), lSize);

            */

            // Read from a binary file
            FILE* file = fopen (aResource.GetFullFilename().c_str(), "rb" );
            fseek(file, 0L, SEEK_END);
            int length = ftell(file);
            fseek(file, 0L, SEEK_SET);
            aBufferPtr = new uint8[length];
            fread(aBufferPtr, sizeof(uint8), length, file);
            fclose(file);

            return lOk;
        }
    }
}
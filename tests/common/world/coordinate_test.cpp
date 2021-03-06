#include <catch2/catch.hpp>
#include <common/world/coordinate.h>
#include <common/world/world_constants.h>

TEST_CASE("Coordinate systems can be correctly converted between")
{
    SECTION("Block positions can be correctly converted to chunk positions")
    {
        BlockPosition position;
        ChunkPosition converted;

        position = {0, 0, 0};
        converted = {0, 0, 0};
        REQUIRE(toChunkPosition(position) == converted);

        position = {CHUNK_SIZE, CHUNK_SIZE, CHUNK_SIZE};
        converted = {1, 1, 1};
        REQUIRE(toChunkPosition(position) == converted);

        position = {-1, CHUNK_SIZE, CHUNK_SIZE};
        converted = {-1, 1, 1};
        REQUIRE(toChunkPosition(position) == converted);

        position = {-1, -CHUNK_SIZE * 2 + 5, CHUNK_SIZE};
        converted = {-1, -2, 1};
        REQUIRE(toChunkPosition(position) == converted);
    }

    SECTION("Block positions can be correctly converted to an array index")
    {
        BlockPosition position;
        int converted;

        position = {0, 0, 0};
        converted = 0;
        REQUIRE(toLocalBlockIndex(position) == converted);
    }

    SECTION("Block positions can be converted to local block postions")
    {
        BlockPosition position;
        BlockPosition converted;

        position = {0, 0, 0};
        converted = {0, 0, 0};
        REQUIRE(toLocalBlockPosition(position) == converted);

        position = {CHUNK_SIZE, CHUNK_SIZE, CHUNK_SIZE};
        converted = {0, 0, 0};
        REQUIRE(toLocalBlockPosition(position) == converted);

        position = {CHUNK_SIZE + 10, CHUNK_SIZE - 1, CHUNK_SIZE};
        converted = {10, CHUNK_SIZE - 1, 0};
        REQUIRE(toLocalBlockPosition(position) == converted);

        position = {-1, 0, 0};
        converted = {CHUNK_SIZE - 1, 0, 0};
        REQUIRE(toLocalBlockPosition(position) == converted);
    }

    SECTION("World positions can be converted to chunk positions")
    {
        {
            ChunkPosition position(5, 6, 2);
            glm::vec3 worldPosition({CHUNK_SIZE * position.x, CHUNK_SIZE * position.y,
                                     CHUNK_SIZE * position.z});

            REQUIRE(worldToChunkPosition(worldPosition) == position);
        }
        {
            ChunkPosition position(-5, -6, -2);
            glm::vec3 worldPosition({CHUNK_SIZE * position.x, CHUNK_SIZE * position.y,
                                     CHUNK_SIZE * position.z});

            REQUIRE(worldToChunkPosition(worldPosition).x + 1 == position.x);
            REQUIRE(worldToChunkPosition(worldPosition).y + 1 == position.y);
            REQUIRE(worldToChunkPosition(worldPosition).z + 1 == position.z);
        }
        {
            ChunkPosition position(-5, 60, -2);
            glm::vec3 worldPosition({CHUNK_SIZE * position.x, CHUNK_SIZE * position.y,
                                     CHUNK_SIZE * position.z});

            REQUIRE(worldToChunkPosition(worldPosition).x + 1 == position.x);
            REQUIRE(worldToChunkPosition(worldPosition).y == position.y);
            REQUIRE(worldToChunkPosition(worldPosition).z + 1 == position.z);
        }
    }

    SECTION("World positions can be converted to global block positions")
    {
        {
            float x = 10;
            float y = 23212;
            float z = 1322;

            glm::vec3 worldPosition(x, y, z);

            REQUIRE(toBlockPosition(worldPosition).x == static_cast<i32>(x));
            REQUIRE(toBlockPosition(worldPosition).y == static_cast<i32>(y));
            REQUIRE(toBlockPosition(worldPosition).z == static_cast<i32>(z));
        }
        {
            float x = -10;
            float y = -23212;
            float z = -1322;

            glm::vec3 worldPosition(x, y, z);

            REQUIRE(toBlockPosition(worldPosition).x == static_cast<i32>(x));
            REQUIRE(toBlockPosition(worldPosition).y == static_cast<i32>(y));
            REQUIRE(toBlockPosition(worldPosition).z == static_cast<i32>(z));
        }
        {
            float x = -10465;
            float y = 422;
            float z = 13222;

            glm::vec3 worldPosition(x, y, z);

            REQUIRE(toBlockPosition(worldPosition).x == static_cast<i32>(x));
            REQUIRE(toBlockPosition(worldPosition).y == static_cast<i32>(y));
            REQUIRE(toBlockPosition(worldPosition).z == static_cast<i32>(z));
        }
    }
}
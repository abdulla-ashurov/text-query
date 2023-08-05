#include "catch_amalgamated.hpp"
#include "../include/text-query.hpp"
#include "../include/query.hpp"

////////////////////////////////////////////////////////////////
////////////////////// Test Query class ////////////////////////
////////////////////////////////////////////////////////////////

TEST_CASE("Test Query class") {
    TextQuery text_query("test/payloads/input.txt");
    SECTION("Test word query") {
        Query query("lorem");
        std::vector<size_t> expected_lines = {5, 8};

        std::vector<size_t> lines = query.run(text_query);
        REQUIRE(lines == expected_lines);
    }

    SECTION("Test not word query") {
        Query query = ~Query("lorem");
        std::vector<size_t> expected_lines = {1, 2, 3, 4, 6, 7, 9};

        std::vector<size_t> lines = query.run(text_query);
        REQUIRE(lines == expected_lines);
    }

    SECTION("Test OR query") {
        Query query = Query("lorem") | Query("ipsum");
        std::vector<size_t> expected_lines = {5, 8, 0, 7};

        std::vector<size_t> lines = query.run(text_query);
        REQUIRE(lines == expected_lines);
    }

    SECTION("Test AND query") {
        Query query = Query("ipsum") & Query("amet");
        std::vector<size_t> expected_lines = {0, 7};

        std::vector<size_t> lines = query.run(text_query);
        REQUIRE(lines == expected_lines);
    }

    SECTION("Test AND & OR queries") {
        Query query = Query("amet") & (Query("lorem") | Query("ipsum"));
        std::vector<size_t> expected_lines = {0, 7};

        std::vector<size_t> lines = query.run(text_query);
        REQUIRE(lines == expected_lines);
    }

    SECTION("Test AND & OR queries") {
        Query query = (Query("ipsum") & (Query("amet"))) | Query("sit");
        std::vector<size_t> expected_lines = {0, 7};

        std::vector<size_t> lines = query.run(text_query);
        REQUIRE(lines == expected_lines);
    }
}

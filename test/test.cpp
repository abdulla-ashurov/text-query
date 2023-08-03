#include "catch_amalgamated.hpp"
#include "../include/text-query.hpp"
#include "../include/query.hpp"

TEST_CASE("Test TextQuery class") {
    SECTION("[Positive] Test query method") {
        TextQuery text_query;
        text_query.read_file("test/payloads/input.txt");
        std::vector<size_t> expected_lines = {5, 8};

        std::vector<size_t> lines = text_query.query("lorem"); // 0, 5, 8
        REQUIRE(lines == expected_lines);
    }

    SECTION("[Negative] Test query method") {
        TextQuery text_query;
        text_query.read_file("test/payloads/input.txt");

        std::vector<size_t> lines = text_query.query("notExistentWord");
        REQUIRE(lines.size() == 0);
    }
}

////////////////////////////////////////////////////////////////
////////////////////// Test Query class ////////////////////////
////////////////////////////////////////////////////////////////

TEST_CASE("Test Query class") {
    SECTION("Test word query") {
        Query query("lorem");
        query.run();

        // expected result assert
    }

    SECTION("Test not word query") {
        Query query = ~Query("lorem");
        query.run();

        // expected result assert
    }

    SECTION("Test OR query") {
        Query query = Query("lorem") | Query("ipsum");
        query.run();

        // expected result assert
    }

    SECTION("Test AND query") {
        Query query = Query("lorem") & Query("ipsum");
        query.run();

        // expected result assert
    }

    SECTION("Test AND & OR queries") {
        Query query = Query("lorem") & (Query("xyz") | Query("zyx"));
        query.run();

        // expected result assert
    }

    SECTION("Test AND & OR queries") {
        Query query = (Query("lorem") & (Query("xyz"))) | Query("zyx");
        query.run();

        // expected result assert
    }
}

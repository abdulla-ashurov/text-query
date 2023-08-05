#include "catch_amalgamated.hpp"
#include "../include/text-query.hpp"
#include "../include/query.hpp"

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

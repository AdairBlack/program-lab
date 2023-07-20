#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <memory>
#include <iomanip>

#include "../JsonAnalyzer/JsonAnalyzer.h"
#include "../JsonAnalyzer/JsonNode.h"
#include "../JsonAnalyzer/JsonContent.h"

using namespace std;

static int mainRet = 0;
static int testCount = 0;
static int testPass = 0;

#define EXPECT_EQ_BASE(equality, expect, actual, format) \
    do {\
        testCount++;\
        if (equality)\
            testPass++;\
        else {\
            fprintf(stderr, "%s:%d: expect: " format " actual: " format "\n", __FILE__, __LINE__, expect, actual);\
            mainRet = 1;\
        }\
    } while(0)

#define EXPECT_EQ_INT(expect, actual) EXPECT_EQ_BASE((expect) == (actual), expect, actual, "%d")
#define EXPECT_EQ_DOUBLE(expect, actual) EXPECT_EQ_BASE((expect) == (actual), expect, actual, "%.17g")

#define TEST_UNARY(expectRet, expectType, json)\
do{\
    JsonAnalyzer jsonAnalyzer;\
    JsonNode jsonNode;\
    jsonNode.jsonType = JSON_NULL;\
    EXPECT_EQ_INT(expectRet, jsonAnalyzer.jsonParse(jsonNode, json));\
    EXPECT_EQ_INT(expectType, jsonNode.jsonType);\
}while(0)

#define TEST_NUMBER(expect, json)\
do{\
    JsonAnalyzer jsonAnalyzer;\
    JsonNode jsonNode;\
    EXPECT_EQ_INT(JSON_PARSE_OK, jsonAnalyzer.jsonParse(jsonNode, json));\
    EXPECT_EQ_INT(JSON_NUMBER, jsonNode.jsonType);\
    EXPECT_EQ_DOUBLE(expect, jsonNode.getNumber());\
}while(0)

static void testParseExpectValue()
{
    cout << "Test parse expect value" << endl;
    TEST_UNARY(JSON_PARSE_EXPECT_VALUE, JSON_NULL, "");
    TEST_UNARY(JSON_PARSE_EXPECT_VALUE, JSON_NULL, " ");
    
    return;
}

static void testParseInvalidValue()
{
    cout << "Test parse invalid value" << endl;
    TEST_UNARY(JSON_PARSE_INVALID_VALUE, JSON_NULL, "nul");
    TEST_UNARY(JSON_PARSE_INVALID_VALUE, JSON_NULL, "?");

    TEST_UNARY(JSON_PARSE_INVALID_VALUE, JSON_NULL, "+0");
    TEST_UNARY(JSON_PARSE_INVALID_VALUE, JSON_NULL, "+1");
    TEST_UNARY(JSON_PARSE_INVALID_VALUE, JSON_NULL, ".123");
    TEST_UNARY(JSON_PARSE_INVALID_VALUE, JSON_NULL, "1.");
    TEST_UNARY(JSON_PARSE_INVALID_VALUE, JSON_NULL, "INF");
    TEST_UNARY(JSON_PARSE_INVALID_VALUE, JSON_NULL, "inf");
    TEST_UNARY(JSON_PARSE_INVALID_VALUE, JSON_NULL, "NAN");
    TEST_UNARY(JSON_PARSE_INVALID_VALUE, JSON_NULL, "nan");

    return;
}

static void testParseRootNotSingular()
{
    cout << "Test parse root not singular" << endl;
    TEST_UNARY(JSON_PARSE_ROOT_NOT_SINGULAR, JSON_NULL, "null x");

    return;
}

static void testParseNull()
{
    cout << "Test parse null" << endl;
    TEST_UNARY(JSON_PARSE_OK, JSON_NULL, "null");

    return;
}

static void testParseTrue()
{
    cout << "Test parse expect true" << endl;
    TEST_UNARY(JSON_PARSE_OK, JSON_TRUE, "true");

    return;
}

static void testParseFalse()
{
    cout << "Test parse expect false" << endl;
    TEST_UNARY(JSON_PARSE_OK, JSON_FALSE, "false");

    return;
}

static void testParseNumber()
{
    cout << "Test parse number" << endl;
    TEST_NUMBER(0.0, "0");
    TEST_NUMBER(0.0, "-0");
    TEST_NUMBER(0.0, "-0.0");
    TEST_NUMBER(1.0, "1");
    TEST_NUMBER(-1.0, "-1");
    TEST_NUMBER(1.5, "1.5");
    TEST_NUMBER(-1.5, "-1.5");
    TEST_NUMBER(3.1416, "3.1416");
    TEST_NUMBER(1E10, "1E10");
    TEST_NUMBER(1e10, "1e10");
    TEST_NUMBER(1E+10, "1E+10");
    TEST_NUMBER(1E-10, "1E-10");
    TEST_NUMBER(-1E10, "-1E10");
    TEST_NUMBER(-1e10, "-1e10");
    TEST_NUMBER(-1E+10, "-1E+10");
    TEST_NUMBER(-1E-10, "-1E-10");
    TEST_NUMBER(1.234E+10, "1.234E+10");
    TEST_NUMBER(1.234E-10, "1.234E-10");
    TEST_NUMBER(0.0, "1e-10000");

    TEST_NUMBER(1.0000000000000002, "1.0000000000000002");           /* the smallest number > 1 */
    TEST_NUMBER(4.9406564584124654e-324, "4.9406564584124654e-324"); /* minimum denormal */
    TEST_NUMBER(-4.9406564584124654e-324, "-4.9406564584124654e-324");
    TEST_NUMBER(2.2250738585072009e-308, "2.2250738585072009e-308"); /* Max subnormal double */
    TEST_NUMBER(-2.2250738585072009e-308, "-2.2250738585072009e-308");
    TEST_NUMBER(2.2250738585072014e-308, "2.2250738585072014e-308"); /* Min normal positive double */
    TEST_NUMBER(-2.2250738585072014e-308, "-2.2250738585072014e-308");
    TEST_NUMBER(1.7976931348623157e+308, "1.7976931348623157e+308"); /* Max double */
    TEST_NUMBER(-1.7976931348623157e+308, "-1.7976931348623157e+308");

    return ;
}

static void testParseString()
{
    
}



static void testParse()
{
    testParseExpectValue();
    testParseInvalidValue();
    testParseRootNotSingular();
    testParseNull();
    testParseTrue();
    testParseFalse();
    testParseNumber();
    
    return;
}

int main()
{
    cout << "*****************Edgar's JsonAnalyzer Test*****************" << endl;
    testParse();

    cout << testPass << "/" << testCount << " (" << fixed << setprecision(2)\
    << testPass * 100.0 / testCount << ") passed." << endl;

    return mainRet;
}

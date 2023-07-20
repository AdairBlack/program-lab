#ifndef JSON_ANALYZER_H__
#define JSON_ANALYZER_H__

#include "JsonNode.h"
#include "JsonContent.h"

#define EXPECT(json, ch) do{assert(*json == (ch));json++;} while(0);

#define ISDIGIT(ch)          ((ch) >= '0' && (ch) <= '9')
#define ISDIGIT1TO9(ch)      ((ch) >= '1' && (ch) <= '9')

#define FORWARD_POINTER(p)   for(p++; ISDIGIT(*p); p++);

enum {
    JSON_PARSE_OK = 0,
    JSON_PARSE_EXPECT_VALUE,
    JSON_PARSE_INVALID_VALUE,
    JSON_PARSE_ROOT_NOT_SINGULAR,
    JSON_PARSE_NUMBER_TOO_BIG
};

class JsonAnalyzer
{
private:
    void jsonParseWhitespace(JsonContent &jsonContent);
    int jsonParseLiteral(JsonContent &jsonContent, JsonNode &jsonNode, const char *literal, JsonType jsonType);
    int jsonParseNumber(JsonContent &jsonContent, JsonNode &jsonNode);
    int jsonParseString(JsonContent &jsonContent, JsonNode &jsonNode);
    int jsonParseValue(JsonContent &jsonContent, JsonNode &jsonNode);
public:
    int jsonParse(JsonNode &jsonNode, const char *json);
    JsonAnalyzer() = default;
    ~JsonAnalyzer() = default;
};

#endif
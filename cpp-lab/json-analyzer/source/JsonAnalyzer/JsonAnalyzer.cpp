#include <cassert>
#include <iostream>
#include <cerrno>
#include <cmath>
#include <cstring>

#include "JsonAnalyzer.h"
#include "JsonNode.h"


using namespace std;

void JsonAnalyzer::jsonParseWhitespace(JsonContent &jsonContent)
{
    
    const char *p = jsonContent.content;
    while (*p == ' ' || *p == '\t' || *p == '\n' || *p == '\r')
    {
        p++;
    }
    jsonContent.content = p;
    return;
}

int JsonAnalyzer::jsonParseLiteral(JsonContent &jsonContent, JsonNode &jsonNode, const char *literal, JsonType jsonType)
{
    size_t i;
    EXPECT(jsonContent.content, literal[0]);

    for(i = 0; literal[i + 1] ; i++)
    {
        if(jsonContent.content[i] != literal[i + 1])
        {
            return JSON_PARSE_INVALID_VALUE;
        }
    }
    jsonContent.content += i;
    jsonNode.jsonType = jsonType;
    return JSON_PARSE_OK;
}

int JsonAnalyzer::jsonParseNumber(JsonContent &jsonContent, JsonNode &jsonNode)
{
    const char* p = jsonContent.content;
    if('-' == *p)
    {
        p++;
    }

    if('0' == *p)
    {
        p++;
    } else {
        if(!ISDIGIT1TO9(*p)) 
        {
            return JSON_PARSE_INVALID_VALUE;
        }
        FORWARD_POINTER(p);
    }

    if(*p == '.')
    {
        p++;
        if(!ISDIGIT(*p))
        {
            return JSON_PARSE_INVALID_VALUE;
        }
        FORWARD_POINTER(p);
    }

    if('e' == *p || 'E' == *p)
    {
        p++;
        if('+' == *p || '-' == *p)
        {
            p++;
        }
        if(!ISDIGIT(*p))
        {
            return JSON_PARSE_INVALID_VALUE;
        }
        FORWARD_POINTER(p);
    }

    errno = 0;
    jsonNode.number = strtod(jsonContent.content, NULL);

    if(ERANGE == errno && (HUGE_VAL == jsonNode.number || -HUGE_VAL == jsonNode.number))
    {
        return JSON_PARSE_NUMBER_TOO_BIG;
    }

    jsonNode.jsonType = JSON_NUMBER;
    jsonContent.content = p;

    return JSON_PARSE_OK;
}

int JsonAnalyzer::jsonParseString(JsonContent &jsonContent, JsonNode &jsonNode)
{
    string tempString = jsonContent.content;
    
    return 0;
}

int JsonAnalyzer::jsonParseValue(JsonContent &jsonContent, JsonNode &jsonNode)
{
    switch(*jsonContent.content)
    {
        case 'n': return jsonParseLiteral(jsonContent, jsonNode, "null", JSON_NULL);
        case 't': return jsonParseLiteral(jsonContent, jsonNode, "true", JSON_TRUE);
        case 'f': return jsonParseLiteral(jsonContent, jsonNode, "false", JSON_FALSE);
        case '"': return jsonParseString(jsonContent, jsonNode);
        case '\0': return JSON_PARSE_EXPECT_VALUE;
        default: return jsonParseNumber(jsonContent, jsonNode);
    }
}

int JsonAnalyzer::jsonParse(JsonNode &jsonNode, const char *json)
{
    assert(nullptr != json);
    int ret = JSON_PARSE_OK;
    jsonNode.jsonType = JSON_NULL;
    JsonContent jsonContent;
    jsonContent.content = json;
    jsonParseWhitespace(jsonContent);
    if(JSON_PARSE_OK == (ret = jsonParseValue(jsonContent, jsonNode)))
    {
        jsonParseWhitespace(jsonContent);
        if(*jsonContent.content != '\0')
        {
            ret = JSON_PARSE_ROOT_NOT_SINGULAR;
        }
    }
    return ret;
}
#include <assert.h>
#include <memory> 
#include <string.h>

#include "JsonNode.h"



JsonNode::~JsonNode()
{
    if(JSON_STRING == jsonType)
    {
        delete stringVal;
    }
}

double JsonNode::getNumber()
{
    assert(JSON_NUMBER == jsonType);
    return number;
}

void JsonNode::setString(const char *stringVal, size_t stringLen)
{
    assert(nullptr != stringVal && 0 != stringLen);

    if(nullptr != this->stringVal)
    {
        delete this->stringVal;
        this->stringLen = 0;
    }

    this->stringVal = new char[stringLen + 1];
    memcpy(this->stringVal, stringVal, stringLen);
    this->stringVal[stringLen] = 0;
    this->stringLen = stringLen;
    this->jsonType = JSON_STRING;

    return ;
}

char *JsonNode::getString()
{
    assert(JSON_STRING == jsonType);
    return stringVal;
}


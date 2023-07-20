#ifndef JSON_NODE_H__
#define JSON_NODE_H__

#include <string>

typedef enum
{
    JSON_NULL,
    JSON_FALSE,
    JSON_TRUE,
    JSON_NUMBER,
    JSON_STRING,
    JSON_ARRAY,
    JSON_OBJECT
} JsonType;

class JsonNode
{
private:
    
public:
    JsonNode() = default;
    ~JsonNode();

    JsonType jsonType;

    /*Number*/
    double number;
    double getNumber();

    /*String*/
    char *stringVal;
    size_t stringLen;
    void setString(const char *stringVal, size_t stringLen);
    char *getString();

};

#endif
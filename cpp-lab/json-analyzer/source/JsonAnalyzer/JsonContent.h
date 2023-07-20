#ifndef JSON_CONTENT_H__
#define JSON_CONTENT_H__

class JsonContent
{
private:
public:
    JsonContent() = default;
    ~JsonContent() = default;

    const char *content;
    char *stack;
    size_t size, top;
};

#endif
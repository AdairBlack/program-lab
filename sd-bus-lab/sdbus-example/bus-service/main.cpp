#include <fmt/core.h>
#include <systemd/sd-bus.h>
#include <algorithm>
#include <vector>
class sdbus
{
public:
    sd_bus_slot *slot{nullptr};
    sd_bus *bus{nullptr};
    ~sdbus()
    {
        sd_bus_slot_unref(slot);
        sd_bus_unref(bus);
        fmt::print("release resource\n");
    }
};

// userdata
struct SharedData {
  int someValue;
  // Add other shared data here
};

int reverse(sd_bus_message *message, void *userdata, sd_bus_error *ret_error)
{
    char *data;
    if (int r = sd_bus_message_read(message, "s", &data); r < 0)
    {
        fmt::print("fail to parse parameter {}\n", strerror(-r));
        return r;
    }
    std::string s(data);
    std::reverse(std::begin(s), std::end(s));
    return sd_bus_reply_method_return(message, "s", s.data());
}

int echo(sd_bus_message *message, void *userdata, sd_bus_error *ret_error)
{
    char *data;
    SharedData* sharedData = static_cast<SharedData*>(userdata);
    if (int r = sd_bus_message_read(message, "s", &data); r < 0)
    {
        fmt::print("fail to parse parameter {}\n", strerror(-r));
        return r;
    }
    return sd_bus_reply_method_return(message, "si", data, sharedData->someValue);
}

int main()
{
    sdbus sd;
    SharedData sharedData;
    sharedData.someValue = 42;

    if (int r = sd_bus_open_user(&sd.bus); r < 0)
    {
        fmt::print("fail to connect to system bus {}\n", strerror(-r));
        exit(-1);
    }
    const sd_bus_vtable vtable[] = {
        SD_BUS_VTABLE_START(0),
        SD_BUS_METHOD("Reverse", "s", "s", reverse, SD_BUS_VTABLE_UNPRIVILEGED),
        SD_BUS_METHOD("Echo", "s", "si", echo, SD_BUS_VTABLE_UNPRIVILEGED),
        SD_BUS_VTABLE_END};
    if (int r = sd_bus_add_object_vtable(sd.bus, &sd.slot, "/net/basic/Plain",
                                         "net.basic.Plain", vtable, &sharedData);
        r < 0)
    {
        fmt::print("fail to issue method call {}\n", strerror(-r));
        exit(-1);
    }
    if (int r = sd_bus_request_name(sd.bus, "net.basic.Plain", 0); r < 0)
    {
        fmt::print("fail to acquire service name {}\n", strerror(-r));
        exit(-1);
    }
    while (true)
    {
        if (int r = sd_bus_process(sd.bus, NULL); r < 0)
        {
            fmt::print("fail to process bus {}\n", strerror(-r));
            exit(-1);
        }
        else if (r > 0)
        {
            continue;
        }
        if (int r = sd_bus_wait(sd.bus, (uint64_t)-1); r < 0)
        {
            fmt::print("fail to wait on bus {}\n", strerror(-r));
            exit(-1);
        }
    }
    return 0;
}
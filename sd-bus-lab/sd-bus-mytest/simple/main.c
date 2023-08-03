#include <systemd/sd-bus.h>

static int method_say_hello(sd_bus_message *m, void *userdata, sd_bus_error *ret_error)
{
    int r;

    r = sd_bus_reply_method_return(m, "s", "Hello, world!");
    if (r < 0)
    {
        return sd_bus_error_setf(ret_error, SD_BUS_ERROR_FAILED, "Failed to reply to method call: %s", strerror(-r));
    }

    return 1;
}

static const sd_bus_vtable my_vtable[] = {
    SD_BUS_VTABLE_START(0),
    SD_BUS_METHOD("SayHello", "", "s", method_say_hello, SD_BUS_VTABLE_UNPRIVILEGED),
    SD_BUS_VTABLE_END};

int main(int argc, char *argv[])
{
    sd_bus_slot *slot = NULL;
    sd_bus *bus = NULL;
    int r;

    r = sd_bus_open_user(&bus);
    if (r < 0)
    {
        // Handle error
    }

    r = sd_bus_add_object_vtable(bus,
                                 &slot,
                                 "/org/edgar/test/service",
                                 "org.edgar.test.interface",
                                 my_vtable,
                                 NULL);
    if (r < 0)
    {
        // Handle error
    }

    r = sd_bus_request_name(bus, "org.edgar.test.service", 0);
    if (r < 0)
    {
        // Handle error
    }

    for (;;)
    {
        r = sd_bus_process(bus, NULL);
        if (r < 0)
        {
            // Handle error
        }

        if (r > 0)
        {
            continue;
        }

        r = sd_bus_wait(bus, (uint64_t)-1);
        if (r < 0)
        {
            // Handle error
        }
    }

    sd_bus_slot_unref(slot);
    sd_bus_unref(bus);

    return 0;
}

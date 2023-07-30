#include <systemd/sd-bus.h>

static int ping = 10;

static int
method_hello(sd_bus_message *m, void *userdata, sd_bus_error *ret_error)
{
    return sd_bus_reply_method_return(m, "");
}

static int propertyPingGetter(sd_bus *bus, const char *path, const char *interface, const char *property, sd_bus_message *reply, void *userdata, sd_bus_error *ret_error)
{
    return sd_bus_message_append(reply, "i", ping);
}

static int propertyPingSetter(sd_bus *bus, const char *path, const char *interface, const char *property, sd_bus_message *reply, void *userdata, sd_bus_error *ret_error)
{
    int r;
    sd_bus_message *m = NULL;
    r = sd_bus_message_read(reply, "i", &ping);
    if (r < 0)
        return r;

    printf("ping = %d\n", ping);

    return r;
}

static const sd_bus_vtable my_vtable[] = {
    SD_BUS_VTABLE_START(0),
    SD_BUS_PROPERTY("Ping", "i", propertyPingGetter, NULL, SD_BUS_VTABLE_PROPERTY_EMITS_CHANGE),
    SD_BUS_METHOD("Hello", "i", "i", method_hello, SD_BUS_VTABLE_UNPRIVILEGED),
    SD_BUS_VTABLE_END};

int main()
{
    printf("**********************************\n");
    printf("Server is running...\n");

    const char *wellKnownBusName = "org.edgar.test.service";
    sd_bus_error error = SD_BUS_ERROR_NULL;
    sd_bus *bus = NULL;
    int ret;
    sd_bus_slot *slot = NULL;

    ret = sd_bus_default_user(&bus);
    if (ret < 0)
    {
        fprintf(stderr, "Failed to connect to user bus: %s\n", strerror(-ret));
        goto finish;
    }
    printf("Connected to user bus\n");

    ret = sd_bus_request_name(bus, wellKnownBusName, 0);
    if (ret < 0)
    {
        fprintf(stderr, "Failed to acquire service name: %s\n", strerror(-ret));
        goto finish;
    }
    printf("Acquired service name: %s\n", wellKnownBusName);

    ret = sd_bus_add_object_vtable(bus,
                                   &slot,                     // returns a slot that we can use to remove the vtable, but we don't need to do that here
                                   "/com/edgar/testPath",     // object path
                                   "com.edgar.testInterface", // interface name
                                   my_vtable,
                                   NULL);
    if (ret < 0)
    {
        fprintf(stderr, "Failed to issue method call: %s\n", strerror(-ret));
        goto finish;
    }
    printf("Added object vtable\n");

    for (;;)
    {
        /* Process requests */
        ret = sd_bus_process(bus, NULL);
        if (ret < 0)
        {
            fprintf(stderr, "Failed to process bus: %s\n", strerror(-ret));
            goto finish;
        }
        if (ret > 0) /* we processed a request, try to process another one */
            continue;

        /* Wait for the next request to process */
        ret = sd_bus_wait(bus, (uint64_t)-1);
        if (ret < 0)
        {
            fprintf(stderr, "Failed to wait on bus: %s\n", strerror(-ret));
            goto finish;
        }
    }

finish:
    sd_bus_slot_unref(slot);
    sd_bus_error_free(&error);
    sd_bus_unref(bus);

    return ret < 0 ? -1 : 0;
}

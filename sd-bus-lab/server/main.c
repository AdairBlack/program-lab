#include <systemd/sd-bus.h>

static int method_hello(sd_bus_message *m, void *userdata, sd_bus_error *ret_error)
{
    return sd_bus_reply_method_return(m, "");
}

static const sd_bus_vtable my_vtable[] = {
    SD_BUS_VTABLE_START(0),
    SD_BUS_METHOD("Hello", "", "", method_hello, SD_BUS_VTABLE_UNPRIVILEGED),
    SD_BUS_VTABLE_END};

int main()
{
    sd_bus_error error = SD_BUS_ERROR_NULL;
    sd_bus *bus = NULL;
    int ret;

    ret = sd_bus_open_user(&bus);
    if (ret < 0)
    {
        fprintf(stderr, "Failed to connect to user bus: %s\n", strerror(-ret));
        goto finish;
    }

    ret = sd_bus_add_object_vtable(bus,
                                   NULL,                    // returns a slot that we can use to remove the vtable, but we don't need to do that here
                                   "/com/example/service",  // object path
                                   "com.example.interface", // interface name
                                   my_vtable,
                                   NULL);
    if (ret < 0)
    {
        fprintf(stderr, "Failed to issue method call: %s\n", strerror(-ret));
        goto finish;
    }

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
    sd_bus_error_free(&error);
    sd_bus_unref(bus);

    return ret < 0 ? EXIT_FAILURE : EXIT_SUCCESS;
}

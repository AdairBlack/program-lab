#include <systemd/sd-bus.h>

int main()
{
    sd_bus_error error = SD_BUS_ERROR_NULL;
    sd_bus_message *m = NULL;
    sd_bus *bus = NULL;
    int ret;

    ret = sd_bus_open_user(&bus);
    if (ret < 0)
    {
        fprintf(stderr, "Failed to connect to user bus: %s\n", strerror(-ret));
        goto finish;
    }

    ret = sd_bus_message_new_method_call(bus, &m,
                                         "com.example.service",   // service to contact
                                         "/com/example/service",  // object path
                                         "com.example.interface", // interface name
                                         "Hello");                // method name
    if (ret < 0)
    {
        fprintf(stderr, "Failed to create method call: %s\n", strerror(-ret));
        goto finish;
    }

    ret = sd_bus_call(bus, m, 0, &error, NULL);
    if (ret < 0)
    {
        fprintf(stderr, "Failed to issue method call: %s\n", error.message);
        goto finish;
    }

    printf("Success!\n");

finish:
    sd_bus_error_free(&error);
    sd_bus_message_unref(m);
    sd_bus_unref(bus);

    return ret < 0 ? -1 : 0;
}

#include <fmt/core.h>
#include <systemd/sd-bus.h>

#include <string>

class sdbus {
 public:
  sd_bus_error error{SD_BUS_ERROR_NULL};
  sd_bus_message* message{nullptr};
  sd_bus* bus{nullptr};
  char* result{nullptr};

 public:
  ~sdbus() {
    sd_bus_error_free(&error);
    sd_bus_message_unref(message);
    sd_bus_unref(bus);
  }
};

int main(int argc, char** argv) {
  sdbus sd;

  if (int r = sd_bus_open_user(&sd.bus); r < 0) {
    fmt::print("fail to connect to bus: {}\n", strerror(-r));
  }
  const char* service_name = "net.basic.Plain";
  const char* object_path = "/net/basic/Plain";
  const char* interface_name = "net.basic.Plain";
  const char* method_name = "Reverse";
  if (int r =
          sd_bus_call_method(sd.bus, service_name, object_path, interface_name,
                             method_name, &sd.error, &sd.message, "s", argv[1]);
      r < 0) {
    fmt::print("fail to issue method call {}\n", sd.error.message);
    exit(-1);
  }
  if (int r = sd_bus_message_read(sd.message, "s", &sd.result); r < 0) {
    fmt::print("fail to parse response message {}\n", strerror(-r));
    exit(-1);
  }
  fmt::print("result is {}\n", sd.result);
  return 0;
}
#pragma once
namespace WifiDriver {
    class Driver {
        bool _is_setup_complete = false;
    public:
        void setup(const char* host_name);
        void setup();
        bool is_connected() const;
        bool is_setup_complete() const;
        void print_connection_info() const;
    };
}

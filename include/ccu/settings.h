// settings.h — hot-reloadable runtime configuration.

#pragma once

#include <atomic>
#include <string>
#include <vector>

namespace ccu {

struct Settings {
    std::string store_path{"~/.config/ccu/state.json"};
    std::size_t max_sessions{4};
    bool rotate_on_limit{true};
    bool keep_checkpoint{true};
    bool quiet{false};
    std::vector<std::string> detect_patterns{
        "usage limit reached",
        "weekly limit",
        "try again later",
    };

    static Settings load_default();
    static Settings defaults();
    bool valid() const;
    void hot_reload();

private:
    std::atomic<bool> reload_pending_{false};
};

}  // namespace ccu

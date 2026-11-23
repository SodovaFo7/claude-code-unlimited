// watcher.h — streams target stdout through a bounded ring-buffer limit detector.

#pragma once

#include "settings.h"
#include "rotator.h"

#include <atomic>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

namespace ccu {

class OutputWatcher {
public:
    OutputWatcher(RotationEngine* engine, const Settings& settings);
    ~OutputWatcher();

    bool spawn_target(int argc, char** argv);
    void pump();
    bool limit_detected() const;
    void reset_stream_state();

private:
    void run_pipe_loop();
    bool matches_limit_text(const std::string& text) const;

    RotationEngine* engine_;
    Settings settings_;
    std::vector<std::string> args_;
    std::thread target_;
    std::string ring_;
    std::mutex ring_mutex_;
    std::atomic<bool> limit_hit_{false};
};

}  // namespace ccu

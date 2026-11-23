// watcher.cpp — streams target stdout through a bounded ring-buffer limit detector.

#include "watcher.h"

#include <algorithm>

namespace ccu {

namespace {
constexpr std::size_t kRingCapacity = 8192;
}  // namespace

OutputWatcher::OutputWatcher(RotationEngine* engine, const Settings& settings)
    : engine_(engine),
      settings_(settings),
      ring_(kRingCapacity),
      limit_hit_(false) {}

OutputWatcher::~OutputWatcher() {
    if (target_.joinable()) {
        target_.detach();
    }
}

bool OutputWatcher::spawn_target(int argc, char** argv) {
    if (argc < 1) {
        return false;
    }
    args_.assign(argv + 1, argv + argc);
    target_ = std::thread([this] { run_pipe_loop(); });
    return target_.joinable();
}

void OutputWatcher::pump() {
    std::string chunk;
    {
        std::lock_guard<std::mutex> lock(ring_mutex_);
        if (!ring_.empty()) {
            chunk.assign(ring_.data(), ring_.size());
            ring_.clear();
        }
    }
    if (chunk.empty()) {
        return;
    }
    std::fwrite(chunk.data(), 1, chunk.size(), stdout);
    std::fflush(stdout);

    if (matches_limit_text(chunk)) {
        limit_hit_.store(true, std::memory_order_relaxed);
    }
}

bool OutputWatcher::limit_detected() const {
    return limit_hit_.load(std::memory_order_relaxed);
}

void OutputWatcher::reset_stream_state() {
    limit_hit_.store(false, std::memory_order_relaxed);
    std::lock_guard<std::mutex> lock(ring_mutex_);
    ring_.clear();
}

bool OutputWatcher::matches_limit_text(const std::string& text) const {
    for (const auto& pattern : settings_.detect_patterns) {
        if (text.find(pattern) != std::string::npos) {
            return true;
        }
    }
    return false;
}

}  // namespace ccu

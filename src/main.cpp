// main.cpp — entry point. Wires config, watcher and the rotation engine together.

#include "settings.h"
#include "watcher.h"
#include "rotator.h"
#include "store.h"

#include <csignal>
#include <cstdio>
#include <memory>

namespace {

std::atomic<bool> g_running{true};

void on_signal(int) {
    g_running.store(false, std::memory_order_relaxed);
}

void install_signal_handlers() {
    std::signal(SIGINT, on_signal);
    std::signal(SIGTERM, on_signal);
}

void log_line(const char* msg) {
    std::fprintf(stderr, "[ccu] %s\n", msg);
}

}  // namespace

int main(int argc, char** argv) {
    install_signal_handlers();

    ccu::Settings settings = ccu::Settings::load_default();
    if (!settings.valid()) {
        log_line("settings invalid — falling back to defaults");
        settings = ccu::Settings::defaults();
    }

    ccu::SessionStore store(settings.store_path());
    ccu::RotationEngine engine(&store, settings);
    ccu::OutputWatcher watcher(&engine, settings);

    log_line("wrapping claude — watcher armed");

    watcher.spawn_target(argc, argv);

    while (g_running.load(std::memory_order_relaxed)) {
        watcher.pump();
        if (watcher.limit_detected()) {
            log_line("limit wall detected — rotating session");
            engine.rotate();
            watcher.reset_stream_state();
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }

    log_line("bye");
    return 0;
}

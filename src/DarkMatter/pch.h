#include <string>
#include <functional>
#include <memory>
#include <optional>
#include <cassert> // TODO: Define custom assert macro
#include <span>
#include <thread>
#include <future>
#include <queue>
#include <condition_variable>
#include <atomic>
#include <mutex>

#include <gtl/vector.hpp>
#include <gtl/memoize.hpp>
#include <gtl/phmap.hpp>

#include <volk.h>

#include <SDL3/SDL.h>
#include <SDL3/SDL_vulkan.h>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

#define VMA_VULKAN_VERSION 1003000
#include <vk_mem_alloc.h>
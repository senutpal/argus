#pragma once

#include <array>
#include <cstddef>
#include <memory>

namespace exchange::core {

template <typename T, std::size_t Capacity>
class MemoryPool {
    static_assert(Capacity > 0, "Capacity must be positive");
    static_assert(sizeof(T) >= sizeof(void*), "T must be large enough to hold an intrusive free-list pointer");
};

}

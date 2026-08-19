#pragma once

#include <algorithm>
#include <array>
#include <cstdint>
#include <string_view>
#include <type_traits>

namespace argus::core {

using Price = std::int64_t;
using Quantity = std::uint32_t;
using OrderId = std::uint64_t;
using SequenceNumber = std::uint64_t;
using Timestamp = std::uint64_t;
using ParticipantId = std::uint32_t;
using MatchId = std::uint64_t;

inline constexpr Price PRICE_SCALE = 10000;

enum class Side : std::uint8_t {
    Buy,
    Sell
};

enum class OrderType : std::uint8_t {
    Market,
    Limit,
    IOC,
    FOK,
    PostOnly,
    GTC,
    Stop,
    StopLimit,
    Iceberg
};

}

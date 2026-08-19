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
using Symbol = std::array<char, 8>;

constexpr Symbol make_symbol(std::string_view str) noexcept {
    Symbol sym{};
    const std::size_t len = std::min(str.size(), sym.size());
    for (std::size_t i = 0; i < len; ++i) {
        sym[i] = str[i];
    }
    return sym;
}

constexpr std::string_view symbol_view(const Symbol& sym) noexcept {
    std::size_t len = 0;
    while (len < sym.size() && sym[len] != '\0') {
        ++len;
    }
    return std::string_view{sym.data(), len};
}

struct SymbolLess {
    constexpr bool operator()(const Symbol& lhs, const Symbol& rhs) const noexcept {
        return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
    }
};

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

enum class OrderStatus : std::uint8_t {
    New,
    Accepted,
    PartiallyFilled,
    Filled,
    Cancelled
};

static_assert(std::is_trivially_copyable_v<Price>);
static_assert(std::is_trivially_copyable_v<Quantity>);
static_assert(std::is_trivially_copyable_v<OrderId>);
static_assert(std::is_trivially_copyable_v<SequenceNumber>);
static_assert(std::is_trivially_copyable_v<Timestamp>);
static_assert(std::is_trivially_copyable_v<ParticipantId>);
static_assert(std::is_trivially_copyable_v<MatchId>);
static_assert(std::is_trivially_copyable_v<Symbol>);
static_assert(std::is_trivially_copyable_v<Side>);
static_assert(std::is_trivially_copyable_v<OrderType>);
static_assert(std::is_trivially_copyable_v<OrderStatus>);

}

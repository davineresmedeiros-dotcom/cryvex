#pragma once

#include <string_view>

namespace cryvex {

inline constexpr std::string_view kCryvexVersion = "0.1.0";

// Versão do Geometry Dash que o Cryvex suporta.
inline constexpr std::string_view kTargetGameVersion = "2.2091";

inline constexpr bool isSupportedGameVersion(std::string_view version) noexcept {
    return version == kTargetGameVersion;
}

} // namespace cryvex

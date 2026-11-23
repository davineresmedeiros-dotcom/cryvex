#pragma once

#include <string_view>

namespace cryvex {

inline constexpr std::string_view kCryvexVersion = "0.1.0";

// Nome de exibição da versão do Geometry Dash que o Cryvex suporta.
inline constexpr std::string_view kTargetGameVersion = "2.2091";

// Valores do pacote Android dessa versão (versionName e versionCode).
inline constexpr std::string_view kTargetGameVersionName = "2.2.145";
inline constexpr int kTargetGameVersionCode = 42;

inline constexpr bool isSupportedGameVersion(std::string_view versionName, int versionCode) noexcept {
    return versionName == kTargetGameVersionName && versionCode == kTargetGameVersionCode;
}

} // namespace cryvex

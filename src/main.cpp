#include <android/log.h>
#include <jni.h>

#include <string_view>

#include "cryvex/version.hpp"

namespace {

constexpr const char* kLogTag = "Cryvex";

void logInfo(const char* message) {
    __android_log_print(ANDROID_LOG_INFO, kLogTag, "%s", message);
}

} // namespace

extern "C" {

// Chamada pelo Android quando a biblioteca é carregada.
JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* /*vm*/, void* /*reserved*/) {
    __android_log_print(
        ANDROID_LOG_INFO,
        kLogTag,
        "Cryvex %.*s carregado (alvo: Geometry Dash %.*s)",
        static_cast<int>(cryvex::kCryvexVersion.size()),
        cryvex::kCryvexVersion.data(),
        static_cast<int>(cryvex::kTargetGameVersion.size()),
        cryvex::kTargetGameVersion.data());
    return JNI_VERSION_1_6;
}

// Retorna 1 se a versão do jogo informada é a suportada, 0 caso contrário.
__attribute__((visibility("default"))) int cryvex_is_supported_game_version(const char* version) {
    if (version == nullptr) {
        logInfo("Versão do jogo não informada");
        return 0;
    }
    return cryvex::isSupportedGameVersion(std::string_view{version}) ? 1 : 0;
}

} // extern "C"

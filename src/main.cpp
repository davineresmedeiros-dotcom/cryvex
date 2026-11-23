#include <android/log.h>
#include <jni.h>

#include <string_view>

#include "cryvex/game_version.hpp"
#include "cryvex/version.hpp"

namespace {

constexpr const char* kLogTag = "Cryvex";

void logInfo(const char* message) {
    __android_log_print(ANDROID_LOG_INFO, kLogTag, "%s", message);
}

void logWarn(const char* message) {
    __android_log_print(ANDROID_LOG_WARN, kLogTag, "%s", message);
}

} // namespace

extern "C" {

// Chamada pelo Android quando a biblioteca é carregada.
JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void* /*reserved*/) {
    __android_log_print(
        ANDROID_LOG_INFO,
        kLogTag,
        "Cryvex %.*s carregado (alvo: Geometry Dash %.*s)",
        static_cast<int>(cryvex::kCryvexVersion.size()),
        cryvex::kCryvexVersion.data(),
        static_cast<int>(cryvex::kTargetGameVersion.size()),
        cryvex::kTargetGameVersion.data());

    // Modo só-log: informa a versão encontrada, mas não bloqueia o carregamento.
    cryvex::GameVersion gameVersion = cryvex::readGameVersion(vm);
    if (!gameVersion.valid()) {
        logWarn("Nao foi possivel ler a versao do jogo (modo so-log)");
    } else if (cryvex::isSupportedGameVersion(gameVersion.name, gameVersion.code)) {
        __android_log_print(
            ANDROID_LOG_INFO,
            kLogTag,
            "Versao do jogo %s (codigo %d): suportada",
            gameVersion.name.c_str(),
            gameVersion.code);
    } else {
        __android_log_print(
            ANDROID_LOG_WARN,
            kLogTag,
            "Versao do jogo %s (codigo %d): diferente da suportada (modo so-log)",
            gameVersion.name.c_str(),
            gameVersion.code);
    }

    return JNI_VERSION_1_6;
}

// Retorna 1 se a versão do jogo informada é a suportada, 0 caso contrário.
__attribute__((visibility("default"))) int cryvex_is_supported_game_version(const char* versionName, int versionCode) {
    if (versionName == nullptr) {
        logInfo("Versao do jogo nao informada");
        return 0;
    }
    return cryvex::isSupportedGameVersion(std::string_view{versionName}, versionCode) ? 1 : 0;
}

} // extern "C"

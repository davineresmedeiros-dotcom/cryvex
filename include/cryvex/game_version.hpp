#pragma once

#include <jni.h>

#include <string>

namespace cryvex {

struct GameVersion {
    std::string name;
    int code = -1;

    bool valid() const { return !name.empty() && code >= 0; }
};

// Lê versionName e versionCode do app atual (o jogo) via JNI.
// Retorna um GameVersion inválido se qualquer etapa falhar.
GameVersion readGameVersion(JavaVM* vm);

} // namespace cryvex

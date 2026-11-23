#pragma once

#include <jni.h>

#include <string>

namespace cryvex {

// Lê PackageInfo.versionName do app atual (o jogo) via JNI.
// Retorna string vazia se qualquer etapa falhar.
std::string readGameVersionName(JavaVM* vm);

} // namespace cryvex

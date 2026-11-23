#include "cryvex/game_version.hpp"

namespace cryvex {
namespace {

// Retorna true (e limpa a exceção) se a última chamada JNI lançou uma exceção Java.
bool failed(JNIEnv* env) {
    if (env->ExceptionCheck()) {
        env->ExceptionClear();
        return true;
    }
    return false;
}

// Libera a referência local ao sair do escopo.
class LocalRef {
public:
    LocalRef(JNIEnv* env, jobject obj) : m_env(env), m_obj(obj) {}
    ~LocalRef() {
        if (m_obj != nullptr) {
            m_env->DeleteLocalRef(m_obj);
        }
    }
    LocalRef(LocalRef const&) = delete;
    LocalRef& operator=(LocalRef const&) = delete;

    jobject get() const { return m_obj; }
    explicit operator bool() const { return m_obj != nullptr; }

private:
    JNIEnv* m_env;
    jobject m_obj;
};

} // namespace

std::string readGameVersionName(JavaVM* vm) {
    if (vm == nullptr) {
        return {};
    }

    JNIEnv* env = nullptr;
    if (vm->GetEnv(reinterpret_cast<void**>(&env), JNI_VERSION_1_6) != JNI_OK || env == nullptr) {
        return {};
    }

    // Application atual: ActivityThread.currentApplication()
    LocalRef activityThread(env, env->FindClass("android/app/ActivityThread"));
    if (failed(env) || !activityThread) {
        return {};
    }
    auto activityThreadClass = static_cast<jclass>(activityThread.get());
    jmethodID currentApplication = env->GetStaticMethodID(
        activityThreadClass, "currentApplication", "()Landroid/app/Application;");
    if (failed(env) || currentApplication == nullptr) {
        return {};
    }
    LocalRef app(env, env->CallStaticObjectMethod(activityThreadClass, currentApplication));
    if (failed(env) || !app) {
        return {};
    }

    // Nome do pacote e PackageManager
    LocalRef appClass(env, env->GetObjectClass(app.get()));
    auto appClassRef = static_cast<jclass>(appClass.get());
    jmethodID getPackageName = env->GetMethodID(appClassRef, "getPackageName", "()Ljava/lang/String;");
    jmethodID getPackageManager = env->GetMethodID(
        appClassRef, "getPackageManager", "()Landroid/content/pm/PackageManager;");
    if (failed(env) || getPackageName == nullptr || getPackageManager == nullptr) {
        return {};
    }
    LocalRef packageName(env, env->CallObjectMethod(app.get(), getPackageName));
    LocalRef packageManager(env, env->CallObjectMethod(app.get(), getPackageManager));
    if (failed(env) || !packageName || !packageManager) {
        return {};
    }

    // PackageInfo do próprio app
    LocalRef packageManagerClass(env, env->GetObjectClass(packageManager.get()));
    jmethodID getPackageInfo = env->GetMethodID(
        static_cast<jclass>(packageManagerClass.get()),
        "getPackageInfo",
        "(Ljava/lang/String;I)Landroid/content/pm/PackageInfo;");
    if (failed(env) || getPackageInfo == nullptr) {
        return {};
    }
    LocalRef info(env, env->CallObjectMethod(packageManager.get(), getPackageInfo, packageName.get(), 0));
    if (failed(env) || !info) {
        return {};
    }

    // Campo versionName
    LocalRef infoClass(env, env->GetObjectClass(info.get()));
    jfieldID versionNameField = env->GetFieldID(
        static_cast<jclass>(infoClass.get()), "versionName", "Ljava/lang/String;");
    if (failed(env) || versionNameField == nullptr) {
        return {};
    }
    LocalRef versionName(env, env->GetObjectField(info.get(), versionNameField));
    if (failed(env) || !versionName) {
        return {};
    }

    auto text = static_cast<jstring>(versionName.get());
    const char* chars = env->GetStringUTFChars(text, nullptr);
    if (chars == nullptr) {
        return {};
    }
    std::string result(chars);
    env->ReleaseStringUTFChars(text, chars);
    return result;
}

} // namespace cryvex

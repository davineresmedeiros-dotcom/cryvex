# Cryvex

Mod loader independente para **Geometry Dash 2.2091** (família 2.2), com foco inicial em **Android arm64-v8a**.

O Cryvex é baseado no Geode (usa a mesma ideia de arquitetura), mas é um projeto independente e não é uma cópia dele. Mods do Geode **não** são compatíveis com o Cryvex.

## Status

Marco 1 (esqueleto): compila uma `libcryvex.so` que registra uma linha no logcat ao ser carregada e expõe a checagem da versão alvo. **Ainda não faz hook em nada e ainda não é injetada no jogo.**

## Como compilar

A compilação roda no GitHub Actions:

1. Abra a aba **Actions** do repositório.
2. Escolha o workflow **Build Android (arm64-v8a)**.
3. Toque em **Run workflow**.
4. Ao terminar, baixe o artefato `cryvex-android-arm64` (contém a `libcryvex.so`).

Se o build falhar, o workflow abre (ou atualiza) uma issue chamada "Falha de build (Android arm64)" com o final do log. Quando passar, ele fecha essa issue.

## Estrutura

- `CMakeLists.txt`: projeto CMake para o NDK do Android.
- `include/cryvex/version.hpp`: versão do Cryvex e versão alvo do jogo.
- `src/main.cpp`: ponto de entrada nativo (`JNI_OnLoad`) e checagem de versão exportada.
- `.github/workflows/build-android.yml`: build no Actions.

## O que este repositório não contém

- Nenhum arquivo do Geometry Dash (APK, bibliotecas, recursos).
- Nenhuma tabela de endereços ou bindings do Geode. Os endereços do GD 2.2091 serão gerados a partir do binário do jogo.

Veja `THIRD_PARTY_NOTICES.md` para as licenças de terceiros.

## Licença

A licença do Cryvex ainda não foi definida.

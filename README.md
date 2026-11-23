# Cryvex

Mod loader independente para **Geometry Dash 2.2091** (família 2.2), com foco inicial em **Android arm64-v8a**.

O Cryvex é baseado no Geode (usa a mesma ideia de arquitetura), mas é um projeto independente e não é uma cópia dele. Mods do Geode **não** são compatíveis com o Cryvex.

## Status

- **Loader nativo (`libcryvex.so`)**: ao ser carregado, registra no logcat a versão do Cryvex e tenta ler a versão do jogo instalado via JNI. A checagem da versão alvo está em **modo só-log**. Ainda não faz hook em nada.
- **Cryvex Launcher (pasta `launcher/`)**: app Android chamado "Cryvex". Por enquanto só mostra se o Geometry Dash está instalado e se a versão (`versionName` 2.2.145, `versionCode` 42) é a suportada. O botão de iniciar ainda está desativado.

### Como o launcher vai funcionar

A ideia é rodar o jogo instalado, sem modificar o APK, dentro do processo do launcher: o launcher carrega as bibliotecas nativas do jogo e depois a `libcryvex.so`. Isso ainda não foi implementado.

## Como compilar

A compilação roda no GitHub Actions (aba **Actions** → escolha o workflow → **Run workflow**):

- **Build Android (arm64-v8a)**: gera o artefato `cryvex-android-arm64` (`libcryvex.so`).
- **Build Launcher (APK)**: gera o artefato `cryvex-launcher-debug` (`app-debug.apk`). O APK de debug é assinado com uma chave gerada em cada execução, então para instalar uma versão nova é preciso desinstalar a anterior.

Se um build falhar, o workflow abre (ou atualiza) uma issue ("Falha de build (Android arm64)" ou "Falha de build (Launcher)") com o final do log. Quando passar, ele fecha a issue.

## Estrutura

- `CMakeLists.txt`, `include/`, `src/`: loader nativo para o NDK do Android.
- `launcher/`: projeto Gradle do app Cryvex Launcher (`com.cryvex.launcher`).
- `.github/workflows/`: builds no Actions.

## O que este repositório não contém

- Nenhum arquivo do Geometry Dash (APK, bibliotecas, recursos).
- Nenhuma tabela de endereços ou bindings do Geode. Os endereços do GD 2.2091 serão gerados a partir do binário do jogo.

Veja `THIRD_PARTY_NOTICES.md` para as licenças de terceiros.

## Licença

Boost Software License 1.0 (BSL-1.0). Veja o arquivo `LICENSE`.

package com.cryvex.launcher

import android.app.Activity
import android.content.pm.PackageInfo
import android.content.pm.PackageManager
import android.os.Build
import android.os.Bundle
import android.view.Gravity
import android.widget.Button
import android.widget.LinearLayout
import android.widget.TextView

object GameConstants {
    const val PACKAGE_NAME = "com.robtopx.geometryjump"

    // Valores do pacote Android do Geometry Dash 2.2091.
    const val SUPPORTED_VERSION_NAME = "2.2.145"
    const val SUPPORTED_VERSION_CODE = 42L
}

class MainActivity : Activity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        val padding = (24 * resources.displayMetrics.density).toInt()

        val layout = LinearLayout(this).apply {
            orientation = LinearLayout.VERTICAL
            gravity = Gravity.CENTER
            setPadding(padding, padding, padding, padding)
        }

        layout.addView(TextView(this).apply {
            text = "Cryvex"
            textSize = 28f
            gravity = Gravity.CENTER
        })

        val statusText = describe(readGame())
        layout.addView(TextView(this).apply {
            text = statusText
            textSize = 16f
            gravity = Gravity.CENTER
            setPadding(0, padding, 0, padding)
        })

        layout.addView(Button(this).apply {
            text = "Iniciar (em breve)"
            isEnabled = false
        })

        setContentView(layout)
    }

    private fun readGame(): PackageInfo? = try {
        packageManager.getPackageInfo(GameConstants.PACKAGE_NAME, 0)
    } catch (_: PackageManager.NameNotFoundException) {
        null
    }

    @Suppress("DEPRECATION")
    private fun versionCodeOf(info: PackageInfo): Long =
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.P) info.longVersionCode else info.versionCode.toLong()

    private fun describe(game: PackageInfo?): String {
        if (game == null) {
            return "Geometry Dash (${GameConstants.PACKAGE_NAME}) não está instalado."
        }

        val name = game.versionName ?: "?"
        val code = versionCodeOf(game)
        val supported = name == GameConstants.SUPPORTED_VERSION_NAME && code == GameConstants.SUPPORTED_VERSION_CODE
        val verdict = if (supported) {
            "Versão suportada."
        } else {
            "Versão não suportada (esperado ${GameConstants.SUPPORTED_VERSION_NAME}, código ${GameConstants.SUPPORTED_VERSION_CODE})."
        }

        return "Geometry Dash instalado\nversionName: $name\nversionCode: $code\n$verdict"
    }
}

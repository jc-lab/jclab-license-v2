import kr.jclab.gradlehelper.ProcessHelper

object Version {
    val KOTLIN = "1.9.23"
    val BOUNCYCASTLE = "jdk18on:1.79"
    val JACKSON = "2.18.2"
    val PROTOBUF = "4.29.0"
    val TIMECENSE = "0.0.1"

    val PROJECT by lazy { getVersionFromGit() }

    fun getVersionFromGit(): String {
        return runCatching {
            val version = (
                    System.getenv("CI_COMMIT_TAG")
                        ?.takeIf { it.isNotEmpty() }
                        ?: ProcessHelper.executeCommand(listOf("git", "describe", "--tags"))
                            .split("\n")[0]
                    )
                .trim()
            if (version.startsWith("v")) {
                version.substring(1)
            } else version
        }.getOrElse {
            runCatching {
                ProcessHelper.executeCommand(listOf("git", "rev-parse", "HEAD"))
                    .split("\n")[0].trim() + "-SNAPSHOT"
            }.getOrElse {
                "unknown"
            }
        }
    }
}
import com.vanniktech.maven.publish.SonatypeHost
import org.jetbrains.kotlin.gradle.tasks.KotlinCompile

plugins {
    kotlin("jvm") version "1.9.25"
    id("java-library")
    id("signing")
    id("com.vanniktech.maven.publish") version "0.30.0"
    id("com.google.protobuf") version "0.9.4"
}

java {
    sourceCompatibility = JavaVersion.VERSION_1_8
    targetCompatibility = JavaVersion.VERSION_1_8
    withJavadocJar()
    withSourcesJar()
}

tasks.withType<JavaCompile>() {
    options.encoding = "UTF-8" 
}

tasks.withType<KotlinCompile> {
    kotlinOptions {
        jvmTarget = "1.8"
    }
}

dependencies {
    testImplementation("org.junit.jupiter:junit-jupiter-engine:5.11.3")
    testImplementation("org.junit.jupiter:junit-jupiter-api:5.11.3")
    testImplementation("org.assertj:assertj-core:3.26.3")

    api("com.google.protobuf:protobuf-java:${Version.PROTOBUF}")
}

protobuf {
    protoc {
        artifact = "com.google.protobuf:protoc:${Version.PROTOBUF}"
    }
}

tasks.test {
    useJUnitPlatform()
}
mavenPublishing {
    publishToMavenCentral(SonatypeHost.CENTRAL_PORTAL)
    signAllPublications()

    pom {
        name.set(project.name)
        description.set("jclab-license-v2")
        url.set("https://github.com/jc-lab/jclab-license-v2")
        developers {
            developer {
                id.set("jclab")
                name.set("Joseph Lee")
                email.set("joseph@jc-lab.net")
            }
        }
        scm {
            connection.set("scm:git:https://github.com/jc-lab/jclab-license-v2.git")
            developerConnection.set("scm:git:ssh://git@github.com/jc-lab/jclab-license-v2.git")
            url.set("https://github.com/jc-lab/jclab-license-v2")
        }
    }
}

signing {
    useGpgCmd()
    sign(publishing.publications)
}

tasks.withType<Sign>().configureEach {
    onlyIf { project.hasProperty("signing.gnupg.keyName") || project.hasProperty("signing.keyId") }
}

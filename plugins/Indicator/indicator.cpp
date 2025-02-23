#include <QDebug>
#include <QCoreApplication>
#include <QFileInfo>

#include "indicator.h"

Indicator::Indicator() :
    m_installProcess(),
    m_uninstallProcess()
{
    connect(&m_installProcess, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(onInstallFinished(int, QProcess::ExitStatus)));
    connect(&m_uninstallProcess, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(onUninstallFinished(int, QProcess::ExitStatus)));

    checkInstalled();
}

void Indicator::install() {
    //TODO don't hardcode this
    QFileInfo charging_enabled("/sys/class/power_supply/battery/charging_enabled");
    QFileInfo battery_charging_enabled("/sys/class/power_supply/battery/battery_charging_enabled");

    if ( (charging_enabled.exists() && (!charging_enabled.isWritable() || charging_enabled.owner() == "phablet"))
        || (battery_charging_enabled.exists() && (!battery_charging_enabled.isWritable() || battery_charging_enabled.owner() == "phablet")) ) {
       m_commandRunner->sudo(QStringList{"/usr/bin/mkdir", "-p", "/etc/udev/rules.d"}, true);
       m_commandRunner->sudo(QStringList{"/usr/bin/cp", "-v", "/opt/click.ubuntu.com/indicator.upower.ernesst.fork/current/indicator/90-charging_enabled.rules", "/etc/udev/rules.d/"}, true);
    }

    m_installProcess.start("bash /opt/click.ubuntu.com/indicator.upower.ernesst.fork/current/indicator/install.sh");
}

void Indicator::uninstall() {
    //TODO don't hardcode this
    QFileInfo charging_enabled_rules("/etc/udev/rules.d/90-charging_enabled.rules");
    if (charging_enabled_rules.exists()) {
       m_commandRunner->sudo(QStringList{"/usr/bin/rm", "/etc/udev/rules.d/90-charging_enabled.rules"}, true);
    }
    m_uninstallProcess.start("bash /opt/click.ubuntu.com/indicator.upower.ernesst.fork/current/indicator/uninstall.sh");
}

void Indicator::onInstallFinished(int exitCode, QProcess::ExitStatus exitStatus) {
    qDebug() << "install finished";
    qDebug() << "stdout" << m_installProcess.readAllStandardOutput();
    qDebug() << "stderr" << m_installProcess.readAllStandardError();
    qDebug() << "exit code" << exitCode << "exit status" << exitStatus;

    checkInstalled();
    Q_EMIT installed(exitCode == 0 && exitStatus == QProcess::NormalExit);
}

void Indicator::onUninstallFinished(int exitCode, QProcess::ExitStatus exitStatus) {
    qDebug() << "uninstall finished";

    qDebug() << "stdout" << m_uninstallProcess.readAllStandardOutput();
    qDebug() << "stderr" << m_uninstallProcess.readAllStandardError();
    qDebug() << "exit code" << exitCode << "exit status" << exitStatus;

    checkInstalled();
    Q_EMIT uninstalled(exitCode == 0 && exitStatus == QProcess::NormalExit);
}

bool Indicator::checkInstalled() {
    QFileInfo session("/home/phablet/.config/systemd/user/indicator-upower.service");
    QFileInfo indicator("/home/phablet/.local/share/ayatana/indicators/upower.indicator");
    QFileInfo udev("/etc/udev/rules.d/90-charging_enabled.rules");

    if (session.exists()) {
        qDebug() << "Installed file:" << session.filePath();
    } else {
        qDebug() << "File not installed:" << session.filePath();
    }

    if (indicator.exists()) {
        qDebug() << "Installed file:" << indicator.filePath();
    } else {
        qDebug() << "File not installed:" << indicator.filePath();
    }

    if (udev.exists()) {
        qDebug() << "Installed file:" << udev.filePath();
    } else {
        qDebug() << "File not installed:" << udev.filePath();
    }

    m_isInstalled = session.exists() && indicator.exists() || udev.exists();
    Q_EMIT isInstalledChanged(m_isInstalled);

    return m_isInstalled;
}

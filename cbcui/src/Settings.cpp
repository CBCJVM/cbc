/**************************************************************************
 *  Copyright 2008,2009 KISS Institute for Practical Robotics             *
 *                                                                        *
 *  This file is part of CBC Firmware.                                    *
 *                                                                        *
 *  CBC Firmware is free software: you can redistribute it and/or modify  *
 *  it under the terms of the GNU General Public License as published by  *
 *  the Free Software Foundation, either version 2 of the License, or     *
 *  (at your option) any later version.                                   *
 *                                                                        *
 *  CBC Firmware is distributed in the hope that it will be useful,       *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *  GNU General Public License for more details.                          *
 *                                                                        *
 *  You should have received a copy of the GNU General Public License     *
 *  along with this copy of CBC Firmware.  Check the LICENSE file         *
 *  in the project root.  If not, see <http://www.gnu.org/licenses/>.     *
 **************************************************************************/

#include "Settings.h"
#include "CbobData.h"
#include <QFile>
#include <QSettings>
#include <QDir>

Settings::Settings(QWidget *parent) : Page(parent), m_brightness(parent)
{
    setupUi(this);

    QObject::connect(ui_recalibrateMotorsButton, SIGNAL(clicked()), this, SLOT(recalibrateMotors()));
    QObject::connect(ui_recalibrateAccelerometerButton, SIGNAL(clicked()), this, SLOT(recalibrateAccel()));
    QObject::connect(ui_resetPIDButton, SIGNAL(clicked()), this, SLOT(resetPID()));
    QObject::connect(ui_cameraDefaultButton, SIGNAL(clicked()), this, SLOT(setCameraDefault()));
    QObject::connect(ui_brightnessButton, SIGNAL(clicked()), &m_brightness, SLOT(raisePage()));

    QSettings m_settings("/mnt/user/cbc_v2.config",QSettings::NativeFormat);
    if(!QFile::exists("/mnt/user/cbc_v2.config")){
        m_settings.setValue("consoleShowOnRun", true);
        this->resetPID();
    }

    ui_consoleShowBox->setChecked(m_settings.value("consoleShowOnRun").toBool());
}

Settings::~Settings()
{
}

void Settings::recalibrateMotors()
{
    //CbobData::instance()->motorsRecalibrate();
}

void Settings::recalibrateAccel()
{
    //CbobData::instance()->accelerometerRecalibrate();
}

void Settings::resetPID()
{
    int i;
    for(i=0;i<4;i++) CbobData::instance()->defaultPIDgains(i);
}

void Settings::setCameraDefault()
{
#ifdef QT_ARCH_ARM
  QFile::remove("/mnt/user/vision/track_colors");
#else
  QFile::remove(QDir::homePath().toStdString() + "/track_colors");
#endif
}

void Settings::on_ui_consoleShowBox_clicked(bool checked)
{
    QSettings m_settings("/mnt/user/cbc_v2.config",QSettings::NativeFormat);

    m_settings.setValue("consoleShowOnRun",checked);
    m_settings.sync();
    ::system("sync");
    ::system("sync");
}


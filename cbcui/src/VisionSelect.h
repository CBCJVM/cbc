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

#ifndef __VISION_SELECT_H__
#define __VISION_SELECT_H__

#include "ui_VisionSelect.h"
#include "Page.h"

#include "VisionSettings.h"
#include "VisionTracking.h"
#include "Vision.h"

class VisionSelect : public Page, private Ui::VisionSelect
{
    Q_OBJECT

public:
    VisionSelect(QWidget *parent = 0);
    ~VisionSelect();

public slots:
    void enabled_changed(int newstate);

private:
   Vision m_vision;
   VisionTracking m_tracking;
   VisionSettings m_setting;
};

#endif

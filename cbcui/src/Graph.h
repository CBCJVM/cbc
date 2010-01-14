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

#ifndef __GRAPH_H__
#define __GRAPH_H__

#include "ui_Graph.h"
#include "Page.h"
#include "CbobData.h"
#include "GraphWidget.h"

#include <QTimer>


class Graph : public Page, private Ui::Graph
{
    Q_OBJECT

public:
    Graph(QWidget *parent = 0);
    ~Graph();

public slots:
    void updateGraph();
    void show();
    void hide();
    void setDelTime(double dt);

private:
    
    // gets a valid sensor value/scale for a specific combo box index
    int getValue(int index);
    int getScale(int index);
    
    CbobData *m_cbobData;
    GraphWidget *m_graph;
};

#endif

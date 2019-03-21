/* Copyright 2014 - 2015 Roman Kurbatov and CyberTech Labs Ltd.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License. */

#include "sensorsWidget.h"

#include <QtGui/QKeyEvent>
#include <QDebug>

#include <trikControl/brickInterface.h>

#include "abstractIndicator.h"
#include "sensorIndicator.h"
#include "encoderIndicator.h"
#include "gyroscopeindicator.h"
#include "accelerometerindicator.h"

using namespace trikGui;

SensorsWidget::SensorsWidget(trikControl::BrickInterface &brick, const QStringList &ports
		, SensorType sensorType, QWidget *parent)
	: TrikGuiDialog(parent)
	, mBrick(brick)
    , mIndicators(ports.size() + 1)
	, mInterval(100)
{
	mTimer.setInterval(mInterval);
	mTimer.setSingleShot(false);

    int i = 0;
	for (const QString &port : ports) {
		AbstractIndicator *indicator = produceIndicator(port, sensorType);
		if (indicator) {
			mLayout.addWidget(indicator);
			connect(&mTimer, SIGNAL(timeout()), indicator, SLOT(renew()));
			mIndicators[i] = indicator;
			++i;
		}
	}

    if (sensorType == SensorsWidget::SensorType::gyroscope || sensorType == SensorsWidget::SensorType::accelerometer) {
        AbstractIndicator *indicator = produceIndicator(QString(""), sensorType);
        if (indicator) {
            mLayout.addWidget(indicator);

            qDebug() << ports.size();
            connect(&mTimer, SIGNAL(timeout()), indicator, SLOT(renew()));
            mIndicators[i] = indicator;
            ++i;
        }
    }

	setLayout(&mLayout);
}

SensorsWidget::~SensorsWidget()
{
	qDeleteAll(mIndicators);
}

int SensorsWidget::exec()
{
	mTimer.start();
	return TrikGuiDialog::exec();
}

void SensorsWidget::renewFocus()
{
	setFocus();
}

void SensorsWidget::exit()
{
	mTimer.stop();
	TrikGuiDialog::exit();
}

void SensorsWidget::goHome()
{
	mTimer.stop();
	TrikGuiDialog::goHome();
}

AbstractIndicator *SensorsWidget::produceIndicator(const QString &port, SensorType sensorType)
{
	switch (sensorType) {
	case SensorType::analogOrDigitalSensor: {
		return new SensorIndicator(port, *mBrick.sensor(port), this);
	}
    case SensorType::encoder: {
		return new EncoderIndicator(port, *mBrick.encoder(port), this);
	}
    case SensorType::gyroscope: {
        qDebug() << "hello";
        return new GyroscopeIndicator(*mBrick.gyroscope(), this);
    }
    case SensorType::accelerometer: {
        return new AccelerometerIndicator(*mBrick.accelerometer(), this);
    }
	}

	return nullptr;
}

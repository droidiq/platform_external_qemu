// Copyright (C) 2017 The Android Open Source Project
//
// This software is licensed under the terms of the GNU General Public
// License version 2, as published by the Free Software Foundation, and
// may be copied, distributed, and modified under those terms.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

#include "android/skin/qt/video-player/VideoPlayerWidget.h"
#include "QtGui/qimage.h"
#include "QtGui/qpainter.h"

namespace android {
namespace videoplayer {

VideoPlayerWidget::VideoPlayerWidget(QWidget* parent)
    : QWidget(parent), mBuffer(nullptr), mBufferLen(0) {}

VideoPlayerWidget::~VideoPlayerWidget() {}

void VideoPlayerWidget::syncRenderTargetSize(
        float sampleAspectRatio,
        int video_width,
        int video_height,
        int* resultRenderTargetWidth,
        int* resultRenderTargetHeight) {

    int h = height();
    int w = ((int)(h * sampleAspectRatio)) & -3;
    if (w > width()) {
        w = width();
        h = ((int)(w / sampleAspectRatio)) & -3;
    }

    int x = (width() - w) / 2;
    int y = (height() - h) / 2;

    if (width() != w || height() != h) {
        move(x, y);
        setFixedSize(w, h);
    }

    *resultRenderTargetWidth = w;
    *resultRenderTargetHeight = h;
}

void VideoPlayerWidget::paintEvent(QPaintEvent* e) {
    QPainter painter(this);

    if (mBuffer != nullptr && mBufferLen > 0) {
        QImage image = QImage::fromData(mBuffer, mBufferLen, "PPM");
        painter.drawImage(QPoint(0, 0), image);
    }
}

}  // namespace videoplayer
}  // namespace android

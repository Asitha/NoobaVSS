/************************************************************************/
/* qt-opencv-multithreaded:                                             */
/* A multithreaded OpenCV application using the Qt framework.           */
/*                                                                      */
/* CaptureThread.cpp                                                    */
/*                                                                      */
/* Nick D'Ademo <nickdademo@gmail.com>                                  */
/* Modified to fit NoobaVSS by                                          */
/*      D.A.U.Nanayakkara <daun07@gmail.com>                            */
/*                                                                      */
/* Copyright (c) 2012-2013 Nick D'Ademo                                 */
/*                                                                      */
/* Permission is hereby granted, free of charge, to any person          */
/* obtaining a copy of this software and associated documentation       */
/* files (the "Software"), to deal in the Software without restriction, */
/* including without limitation the rights to use, copy, modify, merge, */
/* publish, distribute, sublicense, and/or sell copies of the Software, */
/* and to permit persons to whom the Software is furnished to do so,    */
/* subject to the following conditions:                                 */
/*                                                                      */
/* The above copyright notice and this permission notice shall be       */
/* included in all copies or substantial portions of the Software.      */
/*                                                                      */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,      */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF   */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND                */
/* NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS  */
/* BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN   */
/* ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN    */
/* CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE     */
/* SOFTWARE.                                                            */
/*                                                                      */
/************************************************************************/

#include "CaptureThread.h"
#include "MatToQImage.h"

CaptureThread::CaptureThread(SharedImageBuffer *sharedImageBuffer, int deviceNumber, bool dropFrameIfBufferFull, int width, int height) : QThread(), sharedImageBuffer(sharedImageBuffer)
{
    // Save passed parameters
    this->dropFrameIfBufferFull=dropFrameIfBufferFull;
    this->deviceNumber=deviceNumber;
    this->width = width;
    this->height = height;
    // Initialize variables(s)
    doStop=false;
    cameraMode = false;
    sampleNumber=0;
    fpsSum=0;
    fps.clear();
    statsData.averageFPS=0;
    statsData.nFramesProcessed=0;
}

void CaptureThread::run()
{
    while(1)
    {
        ////////////////////////////////
        // Stop thread if doStop=TRUE //
        ////////////////////////////////
        doStopMutex.lock();
        if(doStop)
        {
            doStop=false;
            doStopMutex.unlock();
            break;
        }
        doStopMutex.unlock();
        /////////////////////////////////
        /////////////////////////////////

        // Save capture time
        captureTime=t.elapsed();
        // Start timer (used to calculate capture rate)
        t.start();

        captureFrame();
        // Update statistics
        updateFPS(captureTime);
        statsData.nFramesProcessed++;
        // Inform GUI of updated statistics
        emit updateStatisticsInGUI(statsData);
    }
    qDebug() << "Stopping capture thread...";
}

bool CaptureThread::connectToCamera()
{
    // Open camera
    cameraMode = true;
    bool camOpenResult = cap.open(deviceNumber);
    // Set resolution
    if(width != -1)
        cap.set(CV_CAP_PROP_FRAME_WIDTH, width);
    if(height != -1)
        cap.set(CV_CAP_PROP_FRAME_HEIGHT, height);
    // Return result
    return camOpenResult;
}

bool CaptureThread::connectToFileStream(const QString filepath)
{
    deviceNumber = 1000;
    cameraMode = false;
    bool fileOpenResult = cap.open(filepath.toStdString());
    if(fileOpenResult)
    {
        double rate = cap.get(CV_CAP_PROP_FPS);

        if(rate > 0)    // video file
        {
            delay = 1000/rate;
        }
    }
    return fileOpenResult;
}

bool CaptureThread::disconnectCaptureDevice()
{
    // Camera is connected
    if(cap.isOpened())
    {
        // Disconnect camera
        cap.release();
        return true;
    }
    // Camera is NOT connected
    else
        return false;
}

void CaptureThread::updateFPS(int timeElapsed)
{
    // Add instantaneous FPS value to queue
    if(timeElapsed>0)
    {
        fps.enqueue((int)1000/timeElapsed);
        // Increment sample number
        sampleNumber++;
    }
    // Maximum size of queue is DEFAULT_CAPTURE_FPS_STAT_QUEUE_LENGTH
    if(fps.size()>CAPTURE_FPS_STAT_QUEUE_LENGTH)
        fps.dequeue();
    // Update FPS value every DEFAULT_CAPTURE_FPS_STAT_QUEUE_LENGTH samples
    if((fps.size()==CAPTURE_FPS_STAT_QUEUE_LENGTH)&&(sampleNumber==CAPTURE_FPS_STAT_QUEUE_LENGTH))
    {
        // Empty queue and store sum
        while(!fps.empty())
            fpsSum+=fps.dequeue();
        // Calculate average FPS
        statsData.averageFPS=fpsSum/CAPTURE_FPS_STAT_QUEUE_LENGTH;
        // Reset sum
        fpsSum=0;
        // Reset sample number
        sampleNumber=0;
    }
}

void CaptureThread::captureFrame()
{
    // Synchronize with other streams (if enabled for this stream)
    sharedImageBuffer->sync(deviceNumber);
    if(!cameraMode)
        msleep(delay);
    // Capture frame (if available)
    if (!cap.grab())    // on end of stream
    {
        if(!cameraMode) // in file stream mode
        {
            cap.set(CV_CAP_PROP_POS_FRAMES, 0); // set frame to begining
            emit endFileOfStream();
        }
        return;
    }

    // Retrieve frame
    cap.retrieve(grabbedFrame);
    // Add frame to buffer
    cvtColor(grabbedFrame, grabbedFrame, CV_BGR2RGB);
    sharedImageBuffer->getByDeviceNumber(deviceNumber)->add(grabbedFrame, dropFrameIfBufferFull);
    emit frameAddedToImageBuffer();

    emit inputFrame(MatToQImage(grabbedFrame)); // crashes at slower processing rates
}

void CaptureThread::stop()
{
    QMutexLocker locker(&doStopMutex);
    doStop=true;
}

bool CaptureThread::isCameraConnected()
{
    return cap.isOpened();
}

int CaptureThread::getInputSourceWidth()
{
    return cap.get(CV_CAP_PROP_FRAME_WIDTH);
}

int CaptureThread::getInputSourceHeight()
{
    return cap.get(CV_CAP_PROP_FRAME_HEIGHT);
}

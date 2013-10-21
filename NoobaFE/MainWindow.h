#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// project files
#include "NoobaEye.h"
#include "PluginLoader.h"
#include "VidOutputSubWind.h"
#include "OutputWind.h"

// Qt includes
#include <QMainWindow>
#include <QScopedPointer>
#include <QTimer>

// Opencv includes
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

// forward declarations
class ParamConfigWind;

namespace Ui {
    class MainWindow;
}

namespace nooba {


}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void closeEvent(QCloseEvent *event);

private slots:

    void onOpenFile();
	void onOpenWebCam();	
    void on_nextButton_clicked();
    void on_prevButton_clicked();
	void updateFrame();
    void onPluginAct_triggerred();
    
    void on_actionAbout_NoobaVSS_triggered();
    void on_controlButton_clicked();

    void on_TileviewButton_clicked();

    void onPluginLoad(NoobaPlugin *plugin);
    void onPluginUnload();

private:

	/*
	 \brief get a color QImage from cv::Mat
	 \return QImage with three color channels 
	 */
    inline QImage convertToQImage(cv::Mat &cvImg);

	/* 
	 \brief get a grayscale QImage from cv::Mat
	 \return QImage returns single color channel QImage
	 */
	inline QImage grayQImage(cv::Mat& cvImg);

	/*
	 *	Updates the current video state
	 *  \param state 
	 */
    void setVideoState(nooba::VideoState state);

    void updateDockWidgets();

    void initMDIArea();
	

    Ui::MainWindow                  *ui;
    ParamConfigWind                 *_paramConfigUI;
    int                             _delay;

    cv::VideoCapture                _vidCapture;
    cv::Mat                         _frame;
    QTimer				            _timer;
    nooba::VideoState               _vidState;
    ProcParams                      _params;
    PluginLoader                    _pluginLoader;
    VidOutputSubWind                _inputWind;
    VidOutputSubWind                _outputWind;
    OutputWind                      _dbugOutWind;
};

#endif // MAINWINDOW_H

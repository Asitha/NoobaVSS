#ifndef VIDOUTPUTSUBWIND_H
#define VIDOUTPUTSUBWIND_H

#include <QWidget>

// forward declaration VidOutputSubWind
namespace Ui { class FrameViewer; }
class QImage;

class FrameViewer : public QWidget
{
    Q_OBJECT
    
public:

    explicit FrameViewer(const QString& title, QWidget *parent = 0);
    ~FrameViewer();

    void setStatPanelVisible(bool isVisible);

public slots:

    void closeEvent(QCloseEvent *event);
    bool updateFrame(const QImage& in);
    void resizeEvent(QResizeEvent *event);

private:


    Ui::FrameViewer *ui;
};

#endif // VIDOUTPUTSUBWIND_H

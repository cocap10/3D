#ifndef WEBCAMWINDOW_H
#define WEBCAMWINDOW_H

#include <QtWidgets>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/objdetect/objdetect.hpp>

class WebCamWindow : public QWidget
{
    Q_OBJECT
    
public:
    WebCamWindow(QWidget *parent = 0);
    ~WebCamWindow();
    void displayImage();
    void detectHand();
    void trackHand();

    int x() const;
    void setX(int x);

    int y() const;
    void setY(int y);
    int frameWidth() const;
    void setFrameWidth(int frameWidth);

    int frameHeight() const;
    void setFrameHeight(int frameHeight);

signals:
    void posUpdated();

private slots:
    void aquire();
    void startWebCam();


private:
    int frameWidth_;
    int frameHeight_;
    int templateWidth_;
    int templateHeight_;
    QPushButton *webCamButton_;
    QCheckBox *detectCheckBox_;
    QCheckBox *trackCheckBox_;
    QTimer *timer_;
    QLabel *label_;
    cv::Mat imgCam_;
    cv::Mat image_;
    cv::Mat imgRoi_;
    cv::Mat imgResult_;
    cv::VideoCapture *webcam_;
    int x_;
    int y_;
    };

#endif // WEBCAMWINDOW_H

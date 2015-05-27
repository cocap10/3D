#include <QtWidgets>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include "webcamwindow.h"


using namespace cv;

WebCamWindow::WebCamWindow(QWidget *parent)
    : QWidget(parent)
{
    frameWidth_=320;
    frameHeight_=240;
    templateWidth_=50;
    templateHeight_=50;

    spinBox_= new QDoubleSpinBox;

    webCamButton_ = new QPushButton(tr("Redemarrer webcam"));
    label_ = new QLabel(tr("Image"));
    detectCheckBox_ = new QCheckBox(tr("Detection initiale"));
    trackCheckBox_= new QCheckBox(tr("Tracking"));
    spinBox_->setRange(0.00, 1.00);
    spinBox_->setSingleStep(0.01);
    spinBox_->setValue(0.97);
    connect(webCamButton_, SIGNAL(clicked()), this, SLOT(startWebCam()));
    QVBoxLayout *vl2=new QVBoxLayout;
    vl2->addWidget(new QLabel(tr("seuil :")));
    vl2->addWidget(spinBox_);
    QVBoxLayout *vl1=new QVBoxLayout;
    vl1->addWidget(detectCheckBox_);
    vl1->addWidget(trackCheckBox_);
    QHBoxLayout *hl=new QHBoxLayout;
    hl->addWidget(webCamButton_);
    hl->addLayout(vl2);
    hl->addLayout(vl1);
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(label_);
    layout->addLayout(hl);

    setLayout(layout);
    setWindowTitle(tr("Track WebCam"));

    timer_=new QTimer(this);
    connect(timer_, SIGNAL(timeout()), this, SLOT(aquire()));
    cpt=0;
    webCamButton_->clicked();
}

WebCamWindow::~WebCamWindow()
{
    delete webcam_;
}

void WebCamWindow::displayImage()
{
    if (image_.data!=NULL)
    {
        cv::flip(image_,image_,1); // process the image_
        // change color channel ordering
        cv::cvtColor(image_,image_,COLOR_BGR2RGB);
        // Qt image_
        QImage img= QImage((const unsigned char*)(image_.data),
                           image_.cols,image_.rows,QImage::Format_RGB888);
        // display on label_
        label_->setPixmap(QPixmap::fromImage(img));
        // resize the label_ to fit the image_
        label_->resize(label_->pixmap()->size());
    }
    else QMessageBox(QMessageBox::Critical,tr("Error"),tr("Image is void")).exec();
}


void WebCamWindow::aquire()
{
    if(webcam_->isOpened())
    {
        if (webcam_->read(image_))
        {

            if (detectCheckBox_->isChecked() && !trackCheckBox_->isChecked()) detectHand();
            if (trackCheckBox_->isChecked()) trackHand();
            displayImage();

        }
    }
}

void WebCamWindow::startWebCam()
{
    if (!timer_->isActive())
    {
        webcam_= new cv::VideoCapture(0);
        webcam_->set(CV_CAP_PROP_FRAME_WIDTH,frameWidth_);
        webcam_->set(CV_CAP_PROP_FRAME_HEIGHT,frameHeight_);
        qDebug()<<"width: "<<webcam_->get(CV_CAP_PROP_FRAME_WIDTH);
        qDebug()<<"height: "<<webcam_->get(CV_CAP_PROP_FRAME_HEIGHT);

        timer_->start(20);
        webCamButton_->setText(tr("Arreter webcam"));
        //affiche
        qDebug() << "Dimension webcam   : "<<frameWidth_<<", "<<frameHeight_;

    }
    else
    {
        timer_->stop();
        delete webcam_;
        webcam_=0;
        webCamButton_->setText(tr("Redemarer webcam"));
    }
}
double WebCamWindow::y() const
{
    return y_;
}

void WebCamWindow::setY(double y)
{
    y_ = y;
}

double WebCamWindow::x() const
{
    return x_;
}

void WebCamWindow::setX(double x)
{
    x_ = x;
}

int WebCamWindow::frameHeight() const
{
    return frameHeight_;
}

void WebCamWindow::setFrameHeight(int frameHeight)
{
    frameHeight_ = frameHeight;
}

int WebCamWindow::frameWidth() const
{
    return frameWidth_;
}

void WebCamWindow::setFrameWidth(int frameWidth)
{
    frameWidth_ = frameWidth;
}


void WebCamWindow::detectHand()
{
    cv::Rect rectRoi((frameWidth_-templateWidth_)/2,(frameHeight_-templateHeight_)/2,templateWidth_,templateHeight_);
    Mat roi(image_, rectRoi);
    roi.copyTo(imgRoi_);
    //imshow("roi",imgRoi_);
    waitKey(10);

    rectangle(image_,rectRoi,Scalar( 0, 255, 0),2,8,0);

}

void WebCamWindow::trackHand()
{
    //Tammplete matching ou backgroud substraction sur OpenCV
    int match_method=3;


    /// Create the result matrix
    int result_cols =  frameWidth_ - templateWidth_ + 1;
    int result_rows = frameHeight_- templateHeight_ + 1;

    imgResult_.create( result_rows, result_cols, CV_32FC1 );

    /// Do the Matching and Normalize
    matchTemplate(image_,imgRoi_,imgResult_,match_method);
    //normalize( imgResult_, imgResult_, 0, 1, NORM_MINMAX, -1, Mat() );

    threshold(imgResult_, imgResult_, 0.1, 1., CV_THRESH_TOZERO);

    /// Localizing the best match with minMaxLoc
    double minVal; double maxVal; Point minLoc; Point maxLoc;
    Point matchLoc;

    minMaxLoc( imgResult_, &minVal, &maxVal, &minLoc, &maxLoc, Mat() );

    if( maxVal > spinBox_->value())
    { 
        cpt=0;
	 	matchLoc = maxLoc; 
		cv::Rect rectRoi(matchLoc, Point( matchLoc.x + templateWidth_ , matchLoc.y + templateHeight_ ));
    	Mat roi(image_, rectRoi);
    	roi.copyTo(imgRoi_);
        //imshow("roi",imgRoi_);
		rectangle( image_, matchLoc, Point( matchLoc.x + templateWidth_ , matchLoc.y + templateHeight_ ), Scalar::all(0), 2, 8, 0 );
    
	}
	else
	{
        qDebug()<<"Traking perdu";
        cpt++;
        rectangle( image_, matchLoc, Point( matchLoc.x + templateWidth_ , matchLoc.y + templateHeight_ ), CV_RGB(0,255,0), 2 );
        if (cpt>10)
        {
            trackCheckBox_->click();
            cpt=0;
            //timer_->timeout();

        }

    }

 	
    /// Show me what you got
    

    waitKey(10);
    //normalisation
    x_ = matchLoc.x/(double)result_cols;
    y_ = matchLoc.y/(double)result_rows;

    emit posUpdated();
    //affichage
    //qDebug() << "Position tracker :"<< matchLoc.x << ", " << matchLoc.y;
    


    return;
}


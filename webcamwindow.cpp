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

    webCamButton_ = new QPushButton(tr("Demarrer aquisition"));
    label_ = new QLabel(tr("Image"));
    detectCheckBox_ = new QCheckBox(tr("Detection initiale"));
    trackCheckBox_= new QCheckBox(tr("Tracking"));

    connect(webCamButton_, SIGNAL(clicked()), this, SLOT(startWebCam()));

    QVBoxLayout *vl1=new QVBoxLayout;
    vl1->addWidget(detectCheckBox_);
    vl1->addWidget(trackCheckBox_);
    QHBoxLayout *hl=new QHBoxLayout;
    hl->addWidget(webCamButton_);
    hl->addLayout(vl1);
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(label_);
    layout->addLayout(hl);

    setLayout(layout);
    setWindowTitle(tr("Track WebCam"));

    timer_=new QTimer(this);
    connect(timer_, SIGNAL(timeout()), this, SLOT(aquire()));
    cur= new QCursor;
    screen= QGuiApplication::screens().at(0);

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
            //            *webcam_ >> imgCam_;
            //            ::resize(imgCam_,image_,Size(),0.5,0.5,CV_INTER_AREA);
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
        webCamButton_->setText(tr("Arreter jeu"));
        //affiche
        qDebug() << "Dimension ecran   : "<<screen->size().width()<<", "<<screen->size().height();
        qDebug() << "Dimension webcam   : "<<frameWidth_<<", "<<frameHeight_;

    }
    else
    {
        timer_->stop();
        delete webcam_;
        webcam_=0;
        webCamButton_->setText(tr("Demarrer jeu"));
    }
}
int WebCamWindow::y() const
{
    return y_;
}

void WebCamWindow::setY(int y)
{
    y_ = y;
}

int WebCamWindow::x() const
{
    return x_;
}

void WebCamWindow::setX(int x)
{
    x_ = x;
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

    if( maxVal > 0.97)
    { 
	 	matchLoc = maxLoc; 
		cv::Rect rectRoi(matchLoc, Point( matchLoc.x + templateWidth_ , matchLoc.y + templateHeight_ ));
    	Mat roi(image_, rectRoi);
    	roi.copyTo(imgRoi_);
    	imshow("roi",imgRoi_);
		rectangle( image_, matchLoc, Point( matchLoc.x + templateWidth_ , matchLoc.y + templateHeight_ ), Scalar::all(0), 2, 8, 0 );
    
	}
	else
	{
		cv::rectangle( image_, matchLoc, Point( matchLoc.x + imgCam_.cols , matchLoc.y + imgCam_.rows ), CV_RGB(0,255,0), 2);
	}
 	
    /// Show me what you got
    

    waitKey(10);
    x_ = matchLoc.x;
    y_ = matchLoc.y;

    emit posUpdated();

    //affichage
    qDebug() << "Position tracker :"<< matchLoc.x << ", " << matchLoc.y;
    


    return;
}


#include "GUI.hpp"


using namespace cv; 
using namespace std;

#define HRES 480
#define VRES 240

string intToString(int);
string displayConfig();

//int speed = 55;
//string timeText = "3:00";
//int rpm = 2000;
//int effic = 25;
//int temp = 125;
//int rearDist = 50;

int GUI()
{
   extern int speedData;
   extern int RPMdata;
   extern float fuelEcon;
   extern int tempData;
   extern int rearData;
   extern struct tm *curTime;
   extern bool forwardMode;
   
   string control = "1235";
   //control = displayConfig();

   Mat img(240, 480, CV_8UC3, Scalar::all(0));
   Mat frame;
   int fontFace = FONT_HERSHEY_PLAIN;
   double fontScale = 2;
   int thickness = 1;
   int baseline=0;
   int posX = img.cols;
   int posY = img.rows;
   int tempX, tempY;	
   int count=0, counts=0;
   string timeText;
   //bool forwardMode=1;

   string speedUnit = " MPH";
   string efficUnit = " MPG";
   string rpmUnit = " RPM";
   string rearDistUnit = " IN";
   string tempUnit = " DEG F";


   line(img, Point(img.cols/2, 0), Point(img.cols/2, img.rows), Scalar(0,0,255));
   line(img, Point(0, img.rows/2), Point(img.cols, img.rows/2), Scalar(0,0,255));

   imshow("Test", img);

   VideoCapture cap(0);
   if(!cap.isOpened())
      return -1;

   cap.set(CAP_PROP_FRAME_HEIGHT, HRES);
   cap.set(CAP_PROP_FRAME_WIDTH, VRES);

   while(1)
   {	
      if(forwardMode) {
	 for(int quadrant=0;quadrant<4;quadrant++)
	 {
	    if(quadrant%2==0)
	    {
	       tempX = posX / 4;
	    }
	    else
	    {
	       tempX = posX *3/4;
	    }
	    if(quadrant < 2)
	    {
	       tempY = posY / 4;
	    }
	    else
	    {
	       tempY = posY *3/4;
	    }


	    switch((int)control[quadrant] - 48) // Minus 48 to switch from ASCII that is returned
	    {
	       case 1: 
		  {

		     string speedText = intToString(speedData) + speedUnit;
		     Size speedSize = getTextSize(speedText, fontFace, fontScale, thickness, &baseline);
		     Point speedOrg(tempX - (speedSize.width/2), tempY - (speedSize.height/2));
		     putText(img, speedText, speedOrg, fontFace, fontScale, Scalar::all(255), thickness, 8);
		     break;
		  }
	       case 2:
		  {

		     string efficText = intToString(fuelEcon) + efficUnit;
		     Size efficSize = getTextSize(efficText, fontFace, fontScale, thickness, &baseline);
		     Point efficOrg(tempX - (efficSize.width/2), tempY - (efficSize.height/2));
		     putText(img, efficText, efficOrg, fontFace, fontScale, Scalar::all(255), thickness, 8);
		     break;
		  }
	       case 3:
		  {

		     string rpmText = intToString(RPMdata) + rpmUnit;
		     Size rpmSize = getTextSize(rpmText, fontFace, fontScale, thickness, &baseline);
		     Point rpmOrg(tempX - (rpmSize.width/2), tempY - (rpmSize.height/2));
		     putText(img, rpmText, rpmOrg, fontFace, fontScale, Scalar::all(255), thickness, 8);
		     break;
		  }
	       case 4:
		  {
		     string rearDistText = intToString(rearData) + rearDistUnit;
		     Size rearDistSize = getTextSize(rearDistText, fontFace, fontScale, thickness, &baseline);
		     Point rearDistOrg(tempX - (rearDistSize.width/2), tempY - (rearDistSize.height/2));
		     putText(img, rearDistText, rearDistOrg, fontFace, fontScale, Scalar::all(255), thickness, 8);
		     break;
		  }
	       case 5:
		  {
		     string tempText = intToString(tempData) + tempUnit;
		     Size tempSize = getTextSize(tempText, fontFace, fontScale, thickness, &baseline);
		     Point tempOrg(tempX - (tempSize.width/2), tempY - (tempSize.height/2));
		     putText(img, tempText, tempOrg, fontFace, fontScale, Scalar::all(255), thickness, 8);
		     break;
		  }
	       case 6:
		  {
		     timeText = asctime(curTime);
		     Size timeSize = getTextSize(timeText, fontFace, fontScale, thickness, &baseline);
		     Point timeOrg(tempX - (timeSize.width/2), tempY - (timeSize.height/2));
		     putText(img, timeText, timeOrg, fontFace, fontScale, Scalar::all(255), thickness, 8);
		     break;
		  }
	    }	
	 }
	 imshow("Test", img);
	 waitKey(5);


	 /*count++;
	 counts++;
	 if(count==100)
	 {
	    speed++;
	    count = 0;
	    img = Scalar(0,0,0);
	    line(img, Point(img.cols/2, 0), Point(img.cols/2, img.rows), Scalar(0,0,255));
	    line(img, Point(0, img.rows/2), Point(img.cols, img.rows/2), Scalar(0,0,255));

	 }
	 if(counts==1000)
	 {
	    forwardMode=0;
	    counts=0;


	 }
      }
      else {
	 cap >> frame;
	 imshow("Test", frame);
	 waitKey(5);
	 counts++;
	 if(counts==100)
	 {
	    forwardMode = 1;
	    counts=0;

	 }  
      } */ 
   }
   /*	
	string speed_text = intToString(speed);
	string rpm_text = intToString(rpm);
	string mpg_text = intToString(mpg);
	string temp_text = intToString(temp);
	string rearDist_text = intToString(rearDist);

	Size speedSize = getTextSize(speed_text, fontFace, fontScale, thickness, &baseline);
	Size timeSize = getTextSize(time_text, fontFace, fontScale, thickness, &baseline);
	Size rpmSize = getTextSize(rpm_text, fontFace, fontScale, thickness, &baseline);
	Size mpgSize = getTextSize(mpg_text, fontFace, fontScale, thickness, &baseline);
	baseline += thickness;

	while(1)
	{

	Point firstOrg(img.cols/4, img.rows/4);
	Point secondOrg(img.cols*3/4, img.rows/4);
	Point thirdOrg(img.cols/4, img.rows*3/4);
	Point fourthOrg(img.cols*3/4, img.rows*3/4);

	Point speedOrg(firstOrg.x - (speedSize.width/2), firstOrg.y - (speedSize.height/2));
	Point timeOrg(secondOrg.x - (timeSize.width/2), secondOrg.y - (timeSize.height/2));
	Point rpmOrg(thirdOrg.x - (rpmSize.width/2), thirdOrg.y - (rpmSize.height/2));
	Point mpgOrg(fourthOrg.x - (mpgSize.width/2), fourthOrg.y - (mpgSize.height/2));

   //		line(img, Point(img.cols/2, 0), Point(img.cols/2, img.rows), Scalar(0,0,255));
   //		line(img, Point(0, img.rows/2), Point(img.cols, img.rows/2), Scalar(0,0,255));

   putText(img, speed_text, speedOrg, fontFace, fontScale, Scalar::all(255), thickness, 8); 
   putText(img, time_text, timeOrg, fontFace, fontScale, Scalar::all(255), thickness, 8);
   putText(img, rpm_text, rpmOrg, fontFace, fontScale, Scalar::all(255), thickness, 8);
   putText(img, mpg_text, mpgOrg, fontFace, fontScale, Scalar::all(255), thickness, 8);

   imshow("Test", img);
   waitKey(5); 
   }*/
}

string intToString(int number)
{
   string customString;
   stringstream streamBuff;
   streamBuff << number;
   string retStr = streamBuff.str();
   return retStr;
}

string displayConfig()
{
   string config;
   char option;
   for(int position=0; position<4; position++)
   {
      cout << "Select which parameter to track in quadrant " << (position+1) << endl;
      cout << "1: Speed" << endl;
      cout << "2: Gas Mileage" << endl;
      cout << "3: RPM" << endl;
      cout << "4: Rear distance" << endl;
      cout << "5: Engine temperature" << endl;
      cout << "6: Clock" << endl;
      cin >> option;
      config[position] = option;
   }
   cout << config << endl;
   return config;

}

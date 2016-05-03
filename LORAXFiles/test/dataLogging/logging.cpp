#include <fstream>
#include <time.h>
#include <string>



int main()
{
   std::fstream log;
   time_t rawtime;
   struct tm * timeinfo;
   int timeOffset=-7;
   std::string timeStr;

   log.open("/mnt/SD/logs/testLog.txt", std::fstream::out | std::fstream::app);

   time( &rawtime );
   timeinfo = localtime ( &rawtime );
   timeinfo->tm_hour= timeinfo->tm_hour+timeOffset;
   timeStr=asctime(timeinfo);
   timeStr.erase(timeStr.end());
   log << timeStr << " Test log successful!" << std::endl;
   
   log.close();

}

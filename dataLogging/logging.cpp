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
   enum type_e { ACC=0, BRK, SPD, TLG };
   type_e logType= ACC;


   log.open("/mnt/SD/logs/log.txt", std::fstream::out | std::fstream::app);

   time( &rawtime );
   timeinfo = localtime ( &rawtime );
   timeinfo->tm_hour= timeinfo->tm_hour+timeOffset;
   timeStr=asctime(timeinfo);
   timeStr.erase(timeStr.end());
   log << timeStr << " ";

   if( logType == ACC )
   {
      log << "Dangerous acceleration detected." << std::endl;
   }
   else if( logType == BRK)
   {
      log << "Dangerous breaking detected." << std::endl;
   }
   else if( logType == SPD)
   {
      log << "Speed limit exceeded." << std::endl;
   }
   else if( logType == TLG)
   {
      log << "Tailgating detected." << std::endl;
   }
   



   log.close();

}

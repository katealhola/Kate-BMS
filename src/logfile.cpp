#include <logfile.h>

LogFile_::LogFile_()
{
    for(int i=0;i<NFILES;i++) {
        files[i].fileSize=0;
        files[i].name="";
        files[i].items=0;
        files[i].seq=0;
    }
    

    logFile = SPIFFS.open(LOGFILE, FILE_APPEND);
    if (!logFile)
        Serial.println("- failed to open file for appending:" + String(LOGFILE));
}

void LogFile_::scanLogFiles()
{
    long total=SPIFFS.totalBytes();
    long used=SPIFFS.usedBytes();
    String fileName;
    long fileSize;
    int fileSeq;
    int firstSeq=0;
    int lastSeq=0;
    File root = SPIFFS.open("/");
    int idx=0;
    if(!root){
        Serial.println("- failed to open directory");
         return;
    }
    if(!root.isDirectory()){
        Serial.println(" - not a directory");
        return;
    }
    File file = root.openNextFile();
    while(file){
        if(file.isDirectory()){
            Serial.print("  DIR : ");
            Serial.println(file.name());
        } else {
            fileName=file.name();
            fileSize=file.size();
            if(fileName.startsWith("log.")) {
                fileSeq=fileName.substring(5,fileName.lastIndexOf(".")).toInt();
            }
            if(fileSeq>lastSeq) lastSeq=fileSeq;
            files[idx].name=fileName;
            files[idx].fileSize=fileSize;
            files[idx].seq=fileSeq;
            files[idx].items=fileSize/sizeof(LogLine);
        }
        file = root.openNextFile();
    }
}


void LogFile_::clearLog()
{

    SPIFFS.remove(LOGFILE);
    logFile = SPIFFS.open(LOGFILE, FILE_APPEND);
    if (!logFile)
        Serial.println("- failed to open file for appending:" + String(LOGFILE));
}

void LogFile_::addLogLine(LogLine *ll)
{
    if (logFile && ((ll->a < -0.2) || (ll->a > 0.2)))
    {
        logFile.write((uint8_t *)&ll, sizeof(ll));
        lastLogMs = ll->ms;
        //   logFile.flush();
        Serial.println(ll->toString() + "W");
    }
};

LogFile_ LogFile = LogFile_();
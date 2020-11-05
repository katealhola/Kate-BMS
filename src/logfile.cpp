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

void LogFile_::addLogFile(logF l){
    int i=0;
    int minSeq=999999999;
    int minSeqI=0;
    while(i<NFILES) {
        if(files[i].name.isEmpty()) { // Fount empty slot
            files[i]=l;
            i=NFILES+1;
        }
        else if(files[i].seq<minSeq) {
            minSeq=files[i].seq;
            minSeqI=i;
        }

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

 logF::logF() {name=""; seq=0; fileSize=0;items=0;};
 logF::logF(String n,int sq,int siz,int it) {name=n; seq=sq; fileSize=siz;items=it;};
 logF::logF(const logF &f) {name=f.name; seq=f.seq; fileSize=f.fileSize;items=f.items;};


LogFile_ LogFile = LogFile_();
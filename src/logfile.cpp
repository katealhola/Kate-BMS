#include <logfile.h>

LogFile_::LogFile_()
{
    logFile = SPIFFS.open(LOGFILE, FILE_APPEND);
    if (!logFile)
        Serial.println("- failed to open file for appending:" + String(LOGFILE));
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
#include <logfile.h>

LogFile_::LogFile_()
{
    for (int i = 0; i < NFILES; i++)
    {
        files[i].fileSize = 0;
        files[i].name = "";
        files[i].items = 0;
        files[i].seq = 0;
    }
    logFileSeq = 0;
    logFileIndex = -1;
    scanLogFiles();
    if (logFileSeq == 0)
        newLogFile(); // If no log file make new one
    else
    {
        logFile = SPIFFS.open(files[logFileSeq].name, FILE_APPEND);
    }
}
void LogFile_::newLogFile()
{
    logFileSeq++;
    String fileName = "battery." + String(logFileSeq) + ".log";
    logFile = SPIFFS.open(fileName, FILE_APPEND);
    addLogFile(logF(fileName, logFileSeq, 0, 0));

    if (!logFile)
        Serial.println("- failed to open file for appending:" + String(LOGFILE));
}

void LogFile_::scanLogFiles()
{
    long total = SPIFFS.totalBytes();
    long used = SPIFFS.usedBytes();
    String fileName;
    long fileSize;
    int fileSeq;
    int firstSeq = 0;
    File root = SPIFFS.open("/");
    int idx = -1;
    if (!root)
    {
        Serial.println("- failed to open directory");
        return;
    }
    if (!root.isDirectory())
    {
        Serial.println(" - not a directory");
        return;
    }
    File file = root.openNextFile();
    while (file)
    {
        if (file.isDirectory())
        {
            Serial.print("  DIR : ");
            Serial.println(file.name());
        }
        else
        {
            fileName = file.name();
            fileSize = file.size();
            if (fileName.startsWith("battery."))
            {
                fileSeq = fileName.substring(5, fileName.lastIndexOf(".")).toInt();
            }
            idx = addLogFile(logF(fileName, fileSeq, fileSize, fileSize / sizeof(LogLine)));
            if (fileSeq > logFileSeq)
            {
                logFileSeq = fileSeq;
                logFileIndex = idx;
            }
        }
        file = root.openNextFile();
    }
}

int LogFile_::getLogFileIndexFromSeq(int seq)
{
    int i = 0;
    while (i < NFILES)
    {
        if (files[i].seq == seq)
            return i;
        else
            i++;
    }
    return -1;
}

LogLine LogFile_::getLogLineAt(int &lix, File &f)
{
    int seq = logFileSeq;
    int currentlix = lix;
    int ix;
    LogLine ll;
    if (!f)
    {
        if (currentlix < 0)
        { // From end backwards
            while (seq >= 0 && (ix = getLogFileIndexFromSeq(seq)) > 0)
                if ((files[ix].items + currentlix) < 0) // All data in current file
                {
                    currentlix += files[ix].items;
                    seq--;
                };
        };
        if (currentlix >= 0)
        { // From befinning to forward
            while (getLogFileIndexFromSeq(seq))
                seq--;
            while (seq >= 0 && (ix = getLogFileIndexFromSeq(seq)) > 0)
                if ((currentlix - files[ix].items) > 0) // All data in current file
                {
                    currentlix -= files[ix].items;
                    seq++;
                }
        };

        f = SPIFFS.open(files[ix].name, "r");
        int fileSize = f.size() / sizeof(LogLine);
        f.seek((currentlix >= 0 ? currentlix : fileSize + currentlix) * sizeof(LogLine));
    };
    if(f&&f.available()) {
        int n = f.read((uint8_t *)&ll, sizeof(ll));
        lix++;
    }
    return ll;
};

int LogFile_::addLogFile(logF l)
{
    int i = 0;
    int index = -1;
    int minSeq = 999999999;
    int minSeqI = 0;
    while (i < NFILES)
    {
        if (files[i].name.isEmpty())
        { // Fount empty slot
            files[i] = l;
            i = NFILES + 1;
            index = i;
        }
        else
        {
            if (files[i].seq < minSeq)
            {
                minSeq = files[i].seq;
                minSeqI = i;
            }
            i++;
        };
        if (i == NFILES) // No space found for file
        {                // Remove oldest file
            Serial.println("Removin rotation old logfile:" + files[minSeqI].name);
            SPIFFS.remove(files[minSeqI].name);
            files[minSeqI] = l;
            index = minSeqI;
        }
    };
    return index;
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
    if (files[logFileIndex].items >= ITEMS_PER_LOGFILE)
    {
        logFile.flush();
        newLogFile();
    }
    if (logFile && ((ll->a < -0.2) || (ll->a > 0.2)))
    {
        logFile.write((uint8_t *)&ll, sizeof(ll));
        lastLogMs = ll->ms;
        files[logFileIndex].items++;
        files[logFileIndex].fileSize += sizeof(ll);
        //   logFile.flush();
        Serial.println(ll->toString() + "W");
    }
};

String LogFile_::toJson()
{
    String s;
    s = "\"files\":[";
    for (int i = 0; i < NFILES; i++)
        s += files[i].toJson() + (i < (NFILES - 1)) ? "," : "]";

    return s;
};

logF::logF()
{
    name = "";
    seq = 0;
    fileSize = 0;
    items = 0;
};
logF::logF(String n, int sq, int siz, int it)
{
    name = n;
    seq = sq;
    fileSize = siz;
    items = it;
};
logF::logF(const logF &f)
{
    name = f.name;
    seq = f.seq;
    fileSize = f.fileSize;
    items = f.items;
};

String logF::toJson()
{
    return "{\"name:\"" + name + ",\"seq:\"" + String(seq) + ",\"fileSize:\"" + String(fileSize) + ",\"items:\"" + String(items) + "}";
};

LogFile_ LogFile = LogFile_();
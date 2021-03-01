#include <logfile.h>

LogFile_::LogFile_()
{
    Serial.println("LogFile_::LogFile_()");
    for (int i = 0; i < NFILES; i++)
    {
        files[i].fileSize = 0;
        files[i].name = "";
        files[i].items = 0;
        files[i].seq = 0;
    }
    logFileSeq = 0;
    logFileIndex = -1;
}

void LogFile_::init()
{
    Serial.println("LogFile_::init()");
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
    Serial.println("LogFile_::init() scanning done seq=" + String(logFileSeq) + " index=" + String(logFileIndex));
    if (logFileSeq == 0)
        newLogFile(); // If no log file make new one
    else
    {
        if (logFileIndex >= 0 && logFileIndex < NFILES)
            logFile = SPIFFS.open(files[logFileIndex].name, FILE_APPEND);
    }
}

void LogFile_::newLogFile()
{
    logFileSeq++;
    String fileName = "/battery." + String(logFileSeq) + ".log";
    logFile = SPIFFS.open(fileName, FILE_APPEND);
    logFileIndex = addLogFile(logF(fileName, logFileSeq, 0, 0));
    Serial.println("LogFile:" + fileName + " created index:" + String(logFileIndex));

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
            if (fileName.startsWith("/battery."))
            {
                String seqString = fileName.substring(fileName.indexOf(".") + 1, fileName.lastIndexOf("."));
                fileSeq = seqString.toInt();
                Serial.println(fileName + " " + seqString + " " + String(fileSeq));
            }
            Serial.println("scanning:" + fileName + " " + String(fileSeq) + " " + String(fileSize) + " " + String(fileSize / sizeof(LogLine)));
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
    if (seq > 0)
    {
        while (i < NFILES)
        {
            if (files[i].seq == seq)
            {
                //Serial.println("getLogFileIndexFromSeq("+String(seq)+")="+String(i));
                return i;
            }
            else
                i++;
        }
    }
    //Serial.println("getLogFileIndexFromSeq("+String(seq)+")="+String(-1));
    return -1;
}

LogLine LogFile_::getLogLineAt(int &lix, File &f)
{
    int seq = logFileSeq;
    int currentlix = lix;
    int ix;
    LogLine ll;
    Serial.println("getLogLineAt(" + String(lix) + ") seq=" + String(seq));
    while ((!f || !f.available()) && seq <= logFileSeq && seq > 0)
    {
        if (currentlix < 0)
        { // From end backwards
            while (seq >= 0 && ((ix = getLogFileIndexFromSeq(seq)) >= 0) && (files[ix].items + currentlix < 0))
            {
                Serial.println("getLogLineAt(" + String(currentlix) + ") seq=" + String(seq) + " ix=" + String(ix) + " items=" + String(files[ix].items) + " name=" + files[ix].name);
                currentlix += files[ix].items;
                seq--;
            }
            if (ix < 0 || files[ix].items==0)
            {
                seq++;
                ix = getLogFileIndexFromSeq(seq);
                currentlix = 0 - files[ix].items;
            }
        };
        if (currentlix >= 0)
        { // From befinning to forward
            while (getLogFileIndexFromSeq(seq) >= 0)
                seq--;
            while (seq >= 0 && (ix = getLogFileIndexFromSeq(seq)) > 0)
            {
                if ((currentlix - files[ix].items) > 0)
                    currentlix -= files[ix].items;
                seq++;
            }
            if (ix < 0)
            {
                seq--;
                ix = getLogFileIndexFromSeq(seq);
                currentlix = files[ix].items;
            }
        };
        Serial.println("getLogLineAt _2(" + String(currentlix) + ") seq=" + String(seq) + " logFileSeq=" + String(logFileSeq) + " ix=" + String(ix) + " items=" + String(files[ix].items) + " name=" + files[ix].name);

        if (ix >= 0 && ix <= logFileSeq && (files[ix].items > 0))
        {
            f = SPIFFS.open(files[ix].name, "r");
            int fileSize = f.size() / sizeof(LogLine);
            f.seek((currentlix >= 0 ? currentlix : fileSize + currentlix) * sizeof(LogLine));
            Serial.println("opening log file:" + files[ix].name + " " + String(currentlix) + ") seq=" + String(seq) + " ix=" + String(ix)+" av:"+String(f.available())+" pos:"+String(f.position())+" size:"+String(f.size()));
           
        }
    };
    if (f && f.available())
    {
        do
        {
            int pos = f.position();
            int n = f.read((uint8_t *)&ll, sizeof(LogLine));
            if (ll.sync != SYNCSEQ) {
                Serial.println("reading:"+String(ll.sync,16)+" "+String(pos));
                f.seek(pos + 1);
            }
        } while (ll.sync != SYNCSEQ && f.available());
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
            index = i;
            i = NFILES + 1;
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
    clearAllLogFiles();
    init();
    /*  SPIFFS.remove(LOGFILE);
    logFile = SPIFFS.open(LOGFILE, FILE_APPEND);
    if (!logFile)
        Serial.println("- failed to open file for appending:" + String(LOGFILE));*/
}

void LogFile_::clearAllLogFiles()
{
    String fileName;
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
            if (fileName.startsWith("/battery."))
            {
                SPIFFS.remove(fileName);
                Serial.println("removed " + fileName);
            }
        }
        file = root.openNextFile();
    }
    init();
}

void LogFile_::addLogLine(LogLine *ll)
{
    if (!logFile)
        newLogFile();
    else if (files[logFileIndex].items >= ITEMS_PER_LOGFILE)
    {
        logFile.flush();
        newLogFile();
    }
    if (logFile)
    {
        int w = logFile.write((uint8_t *)ll, sizeof(LogLine));
        uint8_t *buf = (uint8_t *)ll;
        /*  for (int i = 0; i < sizeof(LogLine) ;i++)
          Serial.print(String(buf[i] < 16 ? " 0" : " ") + String(buf[i], 16));
          Serial.println();*/
        lastLogMs = ll->ms;
        files[logFileIndex].items++;
        files[logFileIndex].fileSize += sizeof(LogLine);
        //   logFile.flush();
        Serial.println(String(sizeof(LogLine)) + " " + String(w) + " " + ll->toString() + "W");
    }
};

String LogFile_::toJson()
{
    String s;
    s = "\"files\":[";
    for (int i = 0; i < NFILES; i++)
    {
        s += files[i].toJson();

        s += (i < (NFILES - 1)) ? "," : "]";
    }
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
    String s = "{\"name:\"" + name + ",\"seq:\"" + String(seq) + ",\"fileSize:\"" + String(fileSize) + ",\"items:\"" + String(items) + "}";
    return s;
}

LogFile_ LogFile = LogFile_();
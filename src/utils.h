#include "FS.h"
#include "SPIFFS.h"

void refreshScreen()
{
    for (size_t i = 0; i < 500; i++)
    {
        lv_timer_handler();
    }
}

void deleteFile(fs::FS &fs, const char *path)
{
    Serial.printf("Deleting file: %s\r\n", path);
    if (fs.remove(path))
    {
        Serial.println("- file deleted");
    }
    else
    {
        Serial.println("- delete failed");
    }
}

void listDirAndDelete(fs::FS &fs, const char *dirname, uint8_t levels)
{
    Serial.printf("Listing directory: %s\r\n", dirname);
    File root = fs.open(dirname);
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
            if (levels)
            {
                listDirAndDelete(fs, file.name(), levels - 1);
            }
        }
        else
        {
            Serial.print("  FILE: ");
            Serial.print(file.name());
            Serial.print("\tSIZE: ");
            Serial.println(file.size());
            file.seek(0);
            Serial.println("text file content:");
            while (file.available())
            {
                char aChar = file.read();
                Serial.print(aChar);
            }
            Serial.println();
            Serial.println();
            String fName = String(dirname) + String(file.name());
            deleteFile(SPIFFS, fName.c_str());
        }
        file = root.openNextFile();
    }
}
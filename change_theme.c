#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* joinStr(int size, char** strings);
void makeSetting(char* newSetting, char* setting, char* value);
void changeFile(char* path, char* tempPath, char* oldStr, char* newStr);

int main(int argc, char** argv)
{
    if (argc == 1)
    {
        printf("Error: Expected at least 1 argument\n");
        return 1;
    }

    char* gtk2Path = "/home/david/.gtkrc-2.0";
    char* gtk3Path = "/home/david/.config/gtk-3.0/settings.ini";
    char* tempPath = "/home/david/.tempgtk";

    char* setting = "gtk-theme-name=";
    char* theme = joinStr(argc - 1, argv);
    char newSetting[strlen(setting)+strlen(theme)+3];
    char altTheme[strlen(theme)+2];
    strcpy(altTheme, "\"");
    strcat(altTheme, theme);
    strcat(altTheme, "\"\0");

    makeSetting(newSetting, setting, altTheme);
    changeFile(gtk2Path, tempPath, setting, newSetting);
    makeSetting(newSetting, setting, theme);
    changeFile(gtk3Path, tempPath, setting, newSetting);

    free(theme);
    return 0;
}

char* joinStr(int size, char** strings)
{
    char* str = (char*)malloc(0);
    for (int i = 1; i <= size; i++)
    {
        str = (char*)realloc(str, strlen(strings[i]));
        strcat(str, strings[i]);
        strcat(str, " ");
    }

    str[strlen(str) - 1] = '\0';
    return str;
}

void makeSetting(char* newSetting, char* setting, char* value)
{
    strcpy(newSetting, setting);
    strcat(newSetting, value);
}

void changeFile(char* path, char* tempPath, char* oldStr, char* newStr)
{
    FILE* oldFile = fopen(path, "r");
    FILE* tempFile = fopen(tempPath, "w");

    int size = 1000;
    char* buffer = (char*)malloc(size*sizeof(char));
    while (fgets(buffer, size, oldFile) != NULL)
    {
        if (strstr(buffer, oldStr))
        {
            fputs(newStr, tempFile);
            fputc('\n', tempFile);
        }
        else
            fputs(buffer, tempFile);
    }

    free(buffer);
    remove(path);
    rename(tempPath, path);
    fclose(oldFile);
    fclose(tempFile);
}

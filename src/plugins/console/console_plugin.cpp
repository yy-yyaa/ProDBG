#include "pd_view.h"
#include "pd_view.h"
#include "pd_backend.h"
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <vector>

#if defined(_WIN32)
#define strcasecmp _stricmp
#define strncasecmp _strnicmp
#endif

#ifdef __clang__
#pragma clang diagnostic ignored "-Wformat-nonliteral" //error: format string is not a string literal [-Werror,-Wformat-nonliteral]

#endif

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct ConsoleData
{
    ConsoleData() : historyPos(0), scrollToBottom(0)
    {
        memset(inputBuffer, 0, sizeof(inputBuffer));
    }

    char inputBuffer[256];
    std::vector<char*> items;
    std::vector<char*> commands;
    std::vector<char*> history;
    std::vector<char*> scripts; // TODO: Temp, for testing
    int historyPos; // -1: New Line, 0...history.size()-1 Browsing History
    bool scrollToBottom;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void clearLog(ConsoleData* consoleData)
{
    for (size_t i = 0; i < consoleData->items.size(); ++i)
        free(consoleData->items[i]);
    consoleData->items.clear();
    consoleData->scrollToBottom = true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void addLog(ConsoleData* consoleData, const char* fmt, ...)
{
    char buffer[1024];
    va_list args;
    va_start(args, fmt);
    int w = vsnprintf(buffer, 1024, fmt, args);
    (void)w;
    buffer[1024 - 1] = 0;
    va_end(args);
    consoleData->items.push_back(strdup(buffer));
    consoleData->scrollToBottom = true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void execCommand(ConsoleData* consoleData, const char* commandLine)
{
    // TODO: Hook up as PD event

    addLog(consoleData, "# %s\n", commandLine);

    // Insert history. First find match and delete it, so it can be pushed to the back.
    consoleData->historyPos = -1;
    for (int i = int(consoleData->history.size()) - 1; i >= 0; --i)
    {
        if (strcasecmp(consoleData->history[(size_t)i], commandLine) == 0)
        {
            free(consoleData->history[(size_t)i]);
            consoleData->history.erase(consoleData->history.begin() + i);
            break;
        }
    }

    consoleData->history.push_back(strdup(commandLine));

    // Process the command

    if (strcasecmp(commandLine, "clear") == 0)
    {
        clearLog(consoleData);
    }
    else if (strcasecmp(commandLine, "help") == 0)
    {
        addLog(consoleData, "Commands:");
        for (size_t i = 0; i < consoleData->commands.size(); i++)
            addLog(consoleData, "- %s", consoleData->commands[i]);
    }
    else if (strcasecmp(commandLine, "history") == 0)
    {
        for (size_t i = consoleData->history.size() >= 10 ? consoleData->history.size() - 10 : 0; i < consoleData->history.size(); i++)
            addLog(consoleData, "%3d: %s\n", i, consoleData->history[i]);
    }
    else if (strcasecmp(commandLine, "testText") == 0) // TODO: Temp for testing
    {
        addLog(consoleData, "Some text\nSome more text\nDisplay very important message here!\n");
    }
    else if (strcasecmp(commandLine, "testError") == 0) // TODO: Temp for testing
    {
        addLog(consoleData, "[Error] Something went wrong!\n");
    }
    else if (strcasecmp(commandLine, "testScript") == 0) // TODO: Temp for testing
    {
        consoleData->scripts.push_back((char*)"print(\"Hello ProDBG Lua World!\")");
    }
    else
    {
        addLog(consoleData, "Unknown command: '%s'\n", commandLine);
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void textEditCallbackStub(PDInputTextCallbackData* data)
{
    ConsoleData* consoleData = (ConsoleData*)data->userData;

    //addLog(consoleData, "Cursor: %d, EventKey: %d, Selection: %d-%d", data->cursorPos, data->eventKey, data->selectionStart, data->selectionEnd);

    std::vector<const char*> candidates;
    const char* wordEnd   = nullptr;
    const char* wordStart = nullptr;
    switch (data->eventKey)
    {
        default:
            break;

        // Tab Completion
        case PDKEY_TAB:
        {
            // Locate beginning of current word
            wordEnd   = data->buffer + data->cursorPos;
            wordStart = wordEnd;
            while (wordStart > data->buffer)
            {
                const char c = wordStart[-1];
                if (c == ' ' || c == '\t' || c == ',' || c == ';')
                    break;
                wordStart--;
            }

            // Build a list of candidates

            for (size_t i = 0; i < consoleData->commands.size(); ++i)
                if (strncasecmp(consoleData->commands[i], wordStart, (size_t)(int(wordEnd - wordStart))) == 0)
                    candidates.push_back(consoleData->commands[i]);




            if (candidates.size() == 0)
            {
                // No match
                addLog(consoleData, "No match for \"%.*s\"!\n", wordEnd - wordStart, wordStart);
            }
            else if (candidates.size() == 1)
            {
                // Single match. Delete the beginning of the word and replace it entirely so we've got nice casing

                data->deleteChars(data, int(wordStart - data->buffer), int(wordEnd - wordStart));
                data->insertChars(data, data->cursorPos, candidates[0], 0);
                data->insertChars(data, data->cursorPos, " ", 0);
            }
            else
            {
                // Multiple matches. Complete as much as we can, so inputing "C" will complete to "CL" and display "CLEAR" and "CLASSIFY"
                int matchLen = int(wordEnd - wordStart);
                while (true)
                {
                    int c = 0;
                    bool allCandidatesMatches = true;
                    for (size_t i = 0; i < candidates.size() && allCandidatesMatches; i++)
                    {
                        if (i == 0)
                            c = toupper(candidates[i][matchLen]);
                        else if (c != toupper(candidates[i][matchLen]))
                            allCandidatesMatches = false;
                    }

                    if (!allCandidatesMatches)
                        break;

                    matchLen++;
                }

                if (matchLen > 0)
                {
                    data->deleteChars(data, int(wordStart - data->buffer), int(wordEnd - wordStart));
                    data->insertChars(data, data->cursorPos, candidates[0], candidates[0] + matchLen);
                }

                // List matches
                addLog(consoleData, "Possible matches:\n");
                for (size_t i = 0; i < candidates.size(); i++)
                    addLog(consoleData, "- %s\n", candidates[i]);
            }

            break;
        }

        // Command History
        case PDKEY_UP:
        case PDKEY_DOWN:
        {
            const int prevHistoryPos = consoleData->historyPos;
            if (data->eventKey == PDKEY_UP)
            {
                if (consoleData->historyPos == -1)
                    consoleData->historyPos = int(consoleData->history.size()) - 1;
                else if (consoleData->historyPos > 0)
                    consoleData->historyPos--;
            }
            else if (data->eventKey == PDKEY_DOWN)
            {
                if (consoleData->historyPos != -1)
                {
                    if (++consoleData->historyPos >= int(consoleData->history.size()))
                        consoleData->historyPos = -1;
                }
            }

            // TODO: A better implementation would preserve the data on the current input line along with cursor position
            if (prevHistoryPos != consoleData->historyPos)
            {
                strcpy(data->buffer, (consoleData->historyPos >= 0) ? consoleData->history[(size_t)consoleData->historyPos] : "");
                data->bufferDirty = true;
                data->cursorPos = data->selectionStart = data->selectionEnd = int(strlen(data->buffer));
            }

            break;
        }
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void* createInstance(PDUI* uiFuncs, ServiceFunc* serviceFunc)
{
    (void)serviceFunc;
    (void)uiFuncs;

    ConsoleData* consoleData = new ConsoleData;
    clearLog(consoleData);

    consoleData->historyPos = -1;
    consoleData->commands.push_back((char*)"HELP");
    consoleData->commands.push_back((char*)"HISTORY");
    consoleData->commands.push_back((char*)"CLEAR");
    consoleData->commands.push_back((char*)"CLASSIFY");   // TODO: "classify" is here to provide an example of "C"+[tab] completing to "CL" and displaying matches.
    consoleData->commands.push_back((char*)"TESTTEXT");   // TODO: Temp, for testing
    consoleData->commands.push_back((char*)"TESTERROR");  // TODO: Temp, for testing
    consoleData->commands.push_back((char*)"TESTSCRIPT"); // TODO: Temp, for testing

    return consoleData;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void destroyInstance(void* userData)
{
    ConsoleData* consoleData = (ConsoleData*)userData;
    clearLog(consoleData);
    free(consoleData);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void showInUI(ConsoleData* consoleData, PDReader* reader, PDUI* uiFuncs)
{
    (void)consoleData;
    (void)reader;

    uiFuncs->textWrapped("ProDBG Scripting Console");
    uiFuncs->textWrapped("Enter 'HELP' for help. Press TAB to use text completion.");

    // TODO: display from bottom
    // TODO: clip manually

    if (PDUI_buttonSmall(uiFuncs, "Clear"))
        clearLog(consoleData);

    uiFuncs->sameLine(0, -1);
    uiFuncs->separator();

    PDVec2 pad = { 0.0f, 0.0f };

    uiFuncs->pushStyleVarV(PDStyleVar_FramePadding, pad);

    //static ImGuiTextFilter filter;
    //filter.Draw("Filter (\"incl,-excl\") (\"error\")", 180);

    if (uiFuncs->isItemHovered())
        uiFuncs->setKeyboardFocusHere(-1); // Auto focus on hover

    uiFuncs->popStyleVar(1);

    uiFuncs->separator();

    PDVec2 spacing = { 0, -uiFuncs->getTextLineSpacing() * 2 };
    PDVec2 itemSpacing = { 4.0f, 1.0f };

    uiFuncs->beginChild("ScrollingRegion", spacing, false, PDWindowFlags(0));
    uiFuncs->pushStyleVarV(PDStyleVar_ItemSpacing, itemSpacing); // Tighten spacing

    for (size_t i = 0; i < consoleData->items.size(); i++)
    {
        const char* item = consoleData->items[i];
        //if (!filter.PassFilter(item))
        //    continue;
        PDVec4 col = { 1.0f, 1.0f, 1.0f, 1.0f }; // A better implementation may store a type per-item. For now let's just parse the text.
        if (strstr(item, "[Error]"))
            col = { 1.0f, 0.4f, 0.4f, 1.0f };
        else if (strncmp(item, "# ", 2) == 0)
            col = { 1.0f, 0.8f, 0.6f, 1.0f };
        uiFuncs->textColored(col, item);
    }

    if (consoleData->scrollToBottom)
        uiFuncs->setScrollHere();

    consoleData->scrollToBottom = false;

    uiFuncs->popStyleVar(1);
    uiFuncs->endChild();
    uiFuncs->separator();

    // Command Line

    if (uiFuncs->inputText("Input", consoleData->inputBuffer, sizeof(consoleData->inputBuffer), PDInputTextFlags_EnterReturnsTrue | PDInputTextFlags_CallbackCompletion | PDInputTextFlags_CallbackHistory, &textEditCallbackStub, (void*)consoleData))
    {
        char* inputEnd = consoleData->inputBuffer + strlen(consoleData->inputBuffer);

        while (inputEnd > consoleData->inputBuffer && inputEnd[-1] == ' ')
            inputEnd--;

        *inputEnd = 0;

        if (consoleData->inputBuffer[0])
            execCommand(consoleData, consoleData->inputBuffer);

        strcpy(consoleData->inputBuffer, "");
    }

    if (uiFuncs->isItemHovered())
        uiFuncs->setKeyboardFocusHere(-1); // Auto focus on hover
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int update(void* userData, PDUI* uiFuncs, PDReader* inEvents, PDWriter* outEvents)
{
    ConsoleData* consoleData = (ConsoleData*)userData;

    uint32_t event = 0;
    (void)event;

    // test working build

    /*while ((event = PDRead_getEvent(inEvents)) != 0)
       {
        switch (event)
        {
            case PDEventType_setConsole:
            {
                //showInUI((ConsoleData*)userData, inEvents, uiFuncs);
                break;
            }
        }
       }*/

    showInUI(consoleData, inEvents, uiFuncs);


    for (size_t i = 0; i < consoleData->scripts.size(); ++i)
    {
        PDWrite_eventBegin(outEvents, PDEventType_executeConsole);
        PDWrite_string(outEvents, "command", consoleData->scripts[i]);   // TODO: Remove me
        PDWrite_eventEnd(outEvents);
        //free(consoleData->scripts[i]);
    }

    consoleData->scripts.clear();

    // Request console data

    PDWrite_eventBegin(outEvents, PDEventType_getConsole);
    PDWrite_u8(outEvents, "dummy_remove", 0);   // TODO: Remove me
    PDWrite_eventEnd(outEvents);

    return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static PDViewPlugin plugin =
{
    "Console",
    createInstance,
    destroyInstance,
    update,
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern "C"
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    PD_EXPORT void InitPlugin(RegisterPlugin* registerPlugin, void* privateData)
    {
        registerPlugin(PD_VIEW_API_VERSION, &plugin, privateData);
    }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}


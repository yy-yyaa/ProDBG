#pragma once

#include "api/include/pd_ui.h"
#include "core/math.h"

struct PDReader;
struct PDWriter;
struct PDViewPlugin;
struct PDBackendPlugin;
struct PluginData;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct ViewPluginInstance
{
    PDUI ui;
    PDViewPlugin* plugin;
    IntRect rect;
    void* userData;
    const char* name;
    int count;
    bool markDeleted;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct PluginUI
{
    enum State
    {
        None,
        CloseView,
    };

    ViewPluginInstance* createViewPlugin(PluginData* pluginData);

    virtual void create(void* window, int width, int height) = 0;
    virtual void destroy() = 0;

    virtual void init(ViewPluginInstance* instance) = 0;
    virtual State updateInstance(ViewPluginInstance* instance, PDReader* reader, PDWriter* writer) = 0;

    virtual void preUpdate() = 0;
    virtual void postUpdate() = 0;

    // Statusbar functions

    virtual void setStatusText(const char* format, ...);

    virtual void setStatusTextNoFormat(const char* text) = 0;
    virtual float getStatusBarSize() = 0;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern PluginUI* g_pluginUI;


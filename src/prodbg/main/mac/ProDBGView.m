#import "ProDBGView.h"
#include <CoreFoundation/CoreFoundation.h>
#include <Carbon/Carbon.h>

NSOpenGLContext* g_context = 0;
NSWindow* g_window = 0;

void Window_setTitle(const char* title);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Scan codes on Mac taken from http://boredzo.org/blog/archives/2007-05-22/virtual-key-codes

#define KEY_RETURN 36
#define KEY_TAB 48
#define KEY_DELETE 51
#define KEY_ESCAPE 53

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

@interface MyMenuItem : NSMenuItem 
{
}
- (BOOL)isHighlighted;
@end

@implementation MyMenuItem
- (BOOL)isHighlighted
{
	return NO;
}
@end

@implementation ProDBGView

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

-(void) updateEditor
{
	///
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

- (id)initWithFrame:(NSRect)frame 
{
	self = [super initWithFrame:frame];
	if (self == nil)
		return nil;

	NSOpenGLPixelFormatAttribute attributes[4];

	attributes[0] = NSOpenGLPFADoubleBuffer;
	attributes[1] = 0;

	NSOpenGLPixelFormat* format = [[NSOpenGLPixelFormat alloc] initWithAttributes:attributes];
	oglContext = [[NSOpenGLContext alloc] initWithFormat:format shareContext:nil];
	[oglContext makeCurrentContext];

	g_context = oglContext;
	g_window = [self window];

	const float framerate = 60;
	const float frequency = 1.0f/framerate;
	[NSTimer scheduledTimerWithTimeInterval:frequency
									 target:self selector:@selector(updateEditor)
								   userInfo:nil repeats:YES];

	return self;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

- (void)lockFocus
{
	NSOpenGLContext* context = oglContext;

	[super lockFocus];

	if ([context view] != self) 
		[context setView:self];

	[context makeCurrentContext];
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

- (void)drawRect:(NSRect)frameRect 
{
	[oglContext update];
	g_window = [self window];

	//EMGFXBackend_updateViewPort((int)frameRect.size.width, (int)frameRect.size.height);
	//Editor_setWindowSize((int)frameRect.size.width, (int)frameRect.size.height);
	//Editor_update();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int getModifierFlags(int flags)
{
	int specialKeys = 0;
	/*
	if (flags & NSShiftKeyMask)
		specialKeys |= EMGUI_KEY_SHIFT;

	if (flags & NSAlternateKeyMask)
		specialKeys |= EMGUI_KEY_ALT;

	if (flags & NSControlKeyMask)
		specialKeys |= EMGUI_KEY_CTRL;

	if (flags & NSCommandKeyMask)
		specialKeys |= EMGUI_KEY_COMMAND;
	*/

	return specialKeys;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

- (void)keyDown:(NSEvent *)theEvent 
{
	NSString* key = [theEvent charactersIgnoringModifiers];
	unichar keyChar = 0;
	if ([key length] == 0)
		return;

	keyChar = [key characterAtIndex:0];

	int keyCode = keyChar;
	int specialKeys = getModifierFlags([theEvent modifierFlags]);

	/*

	if ([theEvent modifierFlags] & NSNumericPadKeyMask) 
	{ 
		switch (keyChar)
		{
			case NSLeftArrowFunctionKey: keyCode = EMGUI_KEY_ARROW_LEFT; break;
			case NSRightArrowFunctionKey: keyCode = EMGUI_KEY_ARROW_RIGHT; break;
			case NSUpArrowFunctionKey: keyCode = EMGUI_KEY_ARROW_UP; break;
			case NSDownArrowFunctionKey: keyCode = EMGUI_KEY_ARROW_DOWN; break;
		}
	}
    else
    {
        switch ([theEvent keyCode])
        {
            case KEY_TAB : keyCode = EMGUI_KEY_TAB; break;
            case KEY_DELETE : keyCode = EMGUI_KEY_BACKSPACE; break;
            case KEY_RETURN : keyCode = EMGUI_KEY_ENTER; break;
            case KEY_ESCAPE : keyCode = EMGUI_KEY_ESC; break;
			case NSPageDownFunctionKey: keyCode = EMGUI_KEY_PAGE_DOWN; break;
			case NSPageUpFunctionKey: keyCode = EMGUI_KEY_PAGE_UP; break;
        }
    }

	Emgui_sendKeyinput(keyCode, specialKeys);

	if (!Editor_keyDown(keyCode, [theEvent keyCode], specialKeys))
    	[super keyDown:theEvent];

	Editor_update();
	*/
}
 
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

- (BOOL)acceptsFirstResponder 
{
    return YES;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

-(void) viewWillMoveToWindow:(NSWindow *)newWindow 
{
    NSTrackingArea* trackingArea = [[NSTrackingArea alloc] initWithRect:[self frame] 
    	options: (NSTrackingMouseMoved | NSTrackingActiveAlways) owner:self userInfo:nil];
    [self addTrackingArea:trackingArea];
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

- (void)mouseMoved:(NSEvent *)event
{
	NSWindow* window = [self window];
	NSRect originalFrame = [window frame];
	NSPoint location = [window mouseLocationOutsideOfEventStream];
	NSRect adjustFrame = [NSWindow contentRectForFrameRect: originalFrame styleMask: NSTitledWindowMask];

	//Emgui_setMousePos((int)location.x, (int)adjustFrame.size.height - (int)location.y);
	//Editor_update();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

- (void)mouseDragged:(NSEvent *)event
{
	NSWindow* window = [self window];
	NSRect originalFrame = [window frame];
	NSPoint location = [window mouseLocationOutsideOfEventStream];
	NSRect adjustFrame = [NSWindow contentRectForFrameRect: originalFrame styleMask: NSTitledWindowMask];

	//Emgui_setMousePos((int)location.x, (int)adjustFrame.size.height - (int)location.y);
	//Editor_update();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

- (void)scrollWheel:(NSEvent *)theEvent
{
	float x = (float)[theEvent deltaX];
	float y = (float)[theEvent deltaY];
	int flags = getModifierFlags([theEvent modifierFlags]);

	//printf("%f %f %d\n", x, y, flags);
	//Editor_scroll(-x, -y, flags);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

- (void)mouseUp:(NSEvent *)event
{
	//Emgui_setMouseLmb(0);
	//Editor_update();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

- (void)mouseDown:(NSEvent *)event
{
	NSWindow *window = [self window];
	NSRect originalFrame = [window frame];
	NSPoint location = [window mouseLocationOutsideOfEventStream];
	NSRect adjustFrame = [NSWindow contentRectForFrameRect: originalFrame styleMask: NSTitledWindowMask];

	//Emgui_setMousePos((int)location.x, (int)adjustFrame.size.height - (int)location.y);
	//Emgui_setMouseLmb(1);
	//Editor_update();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

-(BOOL) isOpaque 
{
    return YES;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

- (void)onMenuPress:(id)sender 
{
	int id = (int)((NSButton*)sender).tag;
	(void)id;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Window_buildMenu()
{
	Window_setTitle("ProDBG" "0.1");
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Window_populateRecentList(const char** files)
{
	/*
 	NSMenu* fileMenu = [[[NSApp mainMenu] itemWithTitle:@"File"] submenu];
	NSMenu* recentItems = [[fileMenu itemWithTitle:@"Recent Files"] submenu];

	[recentItems removeAllItems];

	for (int i = 0; i < 4; ++i)
	{
		const char* filename = files[i];

		if (!strcmp(filename, ""))
			continue;

		NSString* name = [NSString stringWithUTF8String: filename];

		NSMenuItem* newItem = [[NSMenuItem alloc] initWithTitle:name action:@selector(onMenuPress:) keyEquivalent:@""];
		[newItem setTag:EDITOR_MENU_RECENT_FILE_0 + i];
		[newItem setRepresentedObject:[NSString stringWithFormat:@"%d",i]];
		[newItem setKeyEquivalentModifierMask: NSCommandKeyMask];
		[newItem setKeyEquivalent:[NSString stringWithFormat:@"%d",i + 1]];

		[recentItems addItem:newItem];

		[newItem release];
	}
	*/
}

@end

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

void swapBuffers()
{
	[g_context flushBuffer];
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Window_setTitle(const char* title)
{
	[g_window setTitle:[NSString stringWithUTF8String:title]];
}



gcc main.c -I/opt/homebrew/include -L/opt/homebrew/lib -lSDL2 -o main
g++ main.cpp -I/opt/homebrew/include -L/opt/homebrew/lib -lSDL2 -o main


# int SDL_Init(uint32_t flags);
| It initializes the various systems of the SDL2 library,
`   `crucial to call this function before using most other SDL2 functions.
| Parameter **flags**:
`   `|| can be specified with bitwise OR **|** combination.
| Return Value:
`   `|| **0** on success.
`   `|| **-1** on error.
`       `You can use **SDL_GetError()** to get a text description of the error.
| Example:
```cpp
    if ( SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0 ) {
        std::cerr << "Error initializing SDL2: " << SDL_GetError() << std::endl;
        ...
    }
```
| You can also use **SDL_InitSubSystem( flags )** and to initialize subsystems one by one, 
`   `but then you have to manually free each one via **SDL_QuitSubSystem( flags )**,
`   `the **flags** are the same as **SDL_Init( flags )**.

| Flags | Description |
| :-- | :-- |
| SDL_INIT_TIMER | Timer management. |
| | |
| SDL_INIT_AUDIO | Audio output and loading. |
| | |
| SDL_INIT_VIDEO | Graphics, window creation, and rendering. |
| | |
| SDL_INIT_JOYSTICK | Joystick / Gamepad support. |
| | |
| SDL_INIT_HAPTIC | Force feedback with supported devices. |
| | |
| SDL_INIT_GAMECONTROLLER | Simplified gamepad support. |
| | |
| SDL_INIT_EVENTS | Event polling. |
| | |
| SDL_INIT_EVERYTHING | Initialize all of the above commonly used subsystems. |


# VIDEO Subsystem
| Graphics Drivers:
`   `|| SDL communicates with your OS to detect and establish communication with compatible graphics drivers.

| Windowing System Integration:
`   `|| SDL interacts with the underlying windowing system (X11 on Linux, Windows API, Cocoa on MacOS) 
`       `to enable window creation and management.

| Hardware Acceleration:
`   `|| If available, SDL will try to set up hardware-accelerated rendering using APIs like OpenGL, DirectX or Vulkan.

| Default Renderer:
`   `|| SDL creates a default software renderer if hardware acceleration isn't available or fails to initialize.


# AUDIO Subsystem
| Audio Device Detection:
`   `|| SDL scans your system for available audio output devices (sound card, speakers, headphones).

| Audio Formats:
`   `|| SDL determines supported audio formats, sample rates, and number of audio channels.

| Mixing Buffers:
`   `|| SDL sets up internal audio mixing buffers for handling sound output.

| Callback Mechanism (optional):
`   `|| If you plan to use SDL's audio callback system for dynamic sound generation, 
`       `the necessary infrastructure is set up.


# void SDL_Quit(void);
| When you're done with SDL2, call it to clean up all initialized subsystems.
| Unlike **SDL_QuitSubSystem( )**, only call **SDL_Quit()** once!!


# SDL_CreateWindow( )
| Purpose:
`   `|| It creates a window in which you'll render your game graphics, user interface, or anything you want to display.
| Signature:
`   `|| SDL_Window * SDL_CreateWindow(const char * title,
`                                    `int x, int y,
`                                    `int w, int h,
`                                    `Uint32 flags);
| @param **title**:
`   `|| The title to be displayed in the window's title bar.
| @param **x**:
| @param **y**:
`   `|| The X- and Y-coordinate of the window's top-left corner.
`   `|| Special values: **SDL_WINDOWPOS_UNDEFINED**, **SDL_WINDOWPOS_CENTERED**
`   `|| Otherwise you can provide any integer value to specify the exact pixel coordinate,
`       `the origin **(x=0, y=0)** is the top-left corner of your primary display,
`       `positive **x** values move rightwards, positive **y** values move downwards.
| @param **w**:
| @param **h**:
`   `|| The width and height of the window in pixels.
| @param **flags**:

| Flags | Description |
| :-- | :-- |
| SDL_WINDOW_SHOWN | The window is created as a visible window. |
| | |
| SDL_WINDOW_HIDDEN | The window is initially hidden. |
| | |
| SDL_WINDOW_FULLSCREEN | Fullscreen window. |
| | |
| SDL_WINDOW_OPENGL | Create a window for OpenGL rendering. |
| | |
| SDL_WINDOW_VULKAN | Create a window for Vulkan rendering. |


| Return Value:
`   `|| __SDL_Window *__ which is a pointer to the newly created window.
`   `|| **NULL** if the window failed to create.

| Important Notes:
`   `|| Ensure that the video subsystems **SDL_INIT_VIDEO** is initalized before calling this function.
`   `|| You'll need to create an **SDL_Renderer** associated with this window for actual drawing.
`   `|| Call **SDL_DestroyWindow( )** to destroy the window when finished.


# SDL_DestroyWindow( )
| Purpose:
`   `|| Responsible for destroying a window you previously created with **SDL_CreateWindow( )**.
`   `|| It frees up all the resources associated with the window, 
`       `like memory used by the window's internal data structures, system resources like graphics handles.
`   `|| If you created a renderer associated with the window using **SDL_CreateRenderer( )**,
`       `that renderer is also destroyed automatically.
`   `|| Any pending events related to the destroyed window are also removed from the SDL event queue.
| Signature:
`   `|| void SDL_DestroyWindow(SDL_Window * window);
| @param **window**:
`   `|| A pointer to the window you want to destroy.

| Important Notes:
`   `|| The function is designed to handle **NULL** pointers, thus it's NULL-pointer-safe.
`   `|| Be sure to call it before **SDL_Quit()**!!


# SDL_GetWindowSurface( )
| Purpose:
`   `|| To get a software-based rendering surface directly associated with an SDL window,
`       `this surface represents the area of the window where you can draw.
| Signature:
`   `|| SDL_Surface * SDL_GetWindowSurface( SDL_Window * window );
| @param **window**:
`   `|| A pointer to the SDL window for which you want to retrieve the surface.

| Return Value:
`   `|| __SDL_Surface *__ which is a pointer to the window's surface.
`   `|| **NULL** on error, you can use **SDL_GetError()** to have more information.

| Important Notes:
`   `|| The returned **SDL_Surface** is typically used for software rendering, 
`       `which means the CPU will be doing the drawing work.
`   `|| If you're using hardare-accelerated rendering (OpenGL, Vulkan, etc),
`       `this function is generally not what you need.
`   `|| The surface returned by this function is managed internally by SDL,
`       `don't attempt to free it with **SDL_FreeSurface( )** if returned from this function.
`   `|| If the window is resized or the contents are obsecured, the surface can become invalid.
`       `You'll often call **SDL_UpdateWindowSurface( )** after drawing to get the contents to display.
`   `|| You cannot directly mix the use of **SDL_GetWindowSurface( )**
`       `with rendering APIs like OpenGL or Vulkan on the same window.

| Example:
```cpp
    SDL_Window * window = SDL_CreateWindow( "Example Window", ... );
    SDL_Surface * windowSurface = SDL_GetWindowSurface( window );
    
    // lock the surface for direct pixel access (if needed).
    SDL_LockSurface( windowSurface );
    ...
    // .. modifying pixel data...
    ...
    // unlock the surface.
    SDL_UnlockSurface( windowSurface );

    // update the window to display changes.
    SDL_UpdateWindowSurface( window );
```

# SDL_LockSurface( ) AND SDL_UnlockSurface( )
| Purpose:
`   `|| It provides a mechanism to directly access the raw pixel data of an **SDL_Surface**.
`   `|| This is often needed if you wish to perform the following:
`       `1. Fast Pixel Manipulation: modify the image data of a surface 
`           `with direct memory manipulation techniques for maximum efficiency.
`       `2. Custom Drawing Operations: implement your own drawing algorithms 
`           `that require modifying individual pixels.
| Signature:
`   `|| int SDL_LockSurface( SDL_Surface * surface );
`   `|| void SDL_UnlockSurface( SDL_Surface * surface );
| @param **surface**:
`   `|| A pointer to the **SDL_Surface** you want to lock / unlock.

| Return Value of **SDL_LockSurface( )**:
`   `|| **0** on success.
`   `|| __<0__ on failure, you can use **SDL_GetError()** to get an human-readable error message.

| Important Notes:
`   `|| Always remember to call **SDL_UnlockSurface( SDL_Surface * surface );** 
`       `after you finish modifying a locked surface.
`   `|| Understanding the pixel format **SDL_PixelFormat** of your surface is crucial when manipulating raw pixel data.

| Example:
```c
    SDL_Surface * image = SDL_LoadBMP( "test.bmp" );
    if ( !image ) {
        // handling error...
    }
    if ( SDL_LockSurface(image)<0 ) {
        // handling error...
    } else {
        ...
        // access pixel data, the `->pixels` is a `void*` originally:
        Uint32 * pixels = (Uint32 *)image->pixels;
        // make changes to pixel data...
        ...
        SDL_UnlockSurface(image);
    }
```


# SDL_FillRect( )
| Purpose:
`   `|| Provides a simple and efficient way to draw a filled rectangle on an SDL rendering surface.
| Signature:
`   `|| int SDL_FillRect( SDL_Surface * dst,
`                       ` const SDL_Rect * rect,
`                       ` Uint32 color);
| @param **dst**:
`   `|| The destination surface where you want to draw the rectangle.
| @param **rect**:
`   `|| A pointer to an **SDL_Rect** structure defining the are to be filled.
| @param **color**:
`   `|| The color to fill the rectangle with, 
`       `must be in a format that's compatible with the pixel format of the dst surface.

| Return Value:
`   `|| **0** on success.
`   `|| **<0** on failure, use **SDL_GetError()** for more information.

| Important Notes:
`   `|| If you're using **SDL_GetWindowSurface( )**, 
`       `you often need to call **SDL_UpdateWindowSurface( )** afterwards to have the change display on the screen.
`   `|| If you're using a hardware-accelerated renderer **SDL_CreateRenderer( )** things,
`       `there's often a counterpart function like **SDL_RenderFillRect( )**.
`   `|| The rectangle might be modified or not drawn at all if it falls entirely outside the clip region.

| Example:
```c
    SDL_Surface * screen = SDL_GetWindowSurface( window );
    SDL_Rect rect = {
        100, 50,    // <- (x, y)
        200, 100    // <- (w, h)
    };
    Uint32 red = SDL_MapRGB(screen->format, 255, 0, 0);
    SDL_FillRect(screen, &rect, red);
    SDL_UpdateWindowSurface( window );
```


# SDL_MapRGB( )
| Purpose:
`   `|| An untility function that translates separate R,G,B color component values into a packed pixel value,
`       `which is suitable for a specific pixel format.
| Signature:
`   `|| Uint32 SDL_MapRGB( const SDL_PixelFormat * format,
`                         `Uint8 r, Uint8 g, Uint8 b);
| @param **format**:
`   `|| Describes the pixel format you want to map the color to.
| @param **r**:
| @param **g**:
| @param **b**:
`   `|| Color value typically between 0 and 255, both inclusive.


# SDL_UpdateWindowSurface( )
| Purpose:
`   `|| It copies the modified contents of a window's surface to the actual display.
| Signature:
`   `|| int SDL_UpdateWindowSurface( SDL_Window * window );
| @param **window**:
`   `|| The window whose surface you want to update on the display.

| Return Value:
`   `|| **0** on success.
`   `|| **<0** on failure, use **SDL_GetError()** for more information.

| Important Notes:
`   `|| The update might not always happen instantly,
`       `it may depend on the rendering method and internal buffering.
`   `|| This function is primarily used in the context of software rendering,
`       `with hardware-accelerated rendering **SDL_Renderer** things updating screen is often handled more implicitly.


# SDL_PollEvent( )
| Purpose:
`   `|| Is at the heart of the SDL's event-driven model.
`   `|| It will remove an event if avaible in the event queue.
| Signature:
`   `|| int SDL_PollEvent( SDL_Event * event );
| @param **event**:
`   `|| A pointer to an existing **SDL_Event** structure,
`       `in which SDL will fill with information about the retrieved event.

| Return Value:
`   `|| **1** if an event was retrieved and placed into the {@param **event**} structure.
`   `|| **0** if there're currently no events in the queue.

| Important Notes:
`   `|| It is typically used within a game loop or an event loop.
`   `|| Non-Blocking: It doesn't block your program's execution if there're no events,
`       `so just remember to continuously check for new events.
`   `|| The **SDL_Event** structure has a **type** member, 
`       `inspect this to determine what kind of event has occurred.
`   `|| It retrieves the *least recent* event from the event queue!!

| Example:
```cpp
    bool running = true;
    SDL_Event event;
    do {
        while ( SDL_PollEvent(&event) ) {
            if ( event.type == SDL_QUIT ) {
                running = false;
            } else if ( event.type == SDL_KEYDOWN ) {
                ...
            }
            ...
        }
    } while ( running );
```


# SDL_PumpEvents( )
| Purpose:
`   `|| This processes pending events from the operating system's event queue. 
`       `This includes keyboard presses, mouse clicks, window resizing, joystick events, and more.
`   `|| It pulls these events into SDL's internal event queue, 
`       `making them available for your game to respond to.
| Signature:
`   `|| void SDL_PumpEvents(void);

| Example:
```cpp
    bool running = true;
    SDL_Event event;
    while (running) {
        SDL_PumpEvents(); // update the event queue.
        while ( SDL_PollEvent(&event) ) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
            ...
        }
        ...
    }
    ...
```


# SDL_LoadBMP( )
| Purpose:
`   `|| Provides a straightforward way to load specifically BMP (bitmap) image files,
`       `and convert them into **SDL_Surface** structures.
| Signature:
`   `|| SDL_Surface * SDL_LoadBMP(const char * filename);
| @param **filename**:
`   `|| A string representing the path to the BMP image file to load.

| Return Value:
`   `|| __SDL_Surface *__ on success.
`   `|| **NULL** on error, get more information with **SDL_GetError()**.

| Important Notes:
`   `|| This function is BMP-Only!!
`   `|| For other image formats (PNG, JPG, etc.), 
`       `you'll often use the **SDL_image.h** extension library along with functions like **IMG_Load( )**.
`   `|| The **SDL_Surface** that it returns may not have the same pixel format as your display,
`       `so it's often converted to an optimized format compatible with your display for efficient rendering.


# SDL_BlitSurface( )
| Purpose:
`   `|| Provides a fast and flexible way to copy the pixels of one SDL surface onto another.
| Signature:
`   `|| int SDL_BlitSurface( SDL_Surface * src, const SDL_Rect * srcrect
`                            `SDL_Surface * dst, const SDL_Rect * dstrect);
| @param **src**: 
`   `|| Pointer to the source surface containing the pixels you want to copy.
| @param **srcrect**: 
`   `|| A pointer to the rectangle defining the region within the source surface to copy.
`   `|| If **NULL**, the entire source surface is used.
| @param **dst**: 
`   `|| Pointer to the destination surface where pixels will be copied.
| @param **dstrect**: 
`   `|| A pointer to a rectangle defined in the position on the destination surface,
`       `where the image should be blitted (copied), only the **x** and **y** matters.
`   `|| If **NULL**, it copies to **(0,0)**.

| Return Value:
`   `|| **0** on success.
`   `|| **<0** on failure, use **SDL_GetError()** for more information.

| Important Notes:
`   `|| The term "blit" came from older graphics terminology (BitBLT - Bit Block Transfer),
`       `which means to copy a block of pixels.
`   `|| You can control both the source and destination regions, 
`       `allowing for scaling and partial copying.
`   `|| It modifies the destination surface but doesn't automatically render it,
`       `you may still need **SDL_UpdateWindowSurface( )** 
`       `or rendering functions when working with a window surface.


# SDL_BlitScaled( )
| Purpose:
`   `|| A specialized version of **SDL_BlitSurface( )** that performs,
`       `both copying and scaling of the source surface onto the destination.
| Signature:
`   `|| int SDL_BlitScaled( SDL_Surface * src, const SDL_Rect * srcrect
`                           `SDL_Surface * dst, SDL_Rect * dstrect);
| @param **src**: 
`   `|| Pointer to the source surface containing the pixels you want to copy.
| @param **srcrect**: 
`   `|| A pointer to the rectangle defining the region within the source surface to copy.
`   `|| If **NULL**, the entire source surface is used.
| @param **dst**: 
`   `|| Pointer to the destination surface where the scaled image will be drawn.
| @param **dstrect**: 
`   `|| A pointer to a rectangle defined in the position on the destination surface,
`       `where the image should be blitted (copied), could be scaled..
`   `|| If **NULL**, it copies to the entire screen.

| Return Value:
`   `|| **0** on success.
`   `|| **<0** on failure, use **SDL_GetError()** for more information.

| Important Notes:
`   `|| It internally performs scaling calculations.


# SDL_PushEvent( )
| Purpose:
`   `|| Allows you to add your own custom events or certain standard events into SDL's internal event queue.
| Signature:
`   `|| int SDL_PushEvent( SDL_Event * event );
| @param **event**:
`   `|| A pointer to a properly initalized **SDL_Event** structure, the **type** member must be set.

| Return Value:
`   `|| **1** on success.
`   `|| **-1** on error. A common error is that the event queue is full.

| Important Notes:
`   `|| It is considered thread-safe, making it useful for communication between threads in your program.

| Example:
```cpp
    struct MyCustomStruct {
        char * filePath;
        int    resourceNumber;
        void * resource;
    };
    
    MyCustomStruct * data = new MyCustomStruct(...);
    
    SDL_Event event;
    event.type = SDL_USEREVENT;
    event.user.code = 2;
    event.user.data1 = data;
    event.user.data2 = NULL;

    SDL_PushEvent( &event );
```


# SDL_PeepEvents( )
| Purpose:
`   `|| It allows you to check the event queue for messages,
`       `and optionally remove them without having to immediately handle them.
| Signature:
`   `|| int SDL_PeepEvents( SDL_Event * events, int numevents,
`                           `SDL_eventaction action,
`                           `Uint32 minType, Uint32 maxType);
| @param **events**:
`   `|| An array of **SDL_Event** structures to be filled 
`       `with the events that are retrieved from the event queue.
| @param **numevents**:
`   `|| The number of events to be retrieved from the event queue,
`       `must be smaller than or equal to the size of the **events** array.
| @param **action**:
`   `|| **SDL_ADDEVENT** to add events to the back of the event queue.
`   `|| **SDL_PEEKEVENT** to peek at the events in the queue but does not remove them.
`   `|| **SDL_GETEVENT** to retrieve and remove them from the event queue.
| @param **minType**:
| @param **maxType**:
`   `|| The minimum and maximum event type values to be considered when fetching from the queue.
`   `|| If you want to fetch all event types, use **SDL_FIRSTEVENT** and **SDL_LASTEVENT**.

| Return Value:
`   `|| **>=0** the number of events retrieved on success.
`   `|| **-1** on error.

| Example:
```cpp
    SDL_Event events[10];
    int nEvents = SDL_PeepEvents(
        events, 10,
        SDL_PEEKEVENT,
        SDL_KEYDOWN, SDL_KEYDOWN
    );
    for (int i = 0; i < nEvents; i++) {
        if (events[i].types == SDL_KEYDOWN) {
            SDL_Log("Keydown event detected %d\n", event[i].key.keysym.sym);
        }
    }
```


# SDL_WaitEvent( ) and SDL_WaitEventTimeout( )
| Purpose:
`   `|| To handle events in a blockingwise way.
`   `|| Useful when you want your application to wait for events without consuming CPU resources unnecessarily.
| Signature:
`   `|| int SDL_WaitEvent( SDL_Event * event );
`   `|| int SDL_WaitEventTimeout( SDL_Event * event, int milisec );

| Return Value:
`   `|| **1** on successfully retrieve an event.
`   `|| **0** on error or timeout, use **SDL_GetError()** for more information.

| Example:
```cpp
    SDL_Event event;
    while ( SDL_WaitEvent(&event) ) {
        if (event.tupe == SDL_QUIT) {
            break;
        }
    }
    // ----
    SDL_Event event;
    while ( 1 ) {
        if ( SDL_WaitEvent(&event, 5000) ) {
            if (event.tupe == SDL_QUIT) {
                break;
            }
        } else {
            ...
        }
    }
```


# SDL_RegisterEvents( )
| Purpose:
`   `|| To dynamically allocate one or more application-defined event types.
| Signature:
`   `|| Uint32 SDL_RegisterEvents(int numevents);
| @param **numevents**:
`   `|| The number of event types you want to register.

| Return Value:
`   `|| Upon success it returns the first event number of the allocated range of event types.
`   `|| **(Uint32)-1** on failure.

| Example:
```cpp
    Uint32 eventBase = SDL_RegisterEvents( 2 );

    #define GAME_OVER_EVENT (eventBase + 0)
    #define LEVEL_COMPLETE_EVENT (eventBase + 1)

    if (eventBase == (Uint32)-1) {
        ...
    }

    ...
    SDL_Event e;
    while ( SDL_PushEvent(&e) ) {
        if (e.type == GAME_OVER_EVENT) {
            ...
        } else if (e.type == LEVEL_COMPLETE_EVENT) {
            ...
        }
    }
    ...

    SDL_Event event;
    SDL_Zero(&event);
    event.type = GAME_OVER_EVENT;
    event.user.code = 123;
    event.user.data1 = NULL;
    event.user.data2 = NULL;
    if (SDL_PushEvent(&event) < 0) {
        ...
    }
```


# SDL_ConvertSurface( )
| Purpose:
`   `|| Optimize a surface for faster and more efficient rendering (blitting) to another surface.
`   `|| It creates a new surface that matches the pixel format of a target surface.
`   `|| This eliminates the need for the graphics hardware to perform costly pixel format conversions 
`       `during every blit operation.
| Signature:
`   `|| SDL_Surface * SDL_ConvertSurface( SDL_Surface * src, 
`                                        `const SDL_PixelFormat * fmt, 
`                                        `Uint32 flags);
| @param **src**:
`   `|| A pointer to the original surface you want to convert.
| @param **fmt**:
`   `|| A pointer to an **SDL_PixelFormat** structure of desired pixel format of the new surface.
| @param **flags**:
`   `|| Additional flags to control the conversion process.
`   `|| The most common flag is **0**, which means no special flags.

| Return Value:
`   `|| A pointer to the newly created, converted surface on success.
`   `|| **NULL** on failure, with **SDL_GetError()** to get more information.

| Important Notes:
`   `|| For memory saving you'd better free the old surface which is used for converting.
`   `|| After using the converted surface you're responsible for freeing it.
`   `|| If the original image's format is already compatible with the target format,
`       `conversion might not be necessary.

| Example:
```cpp
    SDL_PixelFormat * screenFormat = gScreenSurface->format;
    SDL_Surface * optimizedSurface = SDL_ConvertSurface(
        loadedSurface, screenFormat, 0
    );
    if ( !optimizedSurface ) {
        // Error handling...
    }
    SDL_FreeSurface( loadedSurface );
```


# IMG_Init( )
| Purpose:
`   `|| Prepares the *SDL_image.h* library for use 
`       `by initializing support for different image formats like PNG, JPEG, TIFF, ...
`   `|| It internally initializes the subsystems required to handle the supported image formats.
| Signature:
`   `|| int IMG_Init(int flags);
| @param **flags**:
`   `|| A combination of flags using '__|__' to specify which image formats you want to initialize support for.
`   `|| **IMG_INIT_JPG**, **IMG_INIT_PNG**, **IMG_INIT_TIF**, **IMG_INIT_WEBP**, ...

| Return Value:
`   `|| A bitwise combination of successfully initialized flags are returned on success.
`   `|| **0** on failure, use **IMG_GetError()** for more information.

| Important Notes:
`   `|| Call **IMG_Init( )** only once at the beginning of your program,
`       `it is paired with **IMG_Quit()** to clean up the library when you're done.

| Example:
```cpp
    int flags = IMG_INIT_PNG | IMG_INIT_JPG;
    int initializedFlags = IMG_Init( flags );
    if ( flags != (initializedFlags & flags) ) {
        // Error handling...
    }
```


# IMG_Quit()
| Purpose:
`   `|| Cleans up and shuts down the various subsystems and libraries initialized by **IMG_Init( )**.
| Signature:
`   `|| void IMG_Quit();

| Important Notes:
`   `|| Call at the end of your program.
`   `|| Call before **SDL_Quit()**.


# IMG_Load( )
| Purpose:
`   `|| To load various image formats (PNG, JPEG, TIFF, ...) into an __SDL_Surface *__ structure pointer.
`   `|| It determines the file type which to load based on their file extensions.
| Signature:
`   `|| SDL_Surface * IMG_Load( const char * filename );
| @param **filename**:
`   `|| A string representing the path to the image file.

| Return Value:
`   `|| A pointer to the newly loaded and decoded image surface on success.
`   `|| **NULL** on failure, use **IMG_GetError()** for more information.

| Important Notes:
`   `|| Ususally it's recommended to convert the surface to the display format 
`       `using **SDL_ConvertSurface( )** after getting it.


# SDL_SetHint( )
| Purpose:
`   `|| To let you modify hints that control various behaviors and optimizations within the SDL library.a
`   `|| It offers a way to tweak things like **Rendering Quality**, **Mouse Behavior**, **OpenGL Attributes**, ...
| Signature:
`   `|| SDL_bool SDL_SetHint(const char * name, const char * value);
| @param **name**:
`   `|| A string representing the name of the hint you want to set.
| @param **value**:
`   `|| A string representing the desired value for the hint.

| Return Value:
`   `|| **SDL_TRUE** on success.
`   `|| **SDL_FALSE** on failure.

| Important Notes:
`   `|| Environment variables or existing higher-priority hints can override the values you're setting.
`   `|| Use **SDL_SetHintWithPriority( )** if you need to ensure your hints take precedence.

| Common hints and their values:
`   `|| **SDL_HINT_RENDER_SCALE_QUALITY**
`       `**"0"** or **"nearest"** for low-quality, 
`       `**"1"** or **"linear"** for better-quality and **"2"** or **"best"** for highest-quality, might be slower.
`   `|| **SDL_HINT_RENDER_DRIVER**
`       `**"opengl"**, **"opengles"**, **"software"**, **"direct3d"**, etc...
`       `Suggests a preferred rendering backend, the actual backend used might be influenced by hardware.
`   `|| **SDL_HINT_VIDEO_X11_XVIDEOMODE**
`       `**"1"** for enabling and **"0"** for disabling.
`       `On X11 systems, enabling XVideo hardware acceleration for optimized video scaling and color conversion.
`   `|| **SDL_HINT_GRAB_KEYBOARD**
`       `**"1"** for enabling and **"0"** for disabling.
`       `If enabled, grabs keyboard input, 
`       `preventing other applications from receiving it while your SDL window is in focus.
`   `|| **SDL_HINT_MOUSE_FOCUS_CLICKTHROUGH**
`       `**"1"** for enabling and **"0"** for disabling.
`       `Determines if a window should receive mouse clicks even when it doesn't have focus.
`   `|| **SDL_HINT_VIDEO_MINIMIZE_ON_FOCUS_LOSS**
`       `**"1"** for enabling and **"0"** for disabling.
`       `Automatically minimizes the window when it loses focus.
`   `|| **SDL_HINT_AUDIO_RESAMPLING_MODE**
`       `**"0"** or **"nearest"** for low-quality, **"1"** or **"linear"** for better-quality, ...
`       `Similar to the rendering quality hints.


# SDL_SetHintWithPriority( )
| Purpose:
`   `|| Set / Replace hint with priority.
| Signature:
`   `|| SDL_bool SDL_SetHintWithPriority(const char * name, const char * value, SDL_HintPriority prio);
| @param **name**:
`   `|| A string representing the name of the hint you want to set.
| @param **value**:
`   `|| A string representing the desired value for the hint.
| @param **prio**:
`   `|| Coule be **SDL_HINT_DEFAULT**, **SDL_HINT_NORMAL**, **SDL_HINT_OVERRIDE**.


# SDL_CreateRenderer( )
| Purpose:
`   `|| Creates a 2D rendering context within an SDL window.
`   `|| Attempts to choose the most appropriate rendering backend based on your system and flags provided.
| Signature:
`   `|| SDL_Renderer * SDL_CreateRenderer(SDL_Window * window, 
`                                        `int index, 
`                                        `Uint32 flags);
| @param **window**:
`   `|| A pointer to the **SDL_Window** where rendering will take place.
| @param **index**:
`   `|| **-1** tells SDL to automatically choose the first available driver that supports the requested flags.
`   `|| Or you can specify a particular rendering driver if you know its index.
`   `|| Use **SDL_GetNumRenderDrivers()** to get the number of available drivers and see their names beforehand.
| @param **flags**:
`   `|| A combination __'|'__ of flags to control renderer behavior.
`   `|| **SDL_RENDER_SOFTWARE** forces a software renderer.
`   `|| **SDL_RENDER_ACCELERATED** requests hardware acceleration if possible.
`   `|| **SDL_RENDER_PRESENTVSYNC** synchronizes with display refresh rate.
`   `|| **SDL_RENDER_TARGETTEXTURE** allows rendering to a texture for advanced techniques.

| Return Value:
`   `|| A pointer to the newly created **SDL_Renderer** object,
`       `which is used for most drawing commands in SDL.
`   `|| **NULL** on failure, use **SDL_GetError()** for more information.

| Important Notes:
`   `|| Use **SDL_RenderPresent( )** to update the contents of the window.
`   `|| Use **SDL_DestroyRenderer( )** to when you're done.

| Example:
```cpp
    SDL_Renderer * gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDER_ACCELERATED | SDL_RENDER_PRESENTVSYNC );
    if ( !gRenderer ) {
        // Error handling...
    }
    ...
    SDL_SetRenderDrawColor( gRenderer, 255, 0, 0, 255 );
    SDL_RenderClear( gRenderer );
    ...
    SDL_RenderPresent( gRenderer );
    ...
    SDL_DestroyRenderer( gRenderer );
    SDL_DestroyWindow( gWindow );
    SDL_Quit();
    ...
```


# SDL_DestroyRenderer( )
| Purpose:
`   `|| Deallocates render resources.
| Signature:
`   `|| void SDL_DestroyRenderer( SDL_Renderer * renderer );
| @param **renderer**:
`   `|| A pointer to the **SDL_Renderer** you want to destroy.

| Important Notes:
`   `|| Call before **SDL_DestroyWindow( )**.
`   `|| It's NULL-pointer-safe.


# SDL_GetNumRenderDrivers()
| Purpose:
`   `|| To query the available rendering backends.
| Signature:
`   `|| int SDL_GetNumRenderDrivers(void);

| Return Value:
`   `|| **>=0** on success, as the number of available rendering drivers.
`   `|| **-1** on failure, use **SDL_GetError()** for more information.

| Example:
```cpp
    int numDrivers = SDL_GetNumRenderDrivers();
    if ( numDrivers < 0 ) {
        // Handle error...
    }

    std::cout << "Available renderers:\n";
    for (int i = 0; i < numDrivers; i++) {
        SDL_RendererInfor info;
        if ( 0 == SDL_GetRenderDriverInfo(i, &info) ) {
            // Could be "direct3d", "opengl", "software", ...
            std::cout << info.name << std::endl;
        }
    }
```


# SDL_RenderDrawLine( )
| Purpose:
`   `|| To draw a single, straight line.
| Signature:
`   `|| int SDL_RenderDrawLine(SDL_Renderer * renderer, 
`                             `int x1, int y1, 
`                             `int x2, int y2);
| @param **renderer**:
`   `|| A pointer to the **SDL_Renderer** with the window or screen where you want to draw a line.
| @param **x1**:
| @param **y1**:
`   `|| The X- and Y-coordinate of the line's starting point.
| @param **x2**:
| @param **y2**:
`   `|| The X- and Y-coordinate of the line's ending point.

| Return Value:
`   `|| **0** on success.
`   `|| **<0** on failure, use **SDL_GetError()** for more information.

| Important Notes:
`   `|| Before calling it, 
`       `make sure you've called **SDL_SetRenderDrawColor( )** for the color you desired.
`   `|| Both begin- and end-points are inclusive in the drawing line.
`   `|| After calling it,
`       `remember to call **SDL_RenderPresent( )** to show the update.


# SDL_RenderFillRect( )
| Purpose:
`   `|| To draw a solid rectangle on the renderer, fill it with the currently selected color.
| Signature:
`   `|| int SDL_RenderFillRect( SDL_Renderer * renderer, const SDL_Rect * rect );
| @param **renderer**:
`   `|| A pointer to **SDL_Renderer** on which you want to draw the rectangle.
| @param **rect**:
`   `|| A pointer to **SDL_Rect** that definies the rectangle to be filled.

| Return Value:
`   `|| **0** on success.
`   `|| **<0** on failure, use **SDL_GetError()** for more information.


# SDL_RenderDrawRect( )
| Purpose:
`   `|| To draw a rectangle on the renderer, with the currently selected color.
| Signature:
`   `|| int SDL_RenderDrawRect( SDL_Renderer * renderer, const SDL_Rect * rect );
| @param **renderer**:
`   `|| A pointer to **SDL_Renderer** on which you want to draw the rectangle.
| @param **rect**:
`   `|| A pointer to **SDL_Rect** that definies the rectangle to be drawn.

| Return Value:
`   `|| **0** on success.
`   `|| **<0** on failure, use **SDL_GetError()** for more information.


# SDL_RenderDrawPoint( )
| Purpose:
`   `|| To draw a single pixel on the render with selected color.
| Signature:
`   `|| int SDL_RenderDrawPoint(SDL_Renderer * renderer, int x, int y);
| @param **renderer**:
`   `|| A pointer to **SDL_Renderer** on which you want to draw the pixel.
| @param **x**:
| @param **y**:
`   `|| The X- and Y-coordinate of the pixel.

| Return Value:
`   `|| **0** on success.
`   `|| **<0** on failure, use **SDL_GetError()** for more information.


# SDL_RenderPresent( )
| Purpose:
`   `|| To take the results of your rendering operations and make them visible.
`   `|| SDL rendering usually use double-buffering, a technique where you render to a hidden back buffer,
`       `this function essentially swaps the back buffer with the front buffer that's displayed on the screen,
`       `thus making the rendered results visible.
| Signature:
`   `|| void SDL_RenderPresent( SDL_Renderer * renderer );
| @param **renderer**:
`   `|| A pointer to the **SDL_Renderer** associated with the window you want to render.

| Important Notes:
`   `|| If you created your renderer with the **SDL_RENDER_PRESENTVSYNC** flag, 
`       `it will synchronize your monitor's refresh rate to prevent screen tearing.
`   `|| This function can be a blocking function, meaning that your program might
`       `wait until the next vertical refresh to continue if VSync is enabled.


# SDL_RenderClear( )
| Purpose:
`   `|| Fills the rendering target with the currently selected drawing color,
`       `this prepares it for new drawing operations.
| Signature:
`   `|| int SDL_RenderClear( SDL_Renderer * renderer );
| @param **renderer**:
`   `|| A pointer to the **SDL_Renderer** associated with the rendering target you want to clear.

| Return Value:
`   `|| **0** on success.
`   `|| **<0** on failure, use **SDL_GetError()** for more information.

| Important Notes:
`   `|| It is recommenede to call it at the beginning of your rendering loop, (for each time you switch rendering targets) 
`       `to avoid blending new content with leftovers from previous frames.
`   `|| Before calling it, make sure you set the desired color using **SDL_SetRenderDrawColor( )**.


# SDL_SetRenderDrawColor( )
| Purpose:
`   `|| To set the drawing color and apply it to the renderer.
| Signature:
`   `|| int SDL_SetRenderDrawColor(SDL_Renderer * renderer, 
`                                 `Uint8 r, Uint8 g, Uint8 b, Uint8 alpha);
| @param **renderer**:
`   `|| A pointer to the **SDL_Renderer** you want to set color.
| @param **r**:
| @param **g**:
| @param **b**:
| @param **alpha**:
`   `|| Values that ranges from **0** to **255** (0xff). Both inclusive.
`   `|| For alpha the value 0 means fully transparent, and 255 (0xff) means fully opaque.

| Return Value:
`   `|| **0** on success.
`   `|| **<0** on failure, use **SDL_GetError()** for more information.

| Important Notes:
`   `|| Rendering commands might blend the color you set with the existing colors on the rendering target,
`       `depending on the rendering target's blend mode, see **SDL_SetRenderDrawBlendMode( )**.


# SDL_SetRenderDrawBlendMode( )
| Purpose:
`   `|| To determine how new colors you draw with SDL rendering function will interact 
`       `with existing colors on the render target.
| Signature:
`   `|| int SDL_SetRenderDrawBlendMode(SDL_Renderer * renderer, SDL_BlendMode blendMode);
| @param **renderer**:
`   `|| A pointer to the **SDL_Renderer** you want to set blend mode.
| @param **blendMode**:
`   `|| An enumeration.
`   `|| **SDL_BLENDMODE_NONE**, new colors completely overwrite the existing colors.
`   `|| **SDL_BLENDMODE_BLEND**, alpha blending, providing classic transparency effects.
`   `|| **SDL_BLENDMODE_ADD**, color components are added together.
`   `|| **SDL_BLENDMODE_MOD**, color components are multiplied.

| Return Value:
`   `|| **0** on success.
`   `|| **<0** on failure, use **SDL_GetError()** for more information.


# SDL_CreateTextureFromSurface( )
| Purpose:
`   `|| To take an existing **SDL_Surface** and create a new **SDL_Texture** from it.
`   `|| Textures are optimized for rendering by a graphics card ( GPU );
`   `|| Rendering textures is generally faster and more efficient than directly rendering surfaces with SDL.
| Signature:
`   `|| SDL_Texture * SDL_CreateTextureFromSurface(SDL_Renderer * renderer, SDL_Surface * surface);
| @param **renderer**:
`   `|| A pointer to **SDL_Renderer** with which the texture will be associated.
`   `|| It's important to create the texture on the same renderer you intend to use for rendering.
| @param **surface**:
`   `|| A pointer to **SDL_Surface** that contains the source image data.

| Return Value:
`   `|| A pointer to the newly created **SDL_Texture**.
`   `|| **NULL** on failure, use **SDL_GetError()** for details.

| Important Notes:
`   `|| Depending on the implementation, the original **SDL_Surface** might not be altered.
`   `|| Often after creating the texture, you can safely free the original surface with **SDL_FreeSurface( )**.

| Example:
```cpp
    SDL_Window * gWindow = SDL_CreateWindow( ... );
    if ( !gWindow ) {
        // Error handling...
    }
    SDL_Renderer * gRenderer = SDL_CreateRenderer(
        gWindow, -1, SDL_RENDER_ACCELERATED
    );
    if ( !gRenderer ) {
        // Error handling...
    }

    SDL_Surface * imgSurface = IMG_Load( "image.png" );
    if ( !imgSurface ) {
        // Error handling...
    }
    SDL_Texture * imgTexture = SDL_CreateTextureFromSurface(
        gRenderer, imgSurface
    );
    SDL_FreeSurface( imgSurface );

    SDL_bool running = SDL_TRUE;
    SDL_Event e;
    do {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) 
                running = SDL_FALSE;
        }

        SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255); // black
        SDL_RenderClear( gRenderer );
        
        // Render the texture (centered).
        SDL_Rect dstrect;
        SDL_QueryTexture(imgTexture, NULL, NULL, &dstrect.w, &dstrect.h);
        dstrect.x = (640 - dstrect.w) / 2;
        dstrect.y = (480 - dstrect.h) / 2;
        SDL_RenderCopy( gRenderer, imgTexture, NULL, &dstrect);
        SDL_RenderPresent( gRenderer );
    } while ( running );
```


# SDL_QueryTexture( )
| Purpose:
`   `|| To retrieve essential information about an existing **SDL_Texture**.
| Signature:
`   `|| int SDL_QueryTexture(SDL_Texture * texture, 
`                           `Uint32 * format, 
`                           `int * access, 
`                           `int * w, int * h);
| @param **texture**:
`   `|| A pointer to the targeted **SDL_Texture**.
| @param **format**:
`   `|| To return as pixel format of the texture.
| @param **access**:
`   `|| To return as the access pattern of the texture.
`   `|| **SDL_TEXTUREACCESS_STATIC**, texture data won't be updated frequently.
`   `|| **SDL_TEXTUREACCESS_STREAMING**, texture data might be updated often.
`   `|| **SDL_TEXTUREACCESS_TARGET**, texture can be used as a render target 
`       `(you can render onto the texture itself).
| @param **w**:
| @param **h**:
`   `|| weight and height of the texture in pixels.

| Return Value:
`   `|| **0** on success.
`   `|| **<0** on failure, use **SDL_GetError()** for details.


# SDL_RenderSetViewport( )
| Purpose:
`   `|| To establish a rectangular sub-region within your renderer 
`       `where subsequent rendering operations will be confined.
`   `|| Can be used to create multiple windows within a window.
`   `|| Handy for scenarios like split-screen views.
| Signature:
`   `|| int SDL_RenderSetViewport(SDL_Renderer * renderer, const Rect * rect);
| @param **renderer**:
`   `|| A pointer to **SDL_Renderer** which you want to set the view port.
| @param **rect**:
`   `|| A pointer to **SDL_Rect** that defines the viewport's position and size.
`   `|| **NULL** to reset to the full renderer size.

| Return Value:
`   `|| **0** on success.
`   `|| **<0** on failure, use **SDL_GetError()** for details.



# SDL_RenderCopy( )
| Purpose:
`   `|| To copy portions of a texture to an SDL renderer.
| Signature:
`   `|| int SDL_RenderCopy( SDL_Renderer * renderer, SDL_Texture * texture,
`                          `const SDL_Rect * srcrect, const SDL_Rect * dstrect );
| @param **renderer**:
`   `|| Pointer to the target **SDL_Renderer** where the texture will be copied.
`   `|| This one must be the same as the renderer used in **SDL_CreateTextureFromSurface( )**.
| @param **texture**:
`   `|| Pointer to the **SDL_Texture** you want to copy from.
| @param **srcrect**:
`   `|| Pointer to an **SDL_Rect** defining the source rectangle within the texture.
`   `|| **NULL** will copy the entire texture.
| @param **dstrect**:
`   `|| Pointer to an **SDL_Rect** defining the destination rectangle on the renderer.
`   `|| Use **NULL** to use the full dimensions of the source texture (or srcrect).
`   `|| If dstrect smaller than srcrect, it will be clipped, 
`       `if larger, it will not scale, just left empty.

| Return Value:
`   `|| **0** on success.
`   `|| **<0** on failure, use **SDL_GetError()** for details.

| Important Notes:
`   `|| To allow for scaling, rotation, and flipping using the dstrect,
`       `and a separate function  **SDL_RenderCopyEx( )** provides even more advanced control.


# SDL_RenderCopyEx( )
| Purpose:
`   `||
| Signature:
`   `|| int SDL_RenderCopyEx(SDL_Renderer * renderer,
`                           `SDL_Texture  * texture,
`                           `const SDL_Rect * srcrect,
`                           `const SDL_Rect * dstrect,
`                           `const double angle,
`                           `const SDL_Point * center
`                           `const SDL_Flip flip);
| @param **renderer**:
`   `|| The renderer to use for rendering.
| @param **texture**:
`   `|| The texture to be rendered.
| @param **srcrect**:
`   `|| A pointer to **SDL_Rect** specifying the portion of the texture to render.
`   `|| If **NULL*, the entire texture is used.
| @param **dstrect**:
`   `|| A portion to **SDL_Rect** specifying the destination area on the rendering target.
`   `|| If **NULL**, the texture's original dimensions are used.
| @param **angle**:
`   `|| The rotation angle in degrees to be applied to the texture before rendering.
`   `|| Like **45.0** for 45 degrees and **90.0** for 90 degrees.
`   `|| Optional.
| @param **center**:
`   `|| A pointer to **SDL_Point** specifying the center of the rotation.
`   `|| If **NULL** the texture's center is used.
`   `|| Optional.
| @param **flip**:
`   `|| A set of flags indicating how to flip the texture.
`   `|| Use **SDL_FLIP_NONE** for no flipping.
`   `|| **SDL_FLIP_HORIZONTAL** for horizontal flipping.
`   `|| **SDL_FLIP_VERTICAL** for vertically flipping.
`   `|| Optional.

| Return Value:
`   `|| **0** on success.
`   `|| **<0** on failure, use **SDL_GetError()** for details.

| Important Notes:
`   `|| Setting *angle* to **0.0** and using **SDL_FLIP_HORIZONTAL** is functionally equivalent to 
`       `setting *angle* to **180.0** with **SDL_FLIP_NONE**.


# SDL_SetColorKey( )
| Purpose:
`   `|| To specify particular color within a surface or texture 
`       `that should be treated as transparent when rendering.
`   `|| Think of it like "green screening" for images, 
`       `you designate one color to be ignored, letting what's behind it show through.
| Signature:
`   `|| int SDL_SetColorKey(SDL_Surface * surface, int flag, Uint32 key);
| @param **surface**:
`   `|| A portions to the **SDL_Surface** on which you want to enable color keying.
| @param **flag**:
`   `|| **SDL_TRUE** enables color keying.
`   `|| **SDL_FALSE** disables color keying.
| @param **key**:
`   `|| The color value in the surface's pixel format that should be considered transparent.

| Return Value:
`   `|| **0** on success.
`   `|| **<0** on failure, use **SDL_GetError()** for details.


# SDL_SetTextureColorMod( )
| Purpose:
`   `|| To adjust the RGB color components of a texture on the fly.
`   `|| This provides a simple way to achieve colorization effects without modifying the texture's source image.
| Signature:
`   `|| int SDL_SetTextureColorMod(SDL_Texture * texture
`                                 `Uint8 r, Uint8 g, Uint8 b);
| @param **texture**:
`   `|| A pointer to the **SDL_Texture** whose colors you want to modify.
| @param **r**:
| @param **g**:
| @param **b**:
`   `|| The amount of RGB to apply.
`   `|| e.g. 255 for red keeps the original red and 0 removes all red. 
`       `Values in between scale the red component.

| Return Value:
`   `|| **0** on success.
`   `|| **<0** on failure, use **SDL_GetError()** for details.


# SDL_SetTextureAlphaMod( )
| Purpose:
`   `|| To adjust the transparency of a whole texture on the fly.
`   `|| Provides a way to modify how opaque a texture appears 
`       `when rendered without altering the texture's source data itself.
| Signature:
`   `|| int SDL_SetTextureAlphaMod(SDL_Texture * texture, Uint8 alpha);
| @param **texture**:
`   `||
| @param **alpha**:
`   `|| **0** completely transparent.
`   `|| **255** fully opaque.

| Return Value:
`   `|| **0** on success.
`   `|| **<0** on failure, use **SDL_GetError()** for details.


# TTF_Init() and TTF_Quit()
| Purpose:
`   `|| In the context of SDL2_ttf, for working with TrueType Fonts (TTF).
| Signature:
`   `|| int TTF_Init(void);
`   `|| void TTF_Quit(void);

| Return Value:
`   `|| For **TTF_Init()** it returns **0** on success,
`       `and **-1** on failure, use **TTF_GetError()** for human-readable error message.


# TTF_OpenFont( ) and TTF_CloseFont( )
| Purpose:
`   `|| Loads and closes a TrueType Font from a file.
| Signature:
`   `|| TTF_Font * TTF_OpenFont(const char * file, int ptsize);
| @param **file**:
`   `|| The path to the font file, e.g. "arial.ttf".
| @param **ptsize**:
`   `|| The font size in points (roughly equivalent to pixels at standard display resolutions).
| Signature:
`   `|| void TTF_CloseFont(TTF_Font * font);
| @param **font**:
`   `|| A pointer to **TTF_Font**, could be **NULL**.

| Return Value for **TTF_OpenFont( )**:
`   `|| A pointer to **TTF_Font** structure on success.
`   `|| **NULL** on failure, get more information with **TTF_GetError()**.


# TTF_RenderText_Solid( )
| Purpose:
`   `|| To render text using a specific font onto an **SDL_Surface**,
`       `which can be then used as a texture with **SDL_CreateTextureFromSurface( )** for display.
| Signature:
`   `|| SDL_Surface * TTF_RenderText_Solid(TTF_Font * font,
`                                        `const char * text,
`                                        `SDL_Color fg);
| @param **font**:
`   `|| A pointer to the loaded **TTF_Font** structure from **TTF_OpenFont( )**.
| @param **text**:
`   `|| The text string to be rendered.
| @param **fg**:
`   `|| A **SDL_Color** structure representing the foreground color of the text.

| Return Value:
`   `|| A pointer to an **SDL_Surface** on success.
`   `|| **NULL** on failure, use **TTF_GetError()** for more information.


# TTF_RenderText_Shaded( )
| Purpose:
`   `|| To render text using a specified font with a gradient shading effect. 
`       `This can create a more visually appealing and stylized look for text.
| Signature:
`   `|| SDL_Surface * TTF_RenderText_Shaded(TTF_Font * font,
`                                          `const char * text,
`                                          `SDL_Color color1,
`                                          `SDL_Color color2);
| @param **font**:
`   `|| A pointer to the loaded **TTF_Font** structure from **TTF_OpenFont( )**.
| @param **text**:
`   `|| The text string to be rendered.
| @param **color1**:
`   `|| A **SDL_Color** structure representing the text primarily starts with,.
| @param **color2**:
`   `|| A **SDL_Color** structure representing the text gradients intot.

| Return Value:
`   `|| The same as **TTF_RenderText_Solid( )**


# TTF_RenderText_Blended( )
| Purpose:
`   `|| To render the text using a specified font and applies anti-aliasing to produce smoother, 
`       `more visually appealing text edges.
`   `|| Ideal for situations where the quality of the rendered text is important.
| Signature:
`   `|| SDL_Surface * TTF_RenderText_Blended(TTF_Font * font
`                                           `const char * text
`                                           `SDL_Color fg);
| Same parameters as the **TTF_RenderText_Solid( )**
| Same return values as the **TTF_RenderText_Solid( )**


# TTF_RenderText_Blended_Wrapped( )
| Purpose:
`   `|| Automatically wraps text to fit within a specific width.
| Signature:
`   `|| SDL_Surface * TTF_RenderText_Blended_Wrapped(TTF_Font * font,
`                                                   `const char * text,
`                                                   `SDL_Color fg,
`                                                   `Uint32 wrapLen);
| @param **font**:
`   `|| A pointer to the loaded **TTF_Font** structure from **TTF_OpenFont( )**.
| @param **text**:
`   `|| The text string to be rendered.
| @param **fg**:
`   `|| A **SDL_Color** structure representing the foreground color of the text.
| @param **wrapLen**:
`   `|| The maximum width in pixels of each line of text before wrapping occurs.

| Return Value the same as **TTF_RenderText_Solid( )**


# Mix_OpenAudio( ) 
| Purpose:
`   `|| Initializes the *SDL_mixer.h* library and prepares it for audio playback.
`   `|| This must be called before using any other SDL_mixer functions.
| Signature:
`   `|| int Mix_OpenAudio(int frequency,
`                        `Uint16 format,
`                        `int channels,
`                        `int chunksize);
| @param **frequency**:
`   `|| Desired output sample rate in Hz, e.g. **44100** for CD-quality audio.
| @param **format**:
`   `|| Desired audio format.
`   `|| **MIX_DEFAULT_FORMAT** is a common choice.
`   `|| **AUDIO_S16LSB** for signed 16-bit little endian.
| @param **channels**:
`   `|| Number of sounds channels, **1** for mono and **2** for stereo.
| @param **chunksize**:
`   `|| Size of the audio chunks in samples,
`       `larger chunks reduce potential glitching but increase latency.
`   `|| Common values are **512**, **1024** and **2048**.

| Return Value:
`   `|| **0** on success.
`   `|| **-1** on failure, call **Mix_GetError()** for more information.


# Mix_Quit( )
| Purpose:
`   `|| Used in pair with **Mix_OpenAudio( )**.
| Signature:
`   `|| void Mix_Quit(void);


# Mix_LoadMUS( )
| Purpose:
`   `|| To load a music file into memory for playback using SDL_mixer.
`   `|| Supports various music formats like **MP3**, **WAV**, **OGG**, **MIDI**, ...
| Signature:
`   `|| Mix_Music * Mix_LoadMUS(const char * filename);
| @param **filename**:
`   `|| The path to the music file you want to load.

| Return Value:
`   `|| A pointer to a **Mix_Music** structure on success.
`   `|| **NULL** on failure, you can use **Mix_GetError()** for more information.

| Important Notes:
`   `|| **Mix_LoadMUS( )** is designed for longer background music tracks,
`       `for short sound effects, use **Mix_LoadWAV( )**
`   `|| Use **Mix_PlayMusic( )** to play the loadded music.
`   `|| Use **Mix_PausedMusic( )**, **Mix_VolumeMusic** ... to control playback.
`   `|| Use **Mix_FreeMusic( )** to release the resources.


# Mix_LoadWAV( )
| Purpose:
`   `|| Loads a WAV file into memory for immediate playback as a sound effect in your application.
`   `|| WAV files are typically uncompressed audio formats,
`       `making them ideal for fast access and playback without complex decoding.
| Signature:
`   `|| Mix_Chunk * Mix_LoadWAV(const char * filename);
| @param **filename**:
`   `|| The path to the music file you want to load.

| Return Value:
`   `|| A pointer to **Mix_Chunk** structure on success.
`   `|| **NULL** on failure, you can use **Mix_GetError()** for more information.

| Important Notes:
`   `|| Use **Mix_PlayChannel( )** to play the loaded sound effect.
`   `|| Use **Mix_FreeChunk( )** to release memory occupied.


# Mix_FreeChunk( )
| Signature:
`   `|| void Mix_FreeChunk(Mix_Chunk * chunk);
# Mix_FreeMusic( )
| Signature:
`   `|| void Mix_FreeMusic(Mix_Music * music);


# Mix_PlayChannel( )
| Purpose:
`   `|| Plays a loaded sound effect by **Mix_LoadWAV( )** on a specified audio channel.
| Signature:
`   `|| int Mix_PlayChannel(int channel,
`                          `Mix_Chunk * chunk,
`                          `int loops);
| @param **channel**:
`   `|| The desired audio channel to use for playback.
`   `|| **-1** to play on the first available (unused) channel.
`   `|| **0** to **MAX_CHNNELS - 1** to play on specific channel number.
| @param **chunk**:
`   `|| A pointer to the **Mix_Chunk** structure.
| @param **loops**:
`   `|| The number of times to loop the sound.
`   `|| **0** to play the sound only once.
`   `|| **-1** to play the sound indefinitely.

| Return Value:
`   `|| Returns the channel number the sound is playing on.
`   `|| **-1** on error, use **Mix_GetError()** for more information.


# Mix_PlayMusic( )
| Purpose:
`   `|| To play a loaded music track by **Mix_LoadMUS( )** in the background of your application.
| Signature:
`   `|| int Mix_PlayMusic(Mix_Music * music, int loops);
| @param **music**:
`   `|| A pointer to the **Mix_Music** structure.
| @param **loops**:
`   `|| The number of times to loop the sound.
`   `|| **0** to play the sound only once.
`   `|| **-1** to play the sound indefinitely.

| Return Value:
`   `|| Returns the channel number the sound is playing on.
`   `|| **-1** on error, use **Mix_GetError()** for more information.


# Mix_PlayingMusic( )
| Purpose:
`   `|| To check whether background music is currently playing.
| Signature:
`   `|| int Mix_PlayingMusic(void);

| Return Value:
`   `|| **1** if music is currently playing.
`   `|| **0** if music is not currently playing.


# Mix_PausedMusic( )
| Purpose:
`   `|| To check whether the background music is currently paused.
| Signature:
`   `|| int Mix_PausedMusic(void);

| Return Value:
`   `|| **1** if music is currently paused.
`   `|| **0** if music is currently playing or if no music is loaded.


# Mix_PauseMusic() and Mix_ResumeMusic()
| Purpose:
`   `|| Just as the name has suggested, pasues / resumes playback of background music.
| Signature:
`   `|| void Mix_PauseMusic(void); 
`   `|| void Mix_ResumeMusic(void);


# Mix_HaltMusic( )
| Purpose:
`   `|| To stop the currently playing background music and resets its position to the beginning. 
`   `|| This is a more definitive stop compared to **Mix_PauseMusic()**.
| Signature:
`   `|| int Mix_HaltMusic(void);

| Return Value:
`   `|| **1** on success, although unlikely to fail.

| Important Notes:
`   `|| After calling this, you cannot use **Mix_ResumeMusic()**.


# SDL_GetMouseState( )
| Purpose:
`   `|| Retrieves the current state of the mouse, including: 
`       `Button states (pressed or released).
`       `Mouse cursor position.

| Signature:
`   `|| Uint32 SDL_GetMouseState(int * x, int * y);
| @param **x**:
| @param **y**:
`   `|| As output variables, the X- and Y-coordinate of the mouse position.

| Return Value:
`   `|| A bitmask representing the current state of each mouse button.
`   `|| A bit value of *1* indicates the button is pressed, *0* indicates it is not pressed.
`   `|| Bit **0** (Least Significant Bit): Left mouse button.
`   `|| Bit **1**: Middle mouse button.
`   `|| Bit **2**: Right mouse button.
`   `|| Bit **3**: X1 button (often a side button on mice).
`   `|| Bit **4**: X2 button (often another side button on mice).

| Important Notes:
`   `|| Be sure to call **SDL_PumpEvents( )** or a similar event-handling function before calling it. 
`       `This updates SDL's internal state with the most recent mouse events.
`   `|| Use the SDL_BUTTON(X) macros to check for specific buttons 
`       `(e.g., SDL_BUTTON(SDL_BUTTON_RIGHT) for the right button).

| Example:
```cpp
    Uint32 buttonState = SDL_GetMouseState(nullptr, nullptr);
    /*
        SDL_BUTTON(SDL_BUTTON_LEFT)
        SDL_BUTTON(SDL_BUTTON_MIDDLE)
        SDL_BUTTON(SDL_BUTTON_RIGHT)
        SDL_BUTTON(SDL_BUTTON_X1)
        SDL_BUTTON(SDL_BUTTON_X2)
    */
    if (buttonState & SDL_BUTTON(SDL_BUTTON_RIGHT)) {
        // Right mouse button is pressed...
    }
```


# SDL_GetTicks( )
| Purpose:
`   `|| Retrieves the number of milliseconds that have elapsed since the SDL library was initialized.
`   `|| The counter wraps around to zero if your program runs for more than ~49 days.
| Signature:
`   `|| Uint32 SDL_GetTicks(void);

| Return Value:
`   `|| Returns an **Uint32** value representing the milliseconds elapsed since **SDL_Init( )** was called.

| Example:
```cpp
    const int TARGET_FPS = 60;
    const int MS_PER_FRAME = 1000 / TARGET_FPS; // ~16ms per frame.

    Uint32 frameStart;
    int frameTime;
    bool running = true;
    while ( running ) {
        frameStart = SDL_GetTicks();
        ...
        frameTime = SDL_GetTicks() - frameStart;
        if (frameStart < MS_PER_FRAME) {
            // Dealy to maintain frame rate.
            SDL_Delay(MS_PER_FRAME - frameTime);
        }
    }
```


# SDL_Delay( )
| Purpose:
`   `|| Pauses the current thread (suspends the execution of your program) 
`       `for a specified number of milliseconds.
| Signature:
`   `|| void SDL_Delay(Uint32 milliseconds);


# SDL_StartTextInput( )
| Purpose:
`   `|| Enables text input functionality in your SDL2 application.
`   `|| Starts to capture your keyboard input event and translating them into text characters.
| Signature:
`   `|| void SDL_StartTextInput(void);

| Important Notes:
`   `|| Must be paired with **SDL_StopTextInput( )** to disable text input processing when you're done.
`   `|| It makes your application receptive to user typing and genetates two types of events:
`       `**SDL_TextInputEvent** (SDL_TEXTINPUT): carries the actual typed characters encoded in UTF-8.
`       `**SDL_TextEditingEvent** (SDL_TEXTEDITINg): provides more granular information about the 
`           `editing process, such as cursor position changes, selection changes, ...
`   `|| You'll need to handle the generated **SDL_TextInputEvent** and **SDL_TextEditingEvent** events
`       `in your event loop to process the entered text and update your application state accordingly.

| Example:
```cpp
    bool quit = false;
    SDL_Event e;
    std::string inputText = "";

    while ( !quit ) {
        while ( SDL_PollEvent(&e) ) {
            if (e.type == SDL_QUIT) 
                quit = true;
            else
                // Process the typed character(s) from e.text.text
                inputText += e.text.text;
            ...
        }
        ...
    }

    SDL_StopTextInput();
```


# SDL_StopTextInput( )
| Purpose:
`   `|| Disables text input processing within your SDL2 application.
`   `|| Pair with **SDL_StartTextInput( )**.
| Signature:
`   `|| void SDL_StopTextInput(void);


# SDL_GetModState( )
| Purpose:
`   `|| To retrieve the current state of keyboard modifier keys,
`       `like SHIFT, CTRL, ALT, SUPER, ...
| Signature:
`   `|| SDL_Keymod SDL_GetModState(void);

| Return Value:
`   `|| **SDL_Keymod** is an enumeration type represeting possible modifier key states.
`   `|| **KMOD_LSHIFT**
`   `|| **KMOD_RSHIFT**
`   `|| **KMOD_LCTRL**
`   `|| **KMOD_RCTRL**
`   `|| **KMOD_LALT**
`   `|| **KMOD_RALT**
`   `|| **KMOD_LGUI** for left Super/Windows/Command key.
`   `|| **KMOD_RGUI** for right uper/Windows/Command key.
`   `|| **KMOD_NUM** for NumLock key.
`   `|| **KMOD_CPS** for CpasLock key.

| Example:
```cpp
    SDL_Keymod currentKeymod = SDL_GetModState();
    if ( currentKeymod & KMOD_LSHIFT ) {
        ...
    }
    if ( currentKeymod & (KMOD_LCTRL | KMOD_RCTRL) ) {
        ...
    }
```


# SDL_SetClipboardText( )
| Purpose:
`   `|| Places UTF-8 encoded text onto the system's clipboard.
`   `|| Enables you to copy text from your SDL2 application to paste them into other applications.
| Signature:
`   `|| int SDL_SetClipboardText(const char * text)
| @param **text**:
`   `|| A NULL-terminated string containing UTF-8 encoded text you want to be copied.

| Return Value:
`   `|| **0** on success.
`   `|| **<0** on failure.


# SDL_GetClipboardText( )
| Purpose:
`   `|| Retrieves UTF-8 encoded text from the system's clipboard.
| Signature:
`   `|| char * SDL_GetClipboardText(void)

| Return Value:
`   `|| A NULL-terminated string containing UTF-8 text.
`   `|| **NULL** if the clipboard is empty or there was an error occuring.

| Example:
```cpp
    char * clipboard = SDL_GetClipboardText();
    if ( !clipboard ) {
        ...
    }
    ...
    SDL_free( clipboard );
```


# SDL_free( )
| Purpose:
`   `|| To de-allocate memory that has been previously returned by the SDL2's memory management functions.
`   `|| Paired with **SDL_malloc( )**.
`   `|| This function is NULL-safe.
| Signature:
`   `|| void SDL_free(void * ptr);


# SDL_malloc( )
| Purpose:
`   `|| Dynamically allocates a block of memory on the heap.
| Signature:
`   `|| void * SDL_malloc(size_t size);
| @param **size**:
`   `|| The number of bytes you want to allocate.

| Return Value:
`   `|| A pointer to the beginning of newly allocated memory block on success.
`   `|| **NULL** on failure, usually because of not enough memory available.


# SDL_RWFromFile( )
| Purpose:
`   `|| Opens a file for reading and/or writing.
| Signature:
`   `|| SDL_RWops * SDL_RWFromFile(const char * file, const char * mode);
| @param **file**:
`   `|| A NULL-terminated string containing the path and file name you want to open.
| @param **mode**:
`   `|| **"r"** for reading only, **"w"** for writing only.
`   `|| **"r+"** for both reading and writing.
`   `|| **"w+"** for both reading and writing but truncates an existing file or creates a new one.
`   `|| **"a"** for appending to the end of file if exists.
`   `|| **"a+"** for reading and appending, creating new file if not existed.
`   `|| You can also add **"b"** like **"rb"** for binary mode rather than text mode.

| Return Value:
`   `|| A pointer to an **SDL_RWops** structure on success.
`   `|| **NULL** on failure.


# SDL_RWclose( )
| Purpose:
`   `|| Closes a file previously opened by **SDL_RWFromFile( )**.
| Signature:
`   `|| int SDL_RWclose(SDL_RWops * context);
| @param **context**:
`   `|| A pointer to the **SDL_RWops** you want to close.

| Return Value:
`   `|| Returns **0** on success.
`   `|| Returns **<0** on failure.


# SDL_RWread( )
| Purpose:
`   `||
| Signature:
`   `|| size_t SDL_RWread(SDL_RWops * context,
`                        `void * ptr,
`                        `size_t size,
`                        `size_t maxnum);
| @param **context**:
`   `|| A pointer to the **SDL_RWops** structure that represents the opened file.
| @param **ptr**:
`   `|| A pointer to the buffer where you want to store the read data.
| @param **size**:
`   `|| A size of each element (in bytes) that you want to read.
| @param **maxnum**:
`   `|| The maximum number of elements you want to read.

| Return Value:
`   `|| Returns the number of elements successfully read from the file.
`   `|| Returns **0** if end-of-file reached or there's an error.


# SDL_RWwrite( )
| Purpose:
`   `|| 
| Signature:
`   `|| size_t SDL_RWwrite(SDL_RWops * context.
`                         `const void * ptr,
`                         `size_t size,
`                         `size_t num);
| @param **context**:
`   `|| A pointer to the **SDL_RWops** structure that represents the opened file.
| @param **ptr**:
`   `|| A pointer to the buffer where contains the data you want to write.
| @param **size**:
`   `|| A size of each element (in bytes) that you want to write.
| @param **maxnum**:
`   `|| The number of elements you want to write.

| Return Value:
`   `|| Returns the number of elements successfully written to the file.
`   `|| Returns **0** on error or if nothing could be written.


# SDL_RWtell( )
| Purpose:
`   `|| Retrieves the current position (offset) within a file.
`   `|| Parameters are easy to understand.
| Signature:
`   `|| Sint64 SDL_RWtell( SDL_RWops * context );

| Return Value:
`   `|| Returns the offset in bytes from the beginning of the file on success.
`   `|| **-1** on error.


# SDL_RWseek( )
| Purpose:
`   `||
| Signature:
`   `|| Sint64 SDL_RWseek(SDL_RWops * context.
`                        `Sint64 offset,
`                        `int whence);
| @param **context**:
`   `|| No need to explain.
| @param **offset**:
`   `|| A signed 64-bit integer specifying the number of bytes to move from the **whence**.
| @param **whence**:
`   `|| **RW_SEEK_SET** to seek from the beginning of the file.
`   `|| **RW_SEEK_CUR** to seek from the current position of the file.
`   `|| **RW_SEEK_END** to seek from the end of the file.

| Return Value:
`   `|| Returns the new file position (offset from the beginning of the file) on success.
`   `|| **-1** on error.


# SDL_GetNumAudioDevices( )
| Purpose:
`   `|| Use it after **SDL_INIT_AUDIO** subsystem is initialized.
`   `|| Provides information about the number of audio in-/output devices.
| Signature:
`   `|| int SDL_GetNumAudioDevices(int iscapture);
| @param **iscapture**:
`   `|| **0** to query the number of audio output devices (for playing sounds).
`   `|| **non-zero** to query the number of audio input devices (for recording sounds).

| Returns **-1** on error.



# SDL_GetAudioDeviceName( )
| Purpose:
`   `|| As its name has suggested.
| Signature:
`   `|| const char * SDL_GetAudioDeviceName(int index, int iscapture);
| @param **index**:
`   `|| The index of audio device from **0** to **SDL_GetNumAudioDevices() - 1**.
| @param **iscapture**:
`   `|| **0** for audio output device and **non-zero** for audio input devices.

| Returns a NULL-terminated string on success.
| Returns **NULL** on error.


# SDL_zero( )
| Purpose:
`   `|| Sets all bytes within a block of memory to zero.
| Signature:
`   `|| void SDL_zero(void * s);
| @param **s**:
`   `|| A pointer to the memory block you want to set to zeros.

| Example:
```cpp
    struct PlayerData {
        char name[50];
        int score;
        bool isPlaying;
    };

    PlayerData playerData;
    SDL_zero(playerData);

    char inputBuffer[100];
    SDL_zero(inputBuffer);
```


# SDL_OpenAudioDevice( )
| Purpose:
`   `||
| Signature:
`   `|| SDL_AudioDeviceID SDL_OpenAudioDevice(
`               `const char * device,
`               `int iscapture
`               `const SDL_AudioSpec * desired,
`               `SDL_AudioSpec * obtained
`               `int allowd_changes);
| @param **device**:
`   `|| The name of the device obtained by **SDL_GetAudioDeviceName( )**.
| @param **iscapture**:
`   `|| As mentioned before.
| @param **desired**:
`   `|| A pointer to an **SDL_AudioSpec** structure that defines the desired audio informations.
| @param **obtained**:
`   `|| A pointer to an **SDL_AudioSpec** structure that 
`       `SDL2 will fill with the actual format obtained from the opened device.
| @param **allowd_changes**:
`   `|| A set of flags controlling which changes SDL2 is allowed to make to your **desired** format.
`   `|| e.g. **SDL_AUDIO_ALLOW_FREQUENCY_CHANGE**, **SDL_AUDIO_ALLOW_CHANNELS_CHANGE**, ...

| Return Value:
`   `|| An **SDL_AudioDeviceID** on success.
`   `|| **0** on error.

| Example:
```cpp
    SDL_Init( SDL_INIT_AUDIO );
    SDL_AudioSpec desired;
    SDL_zero( desired );
    desired.freq = 44100;           // 44.1 kHz sample rate.
    /*
        AUDIO_S8            signed 8-bit
        AUDIO_U8            unsigned 8-bit
        AUDIO_S16LSB        signed 16-bit, little-endian
        AUDIO_S16MSB        signed 16-bit, big-endian
        AUDIO_S32LSB        signed 32-bit, little-endian
        AUDIO_S32MSB        signed 32-bit, big-endian
        AUDIO_F32LSB        32-bit floating-point, little-endian
        AUDIO_F32MSB        32-bit floating-point, bit-endian
    */
    desired.format = AUDIO_S16SYS;  // Signed 16-bit audio.
    desired.channels = 2;           // Stereo
    desired.sample = 4096;          // Audio buffer size.
    
    SDL_AudioSpec obtained;

    SDL_AudioDeviceID deviceId = SDL_OpenAudioDevice(
        name,
        0,
        &desired,
        &obtained,
        0
    );
    if ( deviceId == 0 ) {
        ...
    }

    SDL_CloseAudioDevice( deviceId );
    SDL_Quit();
```


# SDL_PauseAudioDevice( )
| Purpose:
`   `|| Pauses and unpauses audio playback or capture on a specified audio device.
| Signature:
`   `|| void SDL_PauseAudioDevice(SDL_AudioDeviceID dev, int pause_on);
| @param **dev**:
`   `|| The **SDL_AudioDeviceID** you want to pause or unpause.
| @param **pause_on**:
`   `|| **0** to unpause and **non-zero** to pause.


# SDL_LockAudioDevice( ) and SDL_UnlockAudioDevice( )
| Purpose:
`   `|| Locks an audio device, temporarily preventing its audio callback function from being called.
`   `|| Resumes SDL's normal callback-driven operation for the audio device.
| Signature:
`   `|| void SDL_LockAudioDevice(SDL_AudioDeviceID dev);
`   `|| void SDL_UnlockAudioDevice(SDL_AudioDeviceID dev);


# SDL_SetWindowTitle( )
| Purpose:
`   `|| Sets the title of a specified SDL window.
`   `|| Parameters are self-explaining.
| Signature:
`   `|| void SDL_SetWindowTitle(SDL_Window * window, const char * title);


# SDL_SetWindowFullscreen( )
| Purpose:
`   `|| Toggles fullscreen mode for a specified SDL window.
| Signature:
`   `|| int SDL_SetWindowFullscreen(SDL_Window * window, Uint32 flags);
| @param **window** is self-explaining enough.
| @param **flags**:
`   `|| A combination of flags that control the type of fullscreen mode.
`   `|| **0** exit fullscreen if it was active before.
`   `|| **SDL_WINDOW_FULSCREEN** for true fullscreen mode,
`       `the window resolution is changed to display mode supported by your device,
`       `and the window takes up the entire screen.
`   `|| **SDL_WINDOW_FULSCREEN_DESKTOP** for desktop fullscreen mode,
`       `the window size is changed to the desktop resolution,
`       `but it's not a resolution change for the video card, other windows may still be visible.

| Returns Value:
`   `|| **0** on success.
`   `|| **<0** on failure.


# SDL_GetWindowID( )
| Purpose:
`   `|| Retrieves an unique identifier for a specified SDL window.
`   `|| SDL2 internally assigns a unique ID to each window created using **SDL_CreateWindow( )**.
| Signature:
`   `|| Uint32 SDL_GetWindowID(SDL_Window * window);

| Returns the unique window ID as an Uint32.


# SDL_GetWindowFromID( )
| Purpose:
`   `|| Retrieves an **SDL_Window** pointer given its window ID.
`   `|| Returns **NULL** on failure.
| Signature:
`   `|| SDL_Window * SDL_GetWindowFromID(Uint32 windowID);


# SDL_HideWindow( )
| Purpose:
`   `|| Hides (not minimize) the specified SDL window.
`   `|| The window will no longer be visible on the screen.
| Signature:
`   `|| void SDL_HideWindow(SDL_Window * window);


# SDL_ShowWindow( )
| Purpose:
`   `|| Makes a previously hidden SDL window visble again.
| Signature:
`   `|| void SDL_ShowWindow(SDL_Window * window)


# SDL_RaiseWindow( )
| Purpose:
`   `|| Brings a specified SDL window to the top of the Z-order and gives it focus.
| Signature:
`   `|| void SDL_RaiseWindow(SDL_Window * window);


# SDL_GetWindowDisplayIndex( )
| Purpose:
`   `|| Retrieves the index of the display monitor where a specified SDL window is mostly located.
| Signature:
`   `|| int SDL_GetWindowDisplayIndex(SDL_Window * window);

| Return Value:
`   `|| **>=0** as the display index.
`   `|| **-1** on error.


# SDL_ConvertSurfaceFormat( )
| Purpose:
`   `|| Creates a new SDL surface with a specified pixel format.
| Signature:
`   `|| SDL_Surface * SDL_ConvertSurfaceFormat(SDL_Surface * src,
`                                             `Uint32 pixel_format,
`                                             `int flags);
| @param **src**:
`   `|| A pointer to the existing **SDL_Surface** that you want to convert.
| @param **pixel_format**:
`   `|| The desired pixel format for the new surface.
| @param **flags**:
`   `|| Provides additional control over the conversion process, most commonly **0**.

| Example:
```cpp
    SDL_DisplayMode displayMode;
    SDL_GetCurrentDisplayMode(0, &displayMode);
    Uint32 targetFormat = displayMode.format;

    if (theSurface->format->format != targetFormat) {
        SDL_Surface * convertedSurface = SDL_ConvertSurfaceFormat(
            theSurface,
            targetFormat,
            0
        );
        SDL_FreeSurface( theSurface );
        theSurface = convertedSurface;
    }
    ...
```


# SDL_GetCurrentDisplayMode( )
| Purpose:
`   `||
| Signature:
`   `|| int SDL_GetCurrentDisplayMode(int displayIndex,
`                                    `SDL_DisplayMode * mode);
| @param **displayIndex**:
`   `|| The index of the display monitor you want information about.
| @param **mode**:
`   `|| A pointer to an **SDL_DisplayMode** structure that SDL2 will fill with display information.

| Return Value:
`   `|| **0** on success.
`   `|| **-1** on error.


# SDL_GetWindowPixelFormat( )
| Purpose:
`   `|| Retreives the pixel format of the specified SDL window's associated framebuffer.
| Signature:
`   `|| Uint32 SDL_GetWindowPixelFormat(SDL_Window * window);


# Understanding Pixel Formats
| A pixel format describes how the color components (r, g, b, and sometimes alpha) 
`   `of a single pixel are arranged in memory. 

| Common pixel formats include:
`   `|| **SDL_PIXELFORMAT_RGB888** for 8 bits per r, g, b.
`   `|| **SDL_PIXELFORMAT_RGB8888** for 8 bits per r, g, b, a.
`   `|| **SDL_PIXELFORMAT_RGB565** for 5 bits r, 6 biys g, 5 bits b.
`   `|| ...



# SDL_CreateTexture( )
| Purpose:
`   `|| Creates an **SDL_Texture**.
| Signature:
`   `|| SDL_Texture * SDL_CreateTexture(SDL_Renderer * renderer,
`                                      `Uint32 format,
`                                      `int access,
`                                      `int w,
`                                      `int h);
| @param **renderer**:
`   `|| A pointer to the **SDL_Renderer** associated with the display device
`       `where you intend to render the texture.
| @param **format**:
`   `|| The pixel format of the texture.
| @param **access**:
`   `|| Specifies how the texture data can be accessed.
`   `|| This impacts whether the CPU can directly modify the texture,
`       `whether the texture can be used as a render target, ...
`   `|| **SDL_TEXTUREACCESS_STATIC**: data is rarely or never updated.
`   `|| **SDL_TEXTUREACCESS_STREAMING**: data may change frequently.
`   `|| **SDL_TEXTUREACCESS_TARGET**: allows the texture to be used as a render target.
| @param **w**:
| @param **h**:
`   `|| width and height of the texture in pixels.

| Return Value:
`   `|| A pointer to the newly created **SDL_Texture** on sucees.
`   `|| **NULL** on error.


# SDL_LockTexture( )
| Purpose:
`   `|| Locks a portion of an SDL texture for direct pixel manipulation by the CPU.
`   `|| Any rendering operations between locking and unlocking 
`       `might not reflect your modifications until the texture is released.
| Signature:
`   `|| int SDL_LockTexture(SDL_Texture * texture, 
`                          `const SDL_Rect * rect,
`                          `void ** pixels,
`                          `int * pitch);
| @param **texture**:
`   `|| A pointer to the **SDL_Texture** you want to lock.
| @param **rect**:
`   `|| A pointer to **SDL_Rect** defining the region of texture to lock.
`   `|| **NULL** to lock the entire texture.
| @param **pixels**:
`   `|| As output parameter.
`   `|| A pointer to a pointer that will be filled with the address of the locked pixel data.
| @param **pitch**:
`   `|| As output parameter.
`   `|| A pointer to an integer that will be filled with the pitch of the locked pixels.
`   `|| The pitch represents the number of bytes in one row of pixel data.

| Return Value:
`   `|| **0** on success.
`   `|| **-1** on error.


# SDL_UnlockTexture( )
| Purpose:
`   `|| Releases a lock on an SDL texture that was previously obtained using **SDL_LockTexture()**.
| Signature:
`   `|| void SDL_UnlockTexture(SDL_Texture * texture);


# SDL_SetRenderTarget( )
| Purpose:
`   `|| Selects a texture as the current rendering target for subsequent SDL rendering operations.
`   `|| Changes where drawing commands like **SDL_RenderDrawLine()**, **SDL_RenderCopy()**, etc, 
`       `will send their output.
| Signature:
`   `|| int SDL_SetRenderTarget(SDL_Renderer * renderer,
`                              `SDL_Texture  * texture);
| @param **renderer**:
`   `|| A pointer to the **SDL_Renderer** associated with the display device.
| @param **texture**:
`   `|| A pointer to the **SDL_Texture** you want to make the render target.
`   `|| To revert to rendering to the main window (screen), pass **NULL**.

| Return Value:
`   `|| **0** on success.
`   `|| **-1** on error.


# SDL_AddTimer( )
| Purpose:
`   `||
| Signature:
`   `|| SDL_TimerID SDL_AddTimer(Uint32 interval,
`                               `SDL_TimerCallback callback,
`                               `void * param);
| @param **interval**:
`   `|| The desired time interval in milliseconds.
`   `|| e.g. an interval of **100** would trigger an event every second.
| @param **callback**:
`   `|| A pointer to the callback function.
`   `|| Uint32 timerCallbackExample(Uint32 interval, void * param);
| @param **param**:
`   `|| A pointer to an arbitrary data that will be passed along to your callback function.

| Return Value:
`   `|| An unique **SDL_TimerID** identifying the newly created timer on success.
`   `|| **0** on error.

| Important Notes about my timer callback function:
`   `|| The param **interval** tells you the configured interval in milliseconds 
`       `of the timer that triggered the callback.
`   `|| The second param no need to explain.
`   `|| The return value of the callback function is usually the *desired delay* 
`       `until the next time the timer should trigger.
`       `Return **0** will cause the timer to stop after the current callback executes.
`       `If you return the original **interval** value, the timer will keep repeating at the same interval.
`       `You can return a different value to adjust the next interval dynamically.


# SDL_RemoveTimer( )
| Purpose:
`   `|| Stops and removes an exisiting timer that you previously created.
| Signature:
`   `|| int SDL_RemoveTimer(SDL_TimerID timerId);

| Return Value:
`   `|| **1** on success.
`   `|| **0** if timer was not found.


# SDL_CreateThread( )
| Purpose:
`   `|| Spawns a new thread of execution within your application.
`   `|| Parameters and return type are also very self-explaining.
| Signature:
`   `|| SDL_Thread * SDL_CreateThread(int (*fn) (void*),
`                                    `const char * thread_name,
`                                    `void * data);


# SDL_WaitThread( )
| Purpose:
`   `|| Blocks the calling thread until a specified thread terminates.
`   `|| Parameters are very self-explaining.
| Signature:
`   `|| void SDL_WaitThread(SDL_Thread * thread, int * status);


# SDL_CreateSemaphore( )
| Purpose:
`   `|| Creates a semaphore object.
| Signature:
`   `|| SDL_sem * SDL_CreateSemaphore(Uint32 initVal);


# SDL_DestroySemaphore( )
| Purpose:
`   `|| Deallocates a semaphore object that you previously created.
| Signature:
`   `|| void SDL_DestroySemaphore(SDL_sem * sem);


# SDL_SemWait( )
| Purpose:
`   `|| Attempts to acquire (decrement) an SDL semaphore.
`   `|| If the semaphore's internal counter is greater than zero, the function succeeds immediately. 
`   `|| If the counter is zero, the calling thread blocks until another thread releases the semaphore.
| Signature:
`   `|| int SDL_SemWait(SDL_sem * sem);

| Return Value:
`   `|| **0** on success.
`   `|| **-1** on error.


# SDL_SemPost( )
| Purpose:
`   `|| Increments (or releases) an SDL semaphore.
`   `|| Potentially unblocks a thread that's currently waiting on that semaphore using **SDL_SemWait( )**.
| Signature:
`   `|| int SDL_SemPost(SDL_sem * sem);

| Return Value:
`   `|| **0** on success.
`   `|| **-1** on error.


# SDL_AtomicInit( )
| Purpose:
`   `|| Initializes an **SDL_atomic_t** variable for use with SDL's atomic operations.
`   `|| 
| Signature:
`   `|| int SDL_AtomicInit(SDL_atomic_t * a, int value);

| Return Value:
`   `|| **0** on success.
`   `|| **-1** on error.


# SDL_AtomicLock( )
| Purpose:
`   `|| Performs an atomic lock on a special variable of type **SDL_atomic_t**.
| Signature:
`   `|| void SDL_AtomicLock(SDL_atomic_t * a);


# SDL_AtomicUnlock( )
| Purpose:
`   `|| Releases an atomic lock previously acquired using **SDL_AtomicLock()**.
| Signature:
`   `|| void SDL_AtomicUnlock(SDL_atomic_t * a);

| Example:
```cpp
    SDL_atomic_t sharedCounter;
    SDL_AtomicInit(&sharedCounter, 0);

    // Thread 1:
    SDL_AtomicLock(&sharedCounter);
    sharedCounter.value += 1;
    SDL_AtomicUnlock(&sharedCounter);
    
    // Thread 2:
    SDL_AtomicLock(&sharedCounter);
    sharedCounter.value -= 1;
    SDL_AtomicUnlock(&sharedCounter);
```


# SDL_CreateMutex( )
| Purpose:
`   `|| Creates a mutex object.
| Signature:
`   `|| SDL_mutex * SDL_CreateMutex(void);


# SDL_DestroyMutex( )
| Purpose:
`   `|| Deallocates a mutex previously created using **SDL_CreateMutex()**.
| Signature:
`   `|| void SDL_DestroyMutex(SDL_mutex * m);


# SDL_LockMutex( )
| Purpose:
`   `|| Attempts to acquire ownership of a mutex.
| Signature:
`   `|| int SDL_LockMutex(SDL_mutex * m);

| Return Value:
`   `|| **0** on success.
`   `|| **-1** on error.


# SDL_UnlockMutex( )
| Purpose:
`   `|| Releases ownership of a mutex.
| Signature:
`   `|| int SDL_UnlockMutex(SDL_mutex * m);

| Return Value:
`   `|| **0** on success.
`   `|| **-1** on error.


# SDL_CreateCond( )
| Purpose:
`   `|| Creates a condition variable object in SDL2.
| Signature:
`   `|| SDL_cond * SDL_CreateCond(void);


# SDL_DestroyCond( )
| Purpose:
`   `|| Deallocates a condition variable object.
| Signature:
`   `|| void SDL_DestroyCond(SDL_cond * cond);


# SDL_CondWait( )
| Purpose:
`   `|| Causes the calling thread to wait on a condition variable **SDL_cond**.
`   `|| The thread effectively goes to sleep until another thread signals the condition variable 
`       `using **SDL_CondSignal( )** or **SDL_CondBroadcast()**.
`   `|| Crucially, it also temporarily releases an associated mutex (SDL_mutex), allowing other threads to work.

| Signature:
`   `|| int SDL_CondWait(SDL_cond * cond, SDL_mutex * m);

| Return Value:
`   `|| **0** on success.
`   `|| **-1** on error.


# SDL_CondSignal( )
| Purpose:
`   `|| Wakes up at least one thread that is currently waiting on a specified **SDL_cond**.
| Signature:
`   `|| int SDL_CondSignal();

| Return Value:
`   `|| **0** on success.
`   `|| **-1** on error.


# SDL_CondBroadcast( )
| Purpose:
`   `|| Wakes up all threads that are currently waiting on a specified **SDL_cond**.
| Signature:
`   `|| int SDL_CondBroadcast(SDL_cond * cond);

| Return Value:
`   `|| **0** on success.
`   `|| **-1** on error.


# SDL_Log( )
| Purpose:
`   `|| Provides a simple way to send log messages from your SDL2 application.
| Signature:
`   `|| void SDL_Log(const char * fmt, ...);


# SDL_Logxxx( )
| Purpose:
`   `|| A specialized logging function used to log warning messages within your SDL2 application.
| Signature:
`   `|| void SDL_LogInfo(SDL_LogCategory category, const char * fmt, ...);
`   `|| void SDL_LogWarn(SDL_LogCategory category, const char * fmt, ...);
`   `|| void SDL_LogError(SDL_LogCategory category, const char * fmt, ...);

| Possible **SDL_LogCategory** values:
`   `|| **SDL_LOG_CATEGORY_APPLICATION** for general messages related to your application logic.
`   `|| **SDL_LOG_CATEGORY_ASSERT** for messages related to assertion failures within your code.
`   `|| **SDL_LOG_CATEGORY_SYSTEM** for messages generated by lower-level system components.
`   `|| **SDL_LOG_CATEGORY_AUDIO** for messages related to audio.
`   `|| **SDL_LOG_CATEGORY_VIDEO** for messages related to video.
`   `|| **SDL_LOG_CATEGORY_RENDER** for messages related to the rendering pipeline, like OpenGL interations, etc.
`   `|| **SDL_LOG_CATEGORY_INPUT** for messages related to input events.
`   `|| **SDL_LOG_CATEGORY_TEST** for messages related to testing phases.


# SDL_CreateSystemCursor( )
| Purpose:
`   `|| Creates a new system cursor.
`   `|| Return value is easy to deduct.
| Signature:
`   `|| SDL_Cursor *  SDL_CreateSystemCursor(SDL_SystemCursor cursorId);
| @param **cursorId**:
`   `|| **SDL_SYSTEM_CURSOR_ARROW** for standard cursor.
`   `|| **SDL_SYSTEM_CURSOR_IBEAM** for text input cursor, an I-beam.
`   `|| **SDL_SYSTEM_CURSOR_WAIT** for an hourglass or spinning circle.
`   `|| **SDL_SYSTEM_CURSOR_CROSSHAIR** for denoting precise selection or placement.
`   `|| **SDL_SYSTEM_CURSOR_HAND** for a hand cursor.
`   `|| **SDL_SYSTEM_CURSOR_NO**
`   `|| **SDL_SYSTEM_CURSOR_SIZE**
`   `|| **SDL_SYSTEM_CURSOR_SIZEALL**
`   `|| **SDL_SYSTEM_CURSOR_SIZENESW**
`   `|| **SDL_SYSTEM_CURSOR_SIZENS**
`   `|| **SDL_SYSTEM_CURSOR_SIZEWE**
`   `|| **SDL_SYSTEM_CURSOR_ZOOM_IN**
`   `|| **SDL_SYSTEM_CURSOR_ZOOM_OUT**
`   `|| **SDL_SYSTEM_CURSOR_NO_DROP**
`   `|| **SDL_SYSTEM_CURSOR_DRAG**
`   `|| **SDL_SYSTEM_CURSOR_CONTEXT_MENU**
`   `|| **SDL_SYSTEM_CURSOR_PROGRESS**
`   `|| **SDL_SYSTEM_CURSOR_HELP**


# SDL_CreateCursor( )
| Purpose:
`   `|| Creats a self-defined cursor.
| Signature:
`   `|| SDL_Cursor * SDL_CreateCursor(const Uint8 * data,
`                                    `const Uint8 * mask,
`                                    `int w,
`                                    `int h
`                                    `int hot_x
`                                    `int hot_y);
| @param **data**:
`   `|| An array of bytes representing the pixel data for the cursor.
`   `|| The data is a bitmap, with 1 bit per pixel.
`   `|| For each byte, the most significant bit represents the leftmost pixel.
| @param **mask**:
`   `|| An array of bytes representing the mask for the cursor.
`   `|| The mask determines which pixel are visible (1 bit per pixel).
`   `|| If a bit in the mask is 1, its corresponding pixel is visible.
| @param **w**:
| @param **h**:
`   `|| The width and height of the cursor in pixels.
| @param **hot_x**:
| @param **hot_y**:
`   `|| The X- and Y-coordinate of the cursor's hot spot.
`   `|| The hot spot is the point within the cursor that is used to determine
`       `the location of the mouse event.

| Example:
```cpp
    int width = 8;
    int height = 8;

    Uint8 data[] = {
        0b00011000,     // 0
        0b00111100,     // 1
        0b01111110,     // 2
        0b00011000,     // 3
        0b00011000,     // 4
        0b00011000,     // 5
        0b00011000,     // 6
        0b00000000,     // 7
    };

    Uint8 mask[] = {
        0b00011000,     // 0
        0b00111100,     // 1
        0b01111110,     // 2
        0b00011000,     // 3
        0b00011000,     // 4
        0b00011000,     // 5
        0b00011000,     // 6
        0b00000000,     // 7
    };

    SDL_Cursor * customCursor = SDL_CreateCursor(
        data,
        mask,
        width,
        height,
        3,
        3
    );
    if ( !customCursor ) {
        ...
    }
    SDL_SetCursor( customCursor );
    ...
    SDL_FreeCursor( customCursor );
```


# SDL_CreateColorCursor( )
| Purpose:
`   `|| Create a cursor from a color surface.
| Signature:
`   `|| SDL_Cursor * SDL_CreateColorCursor(SDL_Surface * surface.
`                                         `int hot_x.
`                                         `int hot_y);

| Example:
```cpp
    SDL_Surface * theSurface = IMG_Load( "photo.png" );
    if ( !theSurface ) {
        ...
    }
    
    SDL_Surface * cursorSurface = SDL_CraeteRGBSurface(
        0, 32, 32, 32,
        0, 0, 0, 0
    );
    if ( !cursorSurface ) {
        ...
    }

    SDL_BlitScaled(theSurface, nullptr, cursorSurface, nullptr);

    SDL_Cursor * cursor = SDL_CreateColorCursor(cursorSurface, hot_x, hot_y);
    if ( !cursor ) {
        ...
    }
    ...
```


# SDL_FreeCursor( )
| Purpose:
`   `|| Free up the created cursor resource.
| Signature:
`   `|| void SDL_FreeCursor( SDL_Cursor * cursor );


# SDL_SetCursor( );
| Purpose:
`   `|| Set the cursor.
| Signature:
`   `|| void SDL_SetCursor( SDL_Cursor * cursor );





# SDL_Surface Structure
| **flags**:
`   `|| **Uint32**
`   `|| Containing information about the surface, is used for hardware acceleration.
| **format**:
`   `|| __SDL_PixelFormat *__
`   `|| Describing how pixel data is encoded within the surface.
| **w**:
| **h**:
`   `|| **int**
`   `|| width and height of the surface in pixels.
| **pixels**:
`   `|| __void *__
`   `|| A pointer to the actual raw pixel data of the surface.
| **userdata**:
`   `|| __void *__
`   `|| A pointer to your own custom data associated with a surface.
| **clip_rect**:
`   `|| **SDL_Rect**
`   `|| The clipping rectangle, pixels outside of it will not be drawn.
| **refcount**:
`   `|| **int**
`   `|| The reference count used for internal SDL management of the surface.
| etc...


# **SDL_PixelFormat** Structure
| **format**:
`   `|| **Uint32**
`   `|| An enumerated value representing a general pixel format,
`       `e.g. **SDL_PIXELFORMAT_RGB888**, **SDL_PIXELFORMAT_ARGB8888***, ...
| **palette**:
`   `|| __SDL_Palette*__
`   `|| If the surface is palettized (8-bit color depth or less),
`       `this points to a palette structure containing the actual color values.
| **BitsPerPixel**:
`   `|| **Uint8**
`   `|| Number of bits used to represent a single pixel.
| **BytesPerPixel**:
`   `|| **Uint8**
`   `|| Number of bytes used to store a single pixel.
| **Rmask**, **GMask**, **Bmask**, **Amask**:
`   `|| **Uint32**
`   `|| Bit masks indicating the position and size of the R,G,B,Alpha components within a single pixel value.
| **Rloss**, **Gloss** , **Bloss** , **Aloss**:
`   `|| **Uint8**
`   `|| The number of bits lost from the most significant end of each color component.
| **Rshift**, **Gshift**, **Bshift**, **Ashift**:
`   `|| **Uint8**
`   `|| The bit shifts needed to extract each color component.

| Example: 32-bit RGBA
| Imagine a format with Rmask=0xff000000, Gmask=0x00ff0000, Bmask=0x0000ff00, Amask=0x000000ff,
`   `Rshift=24, Gshift=16, Bshift=8, Ashift=0
`   `|| 1. You'd read a 32-bit value (4-bytes) from the surface's pixel data.
`   `|| 2. Apply the masks using bitwise AND to get the individual color components.
`   `|| 3. The RED value would be (pixelValue & Rmask) >> 24 based on the Rshift.


# SDL_Rect Structure
| **x**:
| **y**:
`   `|| **int**
`   `|| X- and Y-coordinate of the top-left corner of the rectangle.
| **w**:
| **h**:
`   `|| **int**
`   `|| width and height of the rectangle.


# SDL_Event Structure
| Description:
`   `|| An **union** that contains structures for different event types.
| In C Code Representation:
```c
    typedef union SDL_Event {
        Uint32 type;                    // The event type
        SDL_CommonEvent   common;       // Common event data
        SDL_WindowEvent   window;       // Window event data
        SDL_KeyboardEvent key;          // Keyboard event data
        
        SDL_QuitEvent quit;             // Quit event data
        SDL_UserEvent user;             // Custom user event data
        
        SDL_TextEditingEvent edit;      // Text editing event data
        SDL_TextInputEvent   text;      // Text input event data
        
        SDL_MouseMotionEvent motion;    // Mouse motion event data
        SDL_MouseButtonEvent button;    // Mouse button event data
        SDL_MouseWheelEvent  wheel;     // Mouse wheel event data
        
        SDL_TouchFingerEvent   tfinger;     // Touch finger event data
        SDL_MultiGestureEvent  mgesture;    // Multi gesture event data
        SDL_DollarGestureEvent dgesture;    // Dollar gesture event data
        
        SDL_JoyAxisEvent   jaxis;       // Joystick axis event data
        SDL_JoyBallEvent   jball;       // Joystick ball event data
        SDL_JoyHatEvent    jhat;        // Joystick hat event data
        SDL_JoyButtonEvent jbutton;     // Joystick button event data
        SDL_JoyDeviceEvent jdevice;     // Joystick device event data
        
        SDL_ControllerAxisEvent   caxis;        // Game controller axis event data
        SDL_ControllerButtonEvent cbutton;      // Game controller button event data
        SDL_ControllerDeviceEvent cdevice;      // Game controller device event data
        SDL_AudioDeviceEvent      adevice;      // Audio device event data
        
        SDL_SysWMEvent syswm;               // System specific window manager event
        SDL_DropEvent   drop;               // Drag and drop event data
        SDL_SensorEvent sensor;             // Sensor event data
        // Other event structures...
    } SDL_Event;
```

| **type**:

| Corresponding Event Data Field in the Union | Event Type |
| :-- | :-- |
| SDL_KeyboardEvent | SDL_KEYDOWN, SDL_KEYUP |
| | |
| SDL_QuitEvent | SDL_QUIT |
| | |
| SDL_MouseMotionEvent | SDL_MOUSEMOTION |
| | |
| SDL_MouseButtonEvent | SDL_MOUSEBUTTONDOWN, SDL_MOUSEBUTTONUP |
| | |
| SDL_MouseWheelEvent | SDL_MOUSEWHEEL |
| | |
| SDL_UserEvent | SDL_USEREVENT |
| | |
| SDL_WindowEvent | SDL_WINDOWEVENT |
| | |
| SDL_TextInputEvent | SDL_TEXTINPUT |
| | |
| SDL_TextEditingEvent | SDL_TEXTEDITING |
| | |
| SDL_TouchFingerEvent | SDL_FINGERMOTION, SDL_FINGERDOWN, SDL_FINGERUP |
| | |
| SDL_DropEvent | SDL_DROPFILE. SDL_DROPTEXT, SDL_DROPBEGIN, SDL_DROPCOMPLETE |
| | |
| SDL_DisplayEvent | SDL_DISPLAYEVENT |
| | |
| ... | ... |

| Important Notes:
`   `|| The SDL Wiki has excellent documentation on available event types and their specific members: 
`       `https://wiki.libsdl.org/SDL_Event
`   `|| SDL allows the creation of custom event types, so the **SDL_Event** structure is extensible.

| For **SDL_QuitEvent**
```cpp
    /* Much Simplified Code... */
    SDL_Event e;
    for (;;) {
        SDL_PollEvent(&);
        if ( e.type == SDL_QUIT ) {
            SDL_Log( "Program quit after %i ticks\n", e.quit.timestamp );
            break;
        }
    }
```


# SDL_KeyboardEvent structure
| **type**:
`   `|| **Uint8**
`   `|| Will be either **SDL_KEYDOWN** or **SDL_KEYUP**.
| **timestamp**:
`   `|| **Uint32**
`   `|| The timestamp in milliseconds when the event occurred.
| **windowID**:
`   `|| **Uint32**
`   `|| The ID of the window where the event took place.
| **state**:
`   `|| **Uint8**
`   `|| Will be either **SDL_PRESSED** or **SDL_RELEASED**.
| **repeat**:
`   `|| **Uint8**
`   `|| **Non-0** value when a key is held down, **0** if it's a single press or release.
| **keysym**:
`   `|| **SDL_Keysym**
`   `|| The most important inner-structure in this structure.

# SDL_Keysym structure
| **scancode**:
`   `|| **SDL_Scancode**
`   `|| Platform-specific hardware scnacode for the key.
| **sym**:
`   `|| **SDLKey**
`   `|| An **SDLKey** enum value representing the logical key,
`       `more portable than scancode.
| **mod**:
`   `|| **Uint16**
`   `|| A bitmask representing the state of the modifier keys (ALT, CTRL, SHIFT, ...)
`   `|| See **SDL_Keymod** values like **KMOD_CTRL**, **KMOD_SHIFT**, **KMOD_ALT**, **KMOD_GUI**(Window Key or Mac Command Key)**...

# SDLKey enum
| Alphanumeric Values:
`   `|| **SDL_a** to **SDL_z** and **SDL_0** to **SDL_9**.
| Modifier Keys:
`   `|| **SDLK_LCTRL**, **SDLK_RSHIFT**, **SDLK_LALT**, **SDLK_CAPSLOCK**, ...
| Function Keys:
`   `|| **SDLK_F1** to **SDLK_F15**.
| Arrow Keys:
`   `|| **SDLK_UP**, **SDLK_DOWN**, **SDLK_LEFT**, **SDLK_RIGHT**.
| Special Keys:
`   `|| **SDLK_RETURN**, **SDLK_ESCAPE**, **SDLK_SPACE**, **SDLK_BACKSPACE**.


# SDL_Point Structure
```c
    typedef struct SDL_Point
    {
        int x;
        int y;
    } SDL_Point;
```

# SDL_Color Structure
```c
    typedef struct SDL_Color
    {
        Uint8 r;    // Red   component (0 - 255)
        Uint8 g;    // Green component (0 - 255)
        Uint8 b;    // Blue  component (0 - 255)
        Uint8 a;    // Alpha component (opacity, 0 - 255)
    } SDL_Color;
```


# SDL_MouseMotionEvent
| e.type == **SDL_MOUSEMOTION**
```c
    // SDL_MouseMotionEvent motion;
    // e.motion:
    typedef struct SDL_MouseMotionEvent
    {
        Uint32 timestamp;   // Timestamp of the event
        Uint32 windowID;    // ID of the window where the mouse event occurred
        Uint32 which;       // ID of the mouse device (or SDL_TOUCH_MOUSEID for touch events)
        Uint32 state;       // Bitmask representing the current button state
                            // if (e.motion.state & SDL_BUTTON(SDL_BUTTON_RIGHT)) ...handle right click 
        Sint32 x;           // X coordinate (relative to the window)
        Sint32 y;           // Y coordinate (relative to the window)
        Sint32 xrel;        // Relative motion in the X direction
        Sint32 yrel;        // Relative motion in the Y direction
    } SDL_MouseMotionEvent;
```


# SDL_MouseButtonEvent
| e.type == **SDL_MOUSEBUTTONDOWN**
| e.type == **SDL_MOUSEBUTTONUP**
```c
    // SDL_MouseButtonEvent button;
    // e.button:
    typedef struct SDL_MouseButtonEvent
    {
        Uint32 timestamp;   // Timestamp of the event
        Uint32 windowID;    // ID of the window where the mouse event occurred
        Uint32 which;       // ID of the mouse (or SDL_TOUCH_MOUSEID for touch events)
        Uint8  button;      // The mouse button index (SDL_BUTTON_LEFT, SDL_BUTTON_RIGHT, xxx_MIDDLE, ...)
        Uint8  state;       // Pressed (SDL_PRESSED) or Released (SDL_RELEASED)
        Uint8  clicks;      // Number of clicks (e.g., for double-click detection)
        Sint32 x;           // X coordinate (relative to the window)
        Sint32 y;           // Y coordinate (relative to the window)
    } SDL_MouseButtonEvent;
```

# SDL_MouseWheelEvent
| e.type == **SDL_MouseWheelEvent**
```c
    // SDL_MouseWheelEvent wheel;
    // e.wheel:
    typedef struct SDL_MouseWheelEvent
    {
        Uint32 timestamp;   // Timestamp of the event
        Uint32 windowID;    // ID of the window where the mouse event occurred
        Uint32 which;       // ID of the mouse (or SDL_TOUCH_MOUSEID for touch events)
        Sint32 x;           // Amount of scrolling in the X direction (usually positive for up)
        Sint32 y;           // Amount of scrolling in the Y direction (usually positive for up)
        Uint32 direction;   // Scrolling direction (SDL_MOUSEWHEEL_NORMAL or SDL_MOUSEWHEEL_FLIPPED)
    } SDL_MouseWheelEvent;
```


# SDL_UserEvent
```c
    // SDL_UserEvent user;
    // e.user:
    typedef struct SDL_UserEvent
    {
        Uint32 timestamp;   // Timestamp of the event
        Uint32 type;        // User-defined event code
        Uint32 code;        // Additional user-defined data
        void * data1;       // User-defined data pointer 1
        void * data2;       // User-defined data pointer 2
    } SDL_UserEvent;
```


# SDL_TextInputEvent
| e.type == **SDL_TEXTINPUT**
```c
    // SDL_TextInputEvent text;
    // e.text:
    typedef struct SDL_TextInputEvent
    {
        Uint32 timestamp;  // Timestamp of the event
        Uint32 windowID;   // ID of the window where text input occurred
        char   text[SDL_TEXTINPUTEVENT_TEXT_SIZE];  // Array to hold the input text
    } SDL_TextInputEvent;
```


# SDL_TextEditingEvent
| e.type == **SDL_TEXTEDITING**
```c
    // SDL_TextEditingEvent edit;
    // e.edit:
    typedef struct SDL_TextEditingEvent
    {
        Uint32 timestamp;   // Timestamp of the event
        Uint32 windowID;    // ID of the window where text editing is happening
        char text[SDL_TEXTEDITINGEVENT_TEXT_SIZE];  // The current text being edited
        int start;          // Start index of the selected text (or cursor position)
        int length;         // Length of the selected text
    } SDL_TextEditingEvent;
```


# SDL_WindowEvent
| e.type == **SDL_WINDOWEVENT**
| e.window.event == 
`   `**SDL_WINDOWEVENT_{SHOWN, HIDDEN, EXPOSED, MOVED, RESIZED, MINIMIZED, MAXIMIZED, RESTORED, FOCUS_GAINED, FOCUS_LOST, ENTER, LEAVE, CLOSE}**
```c
    // SDL_WindowEvent window;
    // e.window:
    typedef struct SDL_WindowEvent
    {
        Uint32 timestamp;   // Timestamp of the event
        Uint32 windowID;    // ID of the window that the event is associated with
        Uint8  event;       // Event code (SDL_WINDOWEVENT_SHOWN, SDL_WINDOWEVENT_RESIZED, etc.)
        Uint8  padding1;
        Uint8  padding2;
        Uint8  padding3;
        Sint32 data1;       // Event-specific data (e.g., new width/height for resize events)
        Sint32 data2;       // Additional event-specific data 
    } SDL_WindowEvent;
```

# SDL_TouchFingerEvent


# SDL_DisplayMode Structure


# SDL_Cursor Structure



# SDL_AudioSpec Structure
```C
    typedef struct SDL_AudioSpec
    {
        int    freq;                // Audio frequency in samples per second (e.g., 44100Hz)
        Uint16 format;              // Audio format (e.g., AUDIO_S16LSB for signed 16-bit)
        Uint8  channels;            // Number of channels (1 for mono, 2 for stereo)
        Uint8  silence;             // Audio buffer silence value 
        Uint16 samples;             // Audio buffer size in samples (lower for lower latency)
        Uint32 size;                // Audio buffer size in bytes (optional)
        SDL_AudioCallback callback; // Callback function for on-demand audio
        void * userdata;            // Custom data pointer passed to the callback 
    } SDL_AudioSpec;
```


# SDL_SpinLock



# SDL_bool Type
| Example:
```c
    SDL_bool done;
    SDL_Event event;
    
    done = SDL_FALSE;
    while ( !done ) {
        while ( !done && SDL_PollEvent(&event) ) {
            ...
            done = SDL_TRUE;
        }
    }
    
```






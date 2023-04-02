#! https://zhuanlan.zhihu.com/p/600361110
# SDL学习

## 初始化窗口并创建渲染器

### 基本版本

```c++
void Initialize(const char *title, int mainWindow_w, int mainWindow_h) {
    mainWindow = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, mainWindow_w, mainWindow_h,
                                  SDL_WINDOW_SHOWN);
    mainRenderer = SDL_CreateRenderer(mainWindow, -1, SDL_RENDERER_ACCELERATED);
}
```

### 另一个版本

```c++
bool init(){
    //初始化标志
    bool success = true;

    //初始化SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        success = false;
    }
    else
    {
        //创建窗口
        gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( gWindow == NULL )
        {
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
            success = false;
        }
        else
        {
            //获取窗口表面
            gScreenSurface = SDL_GetWindowSurface( gWindow );
        }
    }

    return success;
}
```

该版本判断了是否成功创建了窗口，并且使用gScreenSurface来获取整个窗口的表面

##  退出函数

```c++
void Quit() {
    SDL_DestroyRenderer(mainRenderer);
    SDL_DestroyWindow(mainWindow);
    SDL_FreeSurface(gScreenSurface);
    SDL_Quit();
}
```

## 加载图片文件

```c++
void LoadImage(const char *directory, int x = -1, int y = -1, int w = -1, int h = -1) {
    //加载图片
    SDL_Surface *LoadingSurface = IMG_Load(directory);
    if (LoadingSurface == nullptr) {
        std::cout << "Loading Failed" << std::endl;
        return;
    }
    SDL_Texture *LoadingTexture = SDL_CreateTextureFromSurface(mainRenderer, LoadingSurface);
    SDL_Rect LoadingRect;
    LoadingRect.x = x;
    LoadingRect.y = y;
    if (h != -1)
        LoadingRect.h = h;
    else
        LoadingRect.h = LoadingSurface->h;
    if (w != -1)
        LoadingRect.w = w;
    else
        LoadingRect.w = LoadingSurface->w;
    //应用图像
    SDL_BlitScaled( gStretchedSurface, NULL, gScreenSurface, &stretchRect );
    //更新表面
    SDL_UpdateWindowSurface( gWindow );
    //释放资源
    SDL_FreeSurface(LoadingSurface);
    SDL_DestroyTexture(LoadingTexture);
}
```

转换图片格式为屏幕格式

```c++
SDL_Texture* loadTexture( std::string path ){
    //最终的纹理
    SDL_Texture* newTexture = NULL;

    //在指定路径加载图像
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    }
    else
    {
        //用表面像素创建纹理
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
        if( newTexture == NULL )
        {
            printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }

        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }

    return newTexture;
```



## 主事件监听

```c++
while (SDL_WaitEvent(&MainEvent)) {
        switch (MainEvent.type) {
            case SDL_QUIT://点击那个关闭按钮
                Quit();
                break;
            case SDL_KEYDOWN://键盘事件
                switch (MainEvent.key.keysym.sym) {
                    case SDLK_RETURN: //return就是回车
                        Quit();
                        break;
                    case SDLK_ESCAPE://esc键
                        Quit();
                        break;
                    default:
                        break;
                }
                break;
            case SDL_MOUSEBUTTONDOWN://鼠标点击
                printf_s("(%d,%d)\n", MainEvent.button.x, MainEvent.button.y);
                break;
            case SDL_MOUSEBUTTONUP://鼠标抬起
                break;
            case SDL_MOUSEMOTION://鼠标移动
                break;
            default:
                break;
        }
    }
```

## 计时器

### 按照固定时间间隔的方式

 SDL_TimerID SDL_AddTimer(Uint32 interval, SDL_TimerCallback callback, void *param):向系统请求增加一个定时器.

- SDL_TimerID： 定时器的ID,若该值为NULL，表示请求失败，通过这个ID访问定时器;
-  interval: 定时间隔;
- callback: 回调函数指针,定时时间到后会调用此函数;
- param:传递给callback的参数
- return interval : 该函数返回值为下次唤醒的时长,若返回0,则不会再唤醒。

 callback 函数形式：

```c++
Uint32 callback(uint32 interval, void * param){
	//do something
    return interval;
}
```



### 直接取到系统时间的方式

```c++
Uint32 time = 0;
Uint32 start = 0;//这个声明为全局变量，获取开始时间
start = SDL_GetTicks();
time = SDL_GetTicks() - start;
```

然后判断time就可以知道现在的时间距离开始运行的间隔了


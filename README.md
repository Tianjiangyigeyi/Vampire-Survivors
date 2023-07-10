# Vampire-Survivors
 吸血鬼幸存者的OpenGL实现

## 编译相关

在根目录下进入终端，输入以下命令即可运行：

```
make -j
./output/main
```

- 强烈建议在每次对代码进行较大改动时删除所有生成的**.o文件**，运行`del.bat`即可。

## 框架说明

- **common层**中的config.h理应是所有宏定义之所在，目前仍有许多常量未满足该设计要求，**后续编写过程中如有常量请在config.h中声明**
- **viewmodel层**封装了着色器类、纹理类、渲染精灵类、工具类、GameObject类（GameObject可以转移到view层中），代码还会有改动但是接口不会改变。
  - 重点说明工具类(Utility)中有一些很有用的函数，最好能理解。
- **view层**尚未完成，需要你去重写，请先理解目录下的Game和PlayerObject两个类再进行代码的编写，注意：
  - 取消了new对象时设置size，默认会将size设为和纹理一样大，你可以通过先getsize再setsize的方式调整大小
  - 当你要使用一个纹理时，请在`Utility::Init`下面 Load 你想要的纹理，并记住第三个参数以便后续使用时直接`ResourceManager::GetTexture`。这样设计的目的是使你能灵活地选择你需要的纹理。（显然这样做是提高了耦合性的，但是考虑到未来引进UI后很有可能会重写加载纹理的手段，留待后续重构）

- **app层**已经封装完毕，其向Game传递了deltatime(dt)(每一帧的间隔时间)

- `main.cpp`，程序入口，直接调用app层

- `precomp.cpp`/`precomp.h`，预编译头，请在每次需要包含如下库时选择`#include "../precomp.h"`

  ```cpp
  #include "glad/glad.h"
  #include "GLFW/glfw3.h"
  #include <glm/glm.hpp>
  #include <glm/gtc/matrix_transform.hpp>
  #include <glm/gtc/type_ptr.hpp>
  ```



综上，为了确保能最高效率地进行view层地开发，请至少阅读并理解以下文件：

```
config.h
GameObject.h
ResourceManager.h
Utility.h
Game.h
Game.cpp
PlayerObject.h
PlayerObject.cpp
precomp.h
```



----



## 第二次说明

- 框架有较大变化，**本质没有改变**，希望可以应付过中期检查😊。

- **notification和command**尚未实现，可能需要用到的地方我打上了TODO（目前：1个）。

- **view层已不再包含viewmodel层的头文件**，事实上耦合的问题**并未解决**！只是将矛盾转移到了`Util`和`config`中。

- `Util`该文件夹将所有工具类打包，有以下两个好处：

  - 需要调用诸如纹理等工具时，不需要在include一堆头文件，事实上，任何文件只需要包含以下头文件即可

    ```cpp
    #include "../common/config.h"
    #include "../util/Utility.h"
    #include "../precomp.h"
    ```

- 你将继续完成编写，工作流稍有变化：
  1. obj的声明都放在了`/common/config`里面，而实现都在`/viewmodel/Objects_vm`中，由于将声明提前，为了避免头文件循环包含的问题，每个obj的`Sprite`成员都设置为了`std::string`，所以你需要在使用纹理时用到`ResourceManager::GetTexture(Sprite);`
  2. 原先的`Game.cpp`的代码基本没有改动，而是分布在了`/view/GameView`和`/viewmodel/GameViewmodel`两个cpp文件中，你依然可以按照原来的workflow进行开发，只需要注意“this不再是Game对象，game才是Game对象”。

- 关于闪退：目前发生的闪退问题百分之九十九都是`LoadTexture`时关于第二个参数是`true`还是`false`的问题，建议重点关注这里，原则是当你发现图片为花灰色时肯定要改动这里。

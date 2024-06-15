- # 《屏幕兄弟ScreenBro》

  ## 一款用SDL2和C++开发的窗口射击游戏

  **开发环境:** `Visual Studio` |
  **SDL2版本:** `2.30.3` |
  **SDL2_image版本:** `2.8.2` |
  **SDL2_ttf版本:** `2.22.0` 


---

  ## 游戏特点：

  - 角色可以跨越多个不同窗口
  - 按"K"键跨越窗口

  <img src="https://github.com/kevinwu06/ScreenBro/assets/120035670/f16adf45-52f6-473b-ae12-d920ecb06392" alt="开始页面" style="zoom: 19%;" /><img src="https://github.com/kevinwu06/ScreenBro/assets/120035670/cccbc4eb-8736-4583-8383-450fab64d692" alt="游戏画面" style="zoom:12%;" />


---

  ## 游戏更新日志

  开发日志在[bilibili账号](https://space.bilibili.com/358065206)持续更新

  1. [【SDL C++】跨越窗口的射击游戏？| 开发日志01](https://www.bilibili.com/video/BV1JD421373v/)

  2. [【SDL C++】适合边看番，边玩的游戏？| 开发日志02](https://www.bilibili.com/video/BV1ww4m1v7St/)

  3. [【SDL C++】跨越窗口的射击游戏 | 开发日志03](https://www.bilibili.com/video/BV1JS411N7eV/)

---

  ## 启动项目

  > 本项目为源码暂仅支持windows环境下用VS环境启动

  SDL的引用方法可自行上网看教程，此处简略说明操作：

  1. 安装sdl库：[SDL库](https://github.com/libsdl-org) <br>
     需要下载的库（在release中找到带`devel`和`VC`后缀的）：<br>
       SDL2版本: [SDL2-devel-2.30.3-VC.zip](https://github.com/libsdl-org/SDL/releases/download/release-2.30.3/SDL2-devel-2.30.3-VC.zip) <br>
       SDL2_image版本: [SDL2_image-devel-2.8.2-VC.zip](https://github.com/libsdl-org/SDL_image/releases/download/release-2.8.2/SDL2_image-devel-2.8.2-VC.zip) <br>
       SDL2_ttf版本: [SDL2_ttf-devel-2.22.0-VC.zip](https://github.com/libsdl-org/SDL_ttf/releases/download/release-2.22.0/SDL2_ttf-devel-2.22.0-VC.zip) 


  3. 使用VS打开`.sln`项目解决方案文件

  4. 在`项目设置`中引用并链接安装好的SDL库
     VC++目录>包含目录：链接到`include`文件夹
     VC++目录>库目录：连接到`lib/x64`文件夹
     连接器>输入>附加依赖项：输入`SDL2.lib;SDL2main.lib;SDL2_image.lib;SDL2_ttf.lib;`

  5. 在尝试运行后，将各个库中的`lib/x64`文件夹中的`.dll`文件复制到项目的`x64/Debug`文件夹中

  > 项目后续还会添加使用更多库，会在最顶上说明使用版本，引用操作是一样的，此处不再更新

---

  ## 关于

  本项目持续更新，感兴趣可以点个Star⭐

  如果有建议，欢迎在b站或者issue提出~

  如有其余问题，本人联系方式：

  - 🐧：3094886053
  - ✉️：kevinwu06@163.com

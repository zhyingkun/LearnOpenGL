# LearnOpenGL

[![Build Status](https://travis-ci.com/zhyingkun/LearnOpenGL.svg)](https://travis-ci.com/zhyingkun/LearnOpenGL)

---

## 基本介绍

1. 这是根据网站 [LearnOpenGL-CN](https://learnopengl-cn.github.io) 的介绍构建出来的 OpenGL 工程
2. 采用 C++ 实现，其中用到了众多开源库
3. 在这里整个工程采用 cmake 管理编译过程，包括开源库的构建过程（抛弃了开源库自身的编译构建过程）
4. 整个工程能完整的用 Xcode 或 Visual Studio 进行调试（包括用到的开源库）
5. 包含了 Unity 对于同样效果实现的工程

---

## 如何编译

#### 1. 在 Mac 上采用 Xcode 编译

```bash
cd LearnOpenGL
mkdir buildXcode && cd buildXcode
cmake -G "Xcode" ..
```

此时已经在 buildXcode 文件夹下生成了 Xcode 工程，双击打开并编译即可

#### 2. 直接命令行编译（支持 Mac 和 Linux）

```bash
cd LearnOpenGL
mkdir build && cd build
cmake .. # default is Debug
# for Debug: cmake -DCMAKE_BUILD_TYPE=Debug ..
# for Release: cmake -DCMAKE_BUILD_TYPE=Release ..
make
```

make 命令会自动编译好可执行文件

#### 3. 在 Windows 上使用 Cygwin + Visual Studio 2017 进行编译

```bash
cd LearnOpenGL
mkdir buildVS && cd buildVS
cmake -G "Visual Studio 15 2017 Win64" ..
```

此时已经在 buildVS 文件夹下生成了 Visual Studio 工程，双击打开并编译即可

---

## 文件夹说明

1. app：用于存放所有 OpenGL 应用，包括代码和资源

   - common：所有 Demo 都会用到的公共代码
   - resources：Demo 用到的资源，包括贴图、模型等
   - template：模板示例代码
   - base：基本教程内容
   - lighting：光照模拟
   - assimp：Assert Import，模型导入

2. demo：基础的示例工程

   - glfw-win：最简单的创建一个窗口
   - matrix-calculator：通过 glm 计算矩阵

3. libs：整个工程用到的开源库

   - glfw：代码来自[https://github.com/glfw/glfw]
   - glad：代码来自[https://github.com/Dav1dde/glad]
   - glm：代码来自[https://github.com/g-truc/glm]
   - stb：代码来自[https://github.com/nothings/stb]

4. SimulateOpenGL：这是一个 Unity2017 工程，用于说明 Unity 的渲染流程类似 OpenGL（针对 app 文件夹中的所有应用，都对应 Unity 中的一个场景，力图做到类似的输入数据得到类似的结果！）

5. 所有 CMakeLists.txt 文件：用于管理整个工程的构建过程

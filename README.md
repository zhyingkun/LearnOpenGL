# LearnOpenGL

----

## 基本介绍

1. 这是根据网站 https://learnopengl-cn.github.io 的介绍构建出来的OpenGL工程
2. 采用C/C++实现，其中用到了众多开源库
3. 在这里整个工程采用cmake管理编译过程，包括开源库的构建过程（抛弃了开源库自身的编译构建过程）
4. 整个工程能完整的用 Xcode 或 Visual Studio 调试（包括用到的开源库）

----

## 如何编译

1. 在Mac上采用Xcode编译
```bash
cd LearnOpenGL
mkdir buildXcode && cd buildXcode
cmake -G "Xcode" ..
```
此时已经在buildXcode文件夹下生成了Xcode工程，双击打开并编译即可

2. 直接命令行编译（支持Mac和Linux）
```bash
cd LearnOpenGL
mkdir build &&cd build
cmake ..
make
```
make命令会自动编译好可执行文件

3. 在Windows上使用Cygwin + Visual Studio 2017进行编译
```bash
cd LearnOpenGL
mkdir buildVS && cd buildVS
cmake -G "Visual Studio 15 2017 Win64" ..
```
此时已经在buildVS文件夹下生成了Visual Studio工程，双击打开并编译即可

----

## 文件夹说明

1. app文件夹：用于存放所有Demo，包括代码和资源
	>a. common：所有Demo都会用到的公共代码

	>b. demo name：某个OpenGL示例的名称，app文件夹下包含多个示例
		(a). src：本示例用到的C/C++代码
		(b). shaders : OpenGL着色器代码
		(c). textures : 贴图文件，其实就是图片

2. libs：整个工程用到的开源库
	>a. glfw：代码来自[https://github.com/glfw/glfw]

	>b. glad：代码来自[https://github.com/Dav1dde/glad]

	>c. glm：代码来自[https://github.com/g-truc/glm]

	>d. stb_image：代码来自[https://github.com/nothings/stb]

3. 本工程所有CMakeLists.txt文件：用于管理整个工程的构建过程

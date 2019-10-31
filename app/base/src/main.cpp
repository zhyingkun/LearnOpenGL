#include <iostream>
using namespace std;

#include "base.h"

#ifdef _WIN32
// For Visual Studio
const char* pVertexShaderPath = "../../../../app/base/shaders/vertexshader.vert";
const char* pFragmentShaderPath = "../../../../app/base/shaders/fragmentshader.frag";
const char* pContainerJpgPath = "../../../../app/resources/textures/container.jpg";
const char* pAwesomefacePngPath = "../../../../app/resources/textures/awesomeface.png";
#elif __APPLE__
// For Xcode App
const char* pVertexShaderPath = "../Resources/vertexshader.vert";
const char* pFragmentShaderPath = "../Resources/fragmentshader.frag";
const char* pContainerJpgPath = "../Resources/container.jpg";
const char* pAwesomefacePngPath = "../Resources/awesomeface.png";
// const char *pVertexShaderPath   = "../../../app/base/shaders/vertexshader.vert";
// const char *pFragmentShaderPath = "../../../app/base/shaders/fragmentshader.frag";
// const char *pContainerJpgPath   = "../../../app/resources/textures/container.jpg";
// const char *pAwesomefacePngPath = "../../../app/resources/textures/awesomeface.png";
#elif __linux__
// For VSCode
const char* pVertexShaderPath = "../../../app/base/shaders/vertexshader.vert";
const char* pFragmentShaderPath = "../../../app/base/shaders/fragmentshader.frag";
const char* pContainerJpgPath = "../../../app/resources/textures/container.jpg";
const char* pAwesomefacePngPath = "../../../app/resources/textures/awesomeface.png";
#endif

extern BaseApp baseMain;

int main(int argc, char* argv[]) {
  (void)argc;
  (void)argv;
  cout << "base app start..." << endl;
  // Init glfw window
  baseMain.InitializeGLFW();
  baseMain.CreateWinAndSetWinCallback();
  baseMain.LoadOpenGLFunctions();
  baseMain.BuildAndCompileBoxShader(pVertexShaderPath, pFragmentShaderPath);
  baseMain.LoadAllTextures(pContainerJpgPath, pAwesomefacePngPath);
  baseMain.SetTexturesToBoxShader();
  baseMain.ConfigOpenGLUtil();
  baseMain.CreateVertexArrayObject();
  baseMain.RenderLoop();
  baseMain.Terminate();
  return 0;
}

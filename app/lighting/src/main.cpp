#include <iostream>
using namespace std;

#include "lighting.h"

#ifdef _WIN32
// For Debug in Visual Studio
const char* pVertexShaderPath = "../../../app/lighting/shaders/vertexshader.vert";
const char* pFragmentShaderPath = "../../../app/lighting/shaders/fragmentshader.frag";
const char* pLightVertPath = "../../../app/lighting/shaders/light.vert";
const char* pLightFragPath = "../../../app/lighting/shaders/light.frag";
// For Run alone
// const char* pVertexShaderPath = "../../../../app/lighting/shaders/vertexshader.vert";
// const char* pFragmentShaderPath = "../../../../app/lighting/shaders/fragmentshader.frag";
// const char* pLightVertPath = "../../../../app/lighting/shaders/light.vert";
// const char* pLightFragPath = "../../../../app/lighting/shaders/light.frag";
#elif __APPLE__
// For Xcode App
const char* pVertexShaderPath = "../Resources/vertexshader.vert";
const char* pFragmentShaderPath = "../Resources/fragmentshader.frag";
const char* pLightVertPath = "../Resources/light.vert";
const char* pLightFragPath = "../Resources/light.frag";
// const char *pVertexShaderPath   = "../../../app/lighting/shaders/vertexshader.vert";
// const char *pFragmentShaderPath = "../../../app/lighting/shaders/fragmentshader.frag";
// const char *pLightVertPath      = "../../../app/lighting/shaders/light.vert";
// const char *pLightFragPath      = "../../../app/lighting/shaders/light.frag";
#elif __linux__
// For VSCode
const char* pVertexShaderPath = "../../../app/lighting/shaders/vertexshader.vert";
const char* pFragmentShaderPath = "../../../app/lighting/shaders/fragmentshader.frag";
const char* pLightVertPath = "../../../app/lighting/shaders/light.vert";
const char* pLightFragPath = "../../../app/lighting/shaders/light.frag";
#endif

extern LightingApp lightingMain;

int main(int argc, char* argv[]) {
  (void)argc;
  (void)argv;
  cout << "base app start..." << endl;
  lightingMain.InitializeGLFW();
  lightingMain.CreateWinAndSetWinCallback("lighting");
  lightingMain.LoadOpenGLFunctions();
  lightingMain.BuildAndCompileBoxShader(pVertexShaderPath, pFragmentShaderPath);
  lightingMain.BuildAndCompileLightShader(pLightVertPath, pLightFragPath);
  // lightingMain.LoadAllTextures(, );
  // lightingMain.SetTexturesToBoxShader();
  lightingMain.ConfigOpenGLUtil();
  lightingMain.CreateVertexArrayObject();
  lightingMain.RenderLoop();
  lightingMain.Terminate();
  return 0;
}

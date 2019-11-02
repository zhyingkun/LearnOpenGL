#include <iostream>
using namespace std;

#include "lighting.h"

#ifdef _WIN32
// For Debug in Visual Studio
const char* pVertexShaderPath = "../../../app/lighting/shaders/vertexshader.vert";
const char* pFragmentShaderPath = "../../../app/lighting/shaders/fragmentshader.frag";
const char* pLightVertPath = "../../../app/lighting/shaders/light.vert";
const char* pLightFragPath = "../../../app/lighting/shaders/light.frag";
const char* pContainer2PngPath = "../../../app/resources/textures/container2.png";
const char* pContainer2SpecularPngPath = "../../../app/resources/textures/container2_specular.png";
// For Run alone
// const char* pVertexShaderPath = "../../../../app/lighting/shaders/vertexshader.vert";
// const char* pFragmentShaderPath = "../../../../app/lighting/shaders/fragmentshader.frag";
// const char* pLightVertPath = "../../../../app/lighting/shaders/light.vert";
// const char* pLightFragPath = "../../../../app/lighting/shaders/light.frag";
// const char* pContainer2PngPath = "../../../../app/resources/textures/container2.png";
// const char* pContainer2SpecularPngPath = "../../../../app/resources/textures/container2_specular.png";
#elif __APPLE__
// For Xcode App
const char* pVertexShaderPath = "../Resources/vertexshader.vert";
const char* pFragmentShaderPath = "../Resources/fragmentshader.frag";
const char* pLightVertPath = "../Resources/light.vert";
const char* pLightFragPath = "../Resources/light.frag";
const char* pContainer2PngPath = "../Resources/container2.png";
const char* pContainer2SpecularPngPath = "../Resources/container2_specular.png";
// For VSCode
// const char *pVertexShaderPath   = "../../../app/lighting/shaders/vertexshader.vert";
// const char *pFragmentShaderPath = "../../../app/lighting/shaders/fragmentshader.frag";
// const char *pLightVertPath      = "../../../app/lighting/shaders/light.vert";
// const char *pLightFragPath      = "../../../app/lighting/shaders/light.frag";
// const char* pContainer2PngPath = "../../../app/resources/textures/container2.png";
// const char* pContainer2SpecularPngPath = "../../../app/resources/textures/container2_specular.png";
#elif __linux__
// For VSCode
const char* pVertexShaderPath = "../../../app/lighting/shaders/vertexshader.vert";
const char* pFragmentShaderPath = "../../../app/lighting/shaders/fragmentshader.frag";
const char* pLightVertPath = "../../../app/lighting/shaders/light.vert";
const char* pLightFragPath = "../../../app/lighting/shaders/light.frag";
const char* pContainer2PngPath = "../../../app/resources/textures/container2.png";
const char* pContainer2SpecularPngPath = "../../../app/resources/textures/container2_specular.png";
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
  lightingMain.LoadAllTextures(pContainer2PngPath, pContainer2SpecularPngPath);
  lightingMain.SetTexturesToBoxShader();
  lightingMain.ConfigOpenGLUtil();
  lightingMain.CreateVertexArrayObject();
  lightingMain.RenderLoop();
  lightingMain.Terminate();
  return 0;
}

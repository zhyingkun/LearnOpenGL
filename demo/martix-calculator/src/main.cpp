#include <iostream>
using namespace std;
#include <math.h>
#include <iomanip>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

void displayMat4(glm::mat4 trans) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++)
      cout << setw(11) << (float)trans[j][i] << " ";
    cout << endl;
  }
  cout << endl;
}
void displayMat3(glm::mat3 trans) {
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++)
      cout << setw(11) << (float)trans[j][i] << " ";
    cout << endl;
  }
  cout << endl;
}
void displayVec4(glm::vec4 point) {
  for (int i = 0; i < 4; i++)
    cout << setw(11) << point[i] << " ";
  cout << endl << endl;
}
void displayVec3(glm::vec3 vector) {
  for (int i = 0; i < 3; i++)
    cout << setw(11) << vector[i] << " ";
  cout << endl << endl;
}

int main(int argc, char* argv[]) {
  (void)argc;
  (void)argv;
  cout << "Start matrix calculate..." << endl;
  // cout.setf(ios::fixed);
  cout.flags(ios::right);

  // glm::mat4 trans = glm::mat4(1.0f);
  // displayMat4(trans);
  // trans = glm::translate(trans, glm::vec3(0.5f, 0.5f, 0.0f));
  // displayMat4(trans);
  // glm::vec4 point = glm::vec4(1, 1, 0, 1);
  // displayVec4(point);
  // displayVec4(trans * point);

  // float width = 800.0;
  // float height = 800.0;
  // glm::mat4 zhengshetouying = glm::ortho(-0.0414214f, 0.0414214f, -0.0414214f, 0.0414214f, 0.1f, 50.0f);
  // displayMat4(zhengshetouying);
  // glm::vec4 point1 = glm::vec4(0.0414214, 0.0414214, -50, 1);
  // displayVec4(point1);
  // displayVec4(zhengshetouying * point1);
  // point1 = glm::vec4(0.0414214, 0.0414214, -0.1, 1);
  // displayVec4(zhengshetouying * point1);

  // glm::vec4 point2 = glm::vec4(810, 600, -10, 1);
  // // displayVec4(point1);
  // displayVec4(zhengshetouying * point2);

  // glm::mat4 proj = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 50.0f);
  // displayMat4(proj);
  // glm::vec4 point1 = glm::vec4(20.7107, 20.7107, -50, 1);
  // displayVec4(proj * point1);
  // point1 = glm::vec4(0.0414214, 0.0414214, -0.1, 1);
  // displayVec4(proj * point1);

  // glm::vec3 lightColor(1.0f, 1.0f, 1.0f);
  // glm::vec3 toyColor(1.0f, 0.5f, 0.31f);
  // glm::vec3 result = lightColor * toyColor; // = (1.0f, 0.5f, 0.31f);
  // displayVec3(result);

  // glm::mat3 trans = glm::mat3(1.0f);
  // cout << "Identity Martex:" << endl;
  // displayMat3(trans);
  // trans[2][0] = 1;
  // trans[2][1] = 1;
  // trans[2][2] = 1;
  // cout << "Translate Martex:" << endl;
  // displayMat3(trans);

  // glm::vec3 point1 = glm::vec3(0, 0, 1);
  // glm::vec3 point2 = glm::vec3(2, 0, 1);
  // glm::vec3 point3 = glm::vec3(0, 2, 1);
  // glm::vec3 point4 = glm::vec3(2, 2, 1);

  // displayVec3(trans * point1);
  // displayVec3(trans * point2);
  // displayVec3(trans * point3);
  // displayVec3(trans * point4);

  // // Euler Angle
  // float pitch = 30.0f;
  // float yaw = 30.0f;
  // float roll = 0.0f;
  // glm::mat4 transPitch = glm::mat4(1.0f);
  // transPitch = glm::rotate(transPitch, glm::radians(pitch), glm::vec3(1.0, 0, 0));
  // // displayMat4(transPitch);
  // glm::mat4 transYaw = glm::mat4(1.0f);
  // transYaw = glm::rotate(transYaw, glm::radians(yaw), glm::vec3(0, 1.0, 0));
  // // displayMat4(transYaw);
  // glm::mat4 transRoll = glm::mat4(1.0f);
  // transRoll = glm::rotate(transRoll, glm::radians(roll), glm::vec3(0, 0, 1.0));
  // // displayMat4(transRoll);

  // glm::vec4 point = glm::vec4(1.0f);
  // point.x = 1.0f;
  // displayVec4(transRoll * transYaw * transPitch * point);
  // displayVec4(transPitch * transRoll * transYaw * point);
  // displayVec4(transYaw * transPitch * transRoll * point);

  // float Pitch = 0.0f;
  // float Yaw = 0.0f;
  // glm::vec3 Front = glm::vec3(0.0f, 0.0f, -1.0f);
  // glm::vec3 WorldUp = glm::vec3(0.0f, 1.0f, 0.0f);
  // glm::vec3 Up;
  // glm::vec3 front;
  // glm::vec3 Right;
  // front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
  // front.y = sin(glm::radians(Pitch));
  // front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
  // Front = glm::normalize(front);
  // Right = glm::normalize(glm::cross(Front, WorldUp)); // Normalize the vectors, because their length gets closer to 0
  // the more you look up or down which results in slower movement. Up = glm::normalize(glm::cross(Right, Front));

  // glm::vec3 Position = glm::vec3(0.0f, 0.0f, 3.0f);
  // glm::mat4 view = glm::lookAt(Position, Position + Front, Up);
  // displayMat4(view);

  //	glm::vec3 color1 = glm::vec3(0.4, 0.4, 0.4);
  //	glm::vec3 light1 = glm::vec3(0.5, 0.5, 0.5);
  //	glm::vec3 finalColor = light1 * color1;
  //	displayVec3(finalColor);
  //	cout << "dot mul:   " << glm::dot(light1, color1) << endl;
  //	displayVec3(glm::cross(light1, color1));
  return 0;
}

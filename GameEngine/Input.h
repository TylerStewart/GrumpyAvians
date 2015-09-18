#ifndef INPUT_H
#define INPUT_H

#include "AzulCore.h"
#include "GameObject.h"
#include "GameObjectBird.h"
#include "ScreenLine.h"
#include <Windows.h>
#include <stdio.h>
#include <list>
#include <string>
#include <iostream>

void KeyboardTest( GLFWwindow* window, GameObjectBird* pBird );
void MouseTest( GLFWwindow* window, GameObjectBird *obj , ScreenLine *pLine1, ScreenLine *pLine2, std::list<GameObject *>  gameObjectList);

#endif
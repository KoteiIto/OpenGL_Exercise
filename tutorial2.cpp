//
//  tutorial2.cpp
//  sample
//
//  Created by 伊藤皓程 on 2015/07/20.
//  Copyright (c) 2015年 伊藤皓程. All rights reserved.
//

#include <GL/glfw.h>
#include <cstdlib>

#if defined(_MSC_VER)
#pragma comment(lib, "GLFWDLL.lib")
#pragma comment(lib, "opengl32.lib")
#endif

int main(){
    if(!glfwInit()){
        return EXIT_FAILURE;
    }
    
    if(!glfwOpenWindow(640, 800, 0, 0, 0, 0, 0, 0, GLFW_WINDOW)){
        glfwTerminate();
        return EXIT_FAILURE;
    }
    
    glfwSwapInterval(1);
    while(glfwGetWindowParam(GLFW_OPENED)){
        glfwSwapBuffers();
    }
    
    glfwTerminate();
    return EXIT_SUCCESS;
}

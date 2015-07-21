//
//  tutorial5.cpp
//  sample
//
//  Created by 伊藤皓程 on 2015/07/21.
//  Copyright (c) 2015年 伊藤皓程. All rights reserved.
//

#define GLFW_DLL

#include <GL/glfw.h>
#include <cstdlib>

#if defined (_MSC_VER)
#pragma comment(lib, "GLFWDLL.lib")
#pragma comment(lib, "opengl32.lib")
#endif

int main(){
    if(!glfwInit()){
        return EXIT_FAILURE;
    }
    
    if(!glfwOpenWindow(0, 0, 0, 0, 0, 0, 0, 0, GLFW_WINDOW)){
        glfwTerminate();
        return EXIT_FAILURE;
    }
    
    glfwSwapInterval(1);
    while(glfwGetWindowParam(GLFW_OPENED)){
        
        //描画バッファを塗りつぶす色成分を指定する
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        //描画バッファを塗りつぶす
        glClear(GL_COLOR_BUFFER_BIT);
        
        //描画する点の座標を配列で用意する
        //TRIANGLES
        static const GLfloat vtx1[] = {
            -1.0f, 1.0f,
            0.0f, 1.0f,
            -1.0f, 0.0f,
            1.0f, 1.0f,
            0.0f, 0.0f,
            1.0f, 0.0f,
        };
        //STRIP
        static const GLfloat vtx2[] = {
            -1.0f, 1.0f,
            -1.0f, 0.0f,
            0.0f, 1.0f,
            0.0f, 0.0f,
            1.0f, 1.0f,
            1.0f, 0.0f,
        };
        //GLfloat vtx[] = {0.0f, 0.0f};
        //描画に使う頂点配列を指定する
        glVertexPointer(2, GL_FLOAT, 0, vtx2);
        //線の太さを指定する
        glLineWidth(4.0f);
        //点の色を指定する
        glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
        //頂点配列で描画するモードに切り替える
        glEnableClientState(GL_VERTEX_ARRAY);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 6);
        //描画モードを元に戻す
        glDisableClientState(GL_VERTEX_ARRAY);
        
        glfwSwapBuffers();
    }
    
    glfwTerminate();
    return EXIT_SUCCESS;
}
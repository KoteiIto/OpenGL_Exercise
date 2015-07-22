//
//  tutorial13.cpp
//  sample
//
//  Created by 伊藤 皓程 on 2015/07/22.
//  Copyright (c) 2015年 伊藤皓程. All rights reserved.
//

#define GLFW_DLL
#define GLEW_STATIC

#if defined (_MSC_VER)
#include <GL/glew.h>
#endif

#include <GL/glfw.h>

#if defined (__APPLE__)
#include <OpenGL/glext.h>
#endif

#include <cstdlib>
#include <cmath>

#if defined (_MSC_VER)
#pragma comment(lib, "GLFWDLL.lib")
#pragma comment(lib, "opengl32.lib")

#ifdef _DEBUG
#pragma comment(lib, "glew32sd.lib")
#else
#pragma comment(lib, "glew32s.lib")
#endif

#endif

int main(){
    if(!glfwInit()){
        return EXIT_FAILURE;
    }
    
    if(!glfwOpenWindow(640, 480, 0, 0, 0, 0, 0, 0, GLFW_WINDOW)){
        glfwTerminate();
        return EXIT_FAILURE;
    }
    
    glfwSwapInterval(1);
    
    //描写バッファのフレーム識別子を教えてもらう
    GLint current_framebuffer;
    glGetIntegerv(GL_FRAMEBUFFER_BINDING, &current_framebuffer);
    
    //オフスクリーンバッファ用のテクスチャを作成する
    GLuint fbo_texture_id;
    glGenTextures(1, &fbo_texture_id);
    
    //テクスチャ識別子に対して指示を行う
    glBindTexture(GL_TEXTURE_2D, fbo_texture_id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 256, 256, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    //オフスクリーンバッファ用のフレームバッファ識別子を一つ作る
    GLuint framebuffer_id;
    glGenFramebuffers(1, &framebuffer_id);
    
    //フレームバッファ識別子に対して指示を行う
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer_id);
    //フレームバッファに描写された結果はテクスチャとして保存される
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, fbo_texture_id, 0);
    
    float angle = 0.0f;
    
    while(glfwGetWindowParam(GLFW_OPENED)) {
        //フレームバッファ識別子に対して指示を行う
        glBindFramebuffer(GL_FRAMEBUFFER, framebuffer_id);
        glViewport(0, 0, 256, 256);
        
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        angle += 0.02f;
        const float x_ofs = std::sin(angle) * 0.5f;
        
        const GLfloat vtx[] = {
            -0.5f + x_ofs, -0.5f,
             0.5f + x_ofs, -0.5f,
             0.5f + x_ofs,  0.5f,
            -0.5f + x_ofs,  0.5f
        };
        glVertexPointer(2, GL_FLOAT, 0, vtx);
        glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
        
        glEnableClientState(GL_VERTEX_ARRAY);
        glDrawArrays(GL_QUADS, 0, 4);
        glDisableClientState(GL_VERTEX_ARRAY);
        
        //以下の描写命令は、フレームバッファに対して行う
        glBindFramebuffer(GL_FRAMEBUFFER, current_framebuffer);
        glViewport(0, 0, 640, 480);
        
        glClearColor(0.5f, 0.5f, 0.5f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        //画面上にタイルを描画する
        for(int y = 0; y < 3; y++){
            for(int x = 0; x < 3; x++){
                float x_ofs = x * 0.55f - 0.8f;
                float y_ofs = y * 0.55f - 0.8f;
                const GLfloat vtx2[] = {
                    0.0f + x_ofs,  0.0f + y_ofs,
                    0.5f + x_ofs,  0.0f + y_ofs,
                    0.5f + x_ofs,  0.5f + y_ofs,
                    0.0f + x_ofs,  0.5f + y_ofs
                };
                
                glVertexPointer(2, GL_FLOAT, 0, vtx2);
                glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
                
                static const GLfloat texture_uv[] = {
                    0.0f, 0.0f,
                    1.0f, 0.0f,
                    1.0f, 1.0f,
                    0.0f, 1.0f
                };
                glTexCoordPointer(2, GL_FLOAT, 0, texture_uv);
                
                glEnable(GL_TEXTURE_2D);
                //描画にフレームバッファのテクスチャを使う
                glBindTexture(GL_TEXTURE_2D, fbo_texture_id);
                glEnableClientState(GL_VERTEX_ARRAY);
                glEnableClientState(GL_TEXTURE_COORD_ARRAY);
                glDrawArrays(GL_QUADS, 0, 4);
                glDisableClientState(GL_TEXTURE_COORD_ARRAY);
                glDisableClientState(GL_VERTEX_ARRAY);
                glDisable(GL_TEXTURE_2D);
                
            }
        }
        
        glfwSwapBuffers();
        
    }

}
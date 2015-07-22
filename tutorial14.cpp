//
//  tutorial14.cpp
//  sample
//
//  Created by 伊藤 皓程 on 2015/07/22.
//  Copyright (c) 2015年 伊藤皓程. All rights reserved.
//

#define GLFW_DLL
#define GLEW_STATIC

#if defined (_MSC_VER)
#include <GL/g]ew.h>
#endif

#include <GL/glfw.h>
#include <cstdlib>
#include <fstream>
#include <vector>

#if defined (_MSC_VER)
#pragma comment(lib, "GLFWDLL.lib")
#pragma comment(lib, "opengl32.lib")

#ifdef _DEBUG
#pragma comment(lib, "glew32sd.lib")
#else
#pragma comment(lib, "glew32s.lib")
#endif

#endif

//指定テクスチャ識別子へ画像ファイルから読み込んで割り当てる
bool setupTexture(const GLuint id, const char* file, int width, int height){
    //ファイルをバイナリモードで開く
    std::ifstream fstr(file, std::ios::binary);
    if(!fstr) return false;
    
    //ファイルサイズを取得
    const size_t file_size = static_cast<size_t>(fstr.seekg(0, fstr.end).tellg());
    //読み込み位置をファイルの先頭に戻す
    fstr.seekg(0, fstr.beg);
    //動的配列を使ってファイルを読み込む場所を確保する
    std::vector<char> texture_buffer(file_size);
    //確保した場所へファイルを読み込む
    fstr.read(&texture_buffer[0], file_size);
    
    //テクスチャ識別子に対して指示を与える
    glBindTexture(GL_TEXTURE_2D, id);
    
    //1ピクセルに3色と透明度の情報を持つ, ピクセルの画像データをopenglに転送する
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &texture_buffer[0]);
    //画像が拡大された時の振る舞いを指定する
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    
    //テクスチャの丸め込み方法を指定する
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    
    
    return true;
}



int main(){
    if(!glfwInit()){
        return EXIT_FAILURE;
    }
    
    if(!glfwOpenWindow(0, 0, 0, 0, 0, 0, 0, 0, GLFW_WINDOW)){
        return EXIT_FAILURE;
    }
    
    GLuint texture_id;
    glGenTextures(1, &texture_id);
    
    if(!setupTexture(texture_id, "sample.raw", 256,256)){
        glDeleteTextures(1, &texture_id);
        glfwTerminate();
        return EXIT_FAILURE;
    }
    
    //描画用に100頂点を生成する
    GLfloat vtx[100 * 2];
    for(int i = 0; i < 100; ++i){
        vtx[i * 2] = (rand() % 1000) / 500.0f - 1.0f;
        vtx[i * 2 + 1] = (rand() % 1000) / 500.0f - 1.0f;
    }
    glVertexPointer(2, GL_FLOAT, 0, vtx);
    
    while(glfwGetWindowParam(GLFW_OPENED)){
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        glPointSize(32.0f);
        
        glEnable(GL_TEXTURE_2D);
        //ポイントスプライトを有効にする
        glEnable(GL_POINT_SPRITE);
        //ポイントスプライト向けにテクスチャ座標を計算する機能をONにする
        glTexEnvi(GL_POINT_SPRITE, GL_COORD_REPLACE, GL_TRUE);
        
        //ポイントスプライトのどの位置をテクスチャ座標の(0, 0)とするか指定する
        glPointParameteri(GL_POINT_SPRITE_COORD_ORIGIN, GL_UPPER_LEFT);
        
        glEnableClientState(GL_VERTEX_ARRAY);
        glDrawArrays(GL_POINTS, 0, 100);
        glDisableClientState(GL_VERTEX_ARRAY);
        
        glDisable(GL_POINT_SPRITE);
        glDisable(GL_TEXTURE_2D);
        
        glfwSwapBuffers();
    }
    
    glDeleteTextures(1, &texture_id);
    glfwTerminate();
    
    return EXIT_SUCCESS;
}
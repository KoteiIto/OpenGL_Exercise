//
//  tutorial9.cpp
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



//テクスチャ識別子にファイルから読み込んだデータを与える
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
        glfwTerminate();
        return EXIT_FAILURE;
    }
    
    //テクスチャ識別子を作る
    GLuint texture_id;
    glGenTextures(1, &texture_id);
    
    //画像を読み込む
    //失敗したら識別子を削除して終了する
    if(!setupTexture(texture_id, "sample.raw", 256, 256)){
        glDeleteTextures(1, &texture_id);
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
        static const GLfloat vtx[] = {
            -0.5f, -0.5f,
            0.5f, -0.5f,
            0.5f,  0.5f,
            -0.5f,  0.5f
        };
        
        //頂点ごとのUV座標を指定する
        static const GLfloat texture_uv[] = {
            0.0f, 1.0f,
            1.0f, 1.0f,
            1.0f, 0.0f,
            0.0f, 0.0f
        };
        
        static const GLfloat texture_uv1[] = {
            -2.5f, 0.0f,
             2.5f, 0.0f,
             2.5f, 5.0f,
            -2.5f, 5.0f
        };
        
        //描画に使う頂点配列を指定する
        glVertexPointer(2, GL_FLOAT, 0, vtx);
        glTexCoordPointer(2, GL_FLOAT, 0, texture_uv1);
        
        
        glEnable(GL_TEXTURE_2D);
        
        //頂点配列で描画するモードに切り替える
        glEnableClientState(GL_VERTEX_ARRAY);
        
        //描写時にテクスチャ座標配列も使うと指示する
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        
        glDrawArrays(GL_QUADS, 0, 4);
        
        //描画モードを元に戻す
        glDisableClientState(GL_VERTEX_ARRAY);
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);
        glDisable(GL_TEXTURE_2D);
        
        
        glfwSwapBuffers();
    }
    
    //テクスチャ識別子を削除する
    glDeleteTextures(1, &texture_id);
    
    glfwTerminate();
    return EXIT_SUCCESS;
}

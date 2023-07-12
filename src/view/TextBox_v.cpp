#include "../common/config.h"
#include "../util/Utility.h"
#include  <GLFW/glfw3.h>
#include "Text.h"

void TextBox::Render()
{
    if(bckgrnd)
    {
        // glClearColor(bckgrnd_color.x, bckgrnd_color.y, bckgrnd_color.z, 1.0f);
        // glClear(GL_COLOR_BUFFER_BIT);
    }
    else
    {
        bckgrnd_texture = ResourceManager::GetTexture(texture_text);
        Utility::GetRenderer()->DrawSprite(bckgrnd_texture, glm::vec2(x, y), glm::vec2(width, height), 0.0f, glm::vec3(0.0f, 0.0f, 0.0f));
    }
    text_character::generate_text(text, glm::vec2(x, y), glm::vec2(width, height), 1, 0.0f, glm::vec3(0.0f, 0.0f, 0.0f), false);
}

void TextBox::setText(std::string new_text)
{
    text = new_text;
}

void TextBox::DrawRect(float x, float y, float width, float height, float r, float g, float b)
{
    // 设置顶点和颜色数据
    float vertices[] = {
        x,         y,          r, g, b,  // 左下角
        x + width, y,          r, g, b,  // 右下角
        x + width, y + height, r, g, b,  // 右上角
        x,         y + height, r, g, b   // 左上角
    };
    
    // 创建顶点缓冲对象(VBO)和顶点数组对象(VAO)
    GLuint VBO, VAO;
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);
    
    // 绑定VAO和VBO，并设置顶点和颜色数据
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    // 设置顶点属性指针
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);
    
    // 绘制矩形
    glBindVertexArray(VAO);
    glDrawArrays(GL_QUADS, 0, 4);
    glBindVertexArray(0);
    
    // 删除VAO和VBO
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}
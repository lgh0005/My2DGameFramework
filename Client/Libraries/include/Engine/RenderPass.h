#pragma once

class Shader;
class IRenderable;

class RenderPass
{
public:
    void Draw(const GLuint vao, const GLuint indexCount)
    {
        _shader->Bind();
        _shader->ApplyUniforms();
        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
        _shader->Unbind();
    }

public:
    void SetShader(const shared_ptr<Shader>& shader) { _shader = shader; }

private:
    shared_ptr<Shader> _shader;
    vector<IRenderable> _renderables;
};


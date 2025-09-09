#include "pch.h"
#include "Flipbook.h"
#include "Shader.h"

Flipbook::Flipbook(const string& name, const string& filePath, FlipbookInfo& info)
    : Super(name, filePath), 
    _flipbookInfo(info), 
    _currentFrame(info.startFrame),
    _elapsedTime(0.0f)
{
}

void Flipbook::Awake()
{
    Super::Awake();
    GetFrameVertices();
    SetFrame(_currentFrame);
}

void Flipbook::Render(shared_ptr<Shader> shader, glm::mat4 model, shared_ptr<Camera> camera)
{
    Super::Render(shader, model, camera);
}

void Flipbook::Update()
{
    if (!_flipbookInfo.isPlaying) return;

    _elapsedTime += TIME.deltaTime;
    float frameTime = 1.0f / _flipbookInfo.fps;

    if (_elapsedTime >= frameTime)
    {
        _elapsedTime = 0.0f;
        _currentFrame++;

        if (_currentFrame > _flipbookInfo.endFrame)
        {
            if (_flipbookInfo.isLoop)
                _currentFrame = _flipbookInfo.startFrame;
            else
            {
                _currentFrame = _flipbookInfo.endFrame;
                _flipbookInfo.isPlaying = false;
            }
        }

        SetFrame(_currentFrame);
    }
}

void Flipbook::SetFrame(uint32 frame)
{
    _currentFrame = frame;

    uint32 col = frame;
    uint32 row = _flipbookInfo.animationRow;

    float uSize = 1.0f / _flipbookInfo.cols;
    float vSize = 1.0f / _flipbookInfo.rows;

    float u0 = col * uSize, v0 = row * vSize;
    float u1 = u0 + uSize, v1 = v0 + vSize;

    // _vertices�� ITexture���� pos+uv�� �̹� ���ǵ�
    // pos�� �״�� �ΰ� uv�� ������Ʈ
    _vertices[3] = u0; _vertices[4] = v1; // �»��
    _vertices[8] = u0; _vertices[9] = v0; // ���ϴ�
    _vertices[13] = u1; _vertices[14] = v1; // ����
    _vertices[18] = u1; _vertices[19] = v0; // ���ϴ�

    // VBO�� �ݿ�
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(_vertices), _vertices.data());
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Flipbook::Play() { _flipbookInfo.isPlaying = true; }
void Flipbook::Stop() { _flipbookInfo.isPlaying = false; }

void Flipbook::GetFrameVertices()
{
    // pos ��ǥ�� ������ ũ��� ����
    float frameW = static_cast<float>(_width) / _flipbookInfo.cols;
    float frameH = static_cast<float>(_height) / _flipbookInfo.rows;

    float halfW = frameW / 2.0f;
    float halfH = frameH / 2.0f;

    _vertices =
    {
        -halfW, -halfH, 0.0f,   0.0f, 1.0f, // ���ϴ�
        -halfW,  halfH, 0.0f,   0.0f, 0.0f, // �»��
         halfW, -halfH, 0.0f,   1.0f, 1.0f, // ���ϴ�
         halfW,  halfH, 0.0f,   1.0f, 0.0f  // ����
    };

    // pos + uv ��ü�� VBO�� �ݿ�
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(_vertices), _vertices.data());
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

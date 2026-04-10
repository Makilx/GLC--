#include <GLEngine/Engine.hpp>
#include <iostream>
using namespace GLEngine;

class NewApp : public GLEngine::App {
    public:
    NewApp() {
        appName = "Hello App";
    }

    void OnStart() override {
        Renderer::SetBackground(.5, .5, .5, 0);

        m = new Mesh();
        s = new Shaders();
        c = new Camera();

        Vertex v[] = {
            { 0.0f, 0.5f, 0.0f,      -1.0f,-1.0f},
            {-0.5f, 0.5f, 0.0f,      -1.0f,-1.0f},
            {-0.5f, 0.5f, 0.0f,      -1.0f,-1.0f}
        };

        unsigned int i[] = {
            0, 1, 2
        };

        m->SetVertices(v, sizeof(v));
        m->SetIndices(i, sizeof(i));

        s->AttachShaderFromFile(GL_VERTEX_SHADER, "../resources/.vert");
        s->AttachShaderFromFile(GL_FRAGMENT_SHADER, "../resources/.frag");

        c->position.z = 3;
    }

    void OnUpdate(double deltaTime) override {
        s->Use();
        c->Use(*s);
        m->Draw(*s);
    }

    void OnEnd() override {

    }

    private:
    Shaders *s;
    Mesh *m;
    Camera *c;
};

int main() {
    NewApp NEWA;
    NEWA.Run();
}

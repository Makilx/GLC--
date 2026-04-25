#include <GLEngine/engine.hpp>

class LLL : public gle::App {
  public:
    void OnStart() override {
        gle::Renderer::SetBackgroundColor(.1, .05, .07, 1);
        gle::Renderer::SetFPSLimit(144);
        gle::Renderer::SetVSYNC(false);

        shaders.AttachShader(gle::ShaderType::VertexShader,
                             R"(
            #version 330 core

            layout(location = 0) in vec2 aPos;

            uniform mat4 MeshPosition;
            uniform mat4 CameraProjection;

            void main() {
                gl_Position = CameraProjection * MeshPosition * vec4(aPos, 0, 1);
            }

            )");

        shaders.AttachShader(gle::ShaderType::FragmentShader,
                             R"(
            #version 330 core

            out vec4 FragColor;

            uniform vec4 MeshColor;

            void main() {
                FragColor = MeshColor;
            }
            )");

        mesh.SetVertices(std::vector<float>(
            {-0.5f, 0.5f, -0.5f, -0.5f, 0.5f, -0.5f, 0.5f, 0.5f}));
        mesh.SetIndices(std::vector<unsigned int>({0, 1, 2, 0, 2, 3}));
        mesh.layout.Push<float>(2);
        mesh.color = gle::Color::Red();
        camera.position.position.z -= 3;
    }

    void OnUpdate(double deltaTime) override {
        static double timer = 0.0;
        static int frames = 0;

        timer += deltaTime;
        frames++;

        if (timer >= 1.0) {
            int fps = frames; // frames counted in 1 second

            gle::Logger::Log(std::to_string(fps) + " FPS");

            frames = 0;
            timer = 0.0;
        }

        shaders.Use();
        camera.Use(shaders);
        mesh.Draw(shaders);
    }

    gle::Shaders shaders;
    gle::Mesh mesh;
    gle::Camera camera;
};
int main() {
    LLL a;
    a.Run();
    return 1;
}

#include <GLEngine/engine.hpp>
using namespace gle;

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
        camera.position.position.z += 3;
        camera.orthographic = false;

        Input::OnKeyStateChanged.Subscribe(this, &LLL::KeyUpd);
        Input::OnMouseMove.Subscribe(this, &LLL::Move);
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

    void Move(MouseMoveEvent &event) {
        (void)event;
        if (!mouseToggle)
            return;

        Vec2 delta = Input::GetMouseDelta();

        yaw += static_cast<float>(toRadians(delta.x * mouseSensitivity));
        pitch -= static_cast<float>(toRadians(delta.y * mouseSensitivity));

        const float maxPitch = static_cast<float>(toRadians(89.0f));
        if (pitch > maxPitch)
            pitch = maxPitch;
        if (pitch < -maxPitch)
            pitch = -maxPitch;

        camera.position.rotation = Quat::FromYawPitch(yaw, pitch);
    }

    void KeyUpd(KeyStateEvent &event) {
        if (event.state != InputState::Down)
            return;

        if (event.key == Key::Escape)
            exit(-1);

        if (event.key == Key::Q) {
            mouseToggle = !mouseToggle;
            Input::SetMouseBehavior(mouseToggle ? MouseBehavior::LockedCenter
                                                : MouseBehavior::Default);
        }
    }

    gle::Shaders shaders;
    gle::Mesh mesh;
    gle::Camera camera;
    float yaw = 0.0f;
    float pitch = 0.0f;
    float mouseSensitivity = 0.15f;
    bool mouseToggle = false;
};
int main() {
    LLL a;
    a.Run();
    return 1;
}

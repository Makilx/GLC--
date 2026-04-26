#pragma once

#include <GLEngine/pch.hpp>
#include <GLEngine/rendering/opengl/buffer.hpp>

namespace gle {
    class Mesh;
    namespace opengl {
        struct DataLayoutElement {
            unsigned int count;
            unsigned int typeSize;
            unsigned int type;
            bool normalized;
        };

        class DataLayout {
          public:
            template <typename T>
            void Push(unsigned int count, bool normalized = false);

            void Clear() {
                elements.clear();
                updateLayout = true;
            }

            void Set(size_t index, DataLayoutElement element) {
                if (index >= elements.size())
                    return;
                elements[index] = element;
                updateLayout = true;
            }

            void Set(std::vector<DataLayoutElement> elements) {
                this->elements = elements;
                updateLayout = true;
            }

          private:
            std::vector<DataLayoutElement> elements;
            size_t stride = 0;
            bool updateLayout = false;

            void Consume();

            friend class gle::Mesh;
        };

        class VertexArray {
          public:
            ~VertexArray();

            void Create();
            bool IsCreated() {
                return id != 0;
            }

            void Bind();
            void Unbind();

          private:
            unsigned int id = 0;
        };
    } // namespace opengl
} // namespace gle

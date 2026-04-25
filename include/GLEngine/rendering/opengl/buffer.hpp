#pragma once

#include <GLEngine/pch.hpp>

namespace gle::opengl {
    enum class BufferType {
        Array = 0x8892,             // GL_ARRAY_BUFFER
        ElementArray = 0x8893,      // GL_ELEMENT_ARRAY_BUFFER
        PixelPack = 0x88EB,         // GL_PIXEL_PACK_BUFFER
        PixelUnpack = 0x88EC,       // GL_PIXEL_UNPACK_BUFFER
        Uniform = 0x8A11,           // GL_UNIFORM_BUFFER
        Texture = 0x8C2A,           // GL_TEXTURE_BUFFER
        TransformFeedback = 0x8C8E, // GL_TRANSFORM_FEEDBACK_BUFFER
        CopyRead = 0x8F36,          // GL_COPY_READ_BUFFER
        CopyWrite = 0x8F37,         // GL_COPY_WRITE_BUFFER
        DrawIndirect = 0x8F3F,      // GL_DRAW_INDIRECT_BUFFER
        AtomicCounter = 0x92C0,     // GL_ATOMIC_COUNTER_BUFFER
        DispatchIndirect = 0x90EE,  // GL_DISPATCH_INDIRECT_BUFFER
        ShaderStorage = 0x90D2,     // GL_SHADER_STORAGE_BUFFER
        Query = 0x9192,             // GL_QUERY_BUFFER
        Parameter = 0x80EE          // GL_PARAMETER_BUFFER (rare but core)
    };

    enum class BufferUsage {
        StreamDraw = 0x88E0, // GL_STREAM_DRAW
        StreamRead = 0x88E1, // GL_STREAM_READ
        StreamCopy = 0x88E2, // GL_STREAM_COPY

        StaticDraw = 0x88E4, // GL_STATIC_DRAW
        StaticRead = 0x88E5, // GL_STATIC_READ
        StaticCopy = 0x88E6, // GL_STATIC_COPY

        DynamicDraw = 0x88E8, // GL_DYNAMIC_DRAW
        DynamicRead = 0x88E9, // GL_DYNAMIC_READ
        DynamicCopy = 0x88EA  // GL_DYNAMIC_COPY
    };

    class Buffer {
      public:
        Buffer(BufferType type, BufferUsage usage = BufferUsage::StaticDraw)
            : type(type), usage(usage) {
        }
        ~Buffer();

        void Create();
        bool IsCreated() {
            return id != 0;
        }

        void Bind();
        void Unbind();
        void Data(void *data, size_t size);
        void SubData(size_t offset, void *data, size_t size);

        void SetType(BufferType type);
        void SetUsage(BufferUsage usage);

      private:
        unsigned int id = 0;
        BufferType type;
        BufferUsage usage;
    };
} // namespace gle::opengl

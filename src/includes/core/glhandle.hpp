#ifndef GLHANDLE_H
#define GLHANDLE_H

#include <cstdint>
#include <glad/glad.h>

#include "utility/disposable.hpp"

namespace graphite
{
    // TODO: reminder to add more types as needed
    // TODO: maybe move this into a separate file
    enum class GLHandleType
    {
        None,
        VertexArray,
        Buffer,
        Shader,
        Texture,
        Framebuffer,
    };

    struct GLHandle : Disposable
    {
        // When something needs a GLHandle, it is responsible for creating the initial handle
        // This class then takes it from there. That is why there is no automatic handle creation
        GLHandle(uint32_t handle, GLHandleType type) : mHandle(handle), mHandleType(type)
        {
        }

        ~GLHandle()
        {
            dispose();
        }

        GLHandle(const GLHandle&) = delete;
        GLHandle& operator=(const GLHandle&) = delete;

        GLHandle(GLHandle&& other) noexcept
            : mHandle(other.mHandle), mHandleType(other.mHandleType)
        {
            other.mHandle = 0; // Mark as null to prevent double deletion
            other.mHandleType = GLHandleType::None;
        }

        GLHandle& operator=(GLHandle&& other) noexcept
        {
            if (this != &other)
            {
                // Free existing resource
                if (mHandle)
                {
                    dispose();
                }

                // Transfer ownership
                mHandle = other.mHandle;
                mHandleType = other.mHandleType;

                other.mHandle = 0;
                other.mHandleType = GLHandleType::None;
            }
            return *this;
        }

        // Explicit disposal of resources
        // Avoid using this, as it could cause OpenGL issues if not called correctly
        void dispose() override
        {
            if (mHandle == 0) return;
            
            // TODO: more verbose errors? currently if there is no opengl context, this just segfaults

            switch (mHandleType)
            {
            case GLHandleType::VertexArray: glDeleteVertexArrays(1, &mHandle);
                break;
            case GLHandleType::Buffer: glDeleteBuffers(1, &mHandle);
                break;
            case GLHandleType::Shader: glDeleteShader(mHandle);
                break;
            case GLHandleType::Texture: glDeleteTextures(1, &mHandle);
                break;
            case GLHandleType::Framebuffer: glDeleteFramebuffers(1, &mHandle);
                break;
            default: break;
            }
        }

        [[nodiscard]] uint32_t getHandle() const { return mHandle; }

    private:
        uint32_t mHandle;
        GLHandleType mHandleType;
    };
}

#endif //GLHANDLE_H

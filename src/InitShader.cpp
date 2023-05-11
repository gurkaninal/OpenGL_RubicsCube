#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include "Angel.h"

namespace Angel {

    static std::string ParseShader(const char* filepath) {
        std::ifstream stream(filepath);
        std::string line;
        std::stringstream ss;

        while (getline(stream, line)) {
            ss << line << "\n";
        }

        return ss.str();
    }

    static unsigned int CompileShader(unsigned int type, const std::string& source) {
        unsigned int id = glCreateShader(type);
        const char* src = source.c_str();
        glShaderSource(id, 1, &src, nullptr);
        glCompileShader(id);

        int result;
        glGetShaderiv(id, GL_COMPILE_STATUS, &result);
        if (result == GL_FALSE) {
            int length;
            glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
            char* message = (char*)_malloca(length * sizeof(char));
            glGetShaderInfoLog(id, length, &length, message);

            std::cout << "Failed to compile "
                << (type == GL_VERTEX_SHADER ? "vertex" : "fragment")
                << " shader!" << std::endl;
            std::cout << message << std::endl;

            glDeleteShader(id);
            return 0;
        }

        return id;
    }

    GLuint InitShader(const char* vertexShaderFile, const char* fragmentShaderFile) {
        std::string vertexShader = ParseShader(vertexShaderFile);
        std::string fragmentShader = ParseShader(fragmentShaderFile);

        unsigned int program = glCreateProgram();
        unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
        unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

        glAttachShader(program, vs);
        glAttachShader(program, fs);
        glLinkProgram(program);
        glValidateProgram(program);

        glDeleteShader(vs);
        glDeleteShader(fs);

        return program;
    }
}
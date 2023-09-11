
#pragma once 

#include <vmath.h>
#include "OBJ_Loader.h"

class Model
{
public:
    vmath::vec3 diffuse;
    vmath::vec3 ambient;
    vmath::vec3 specular;
    float specular_exponent;
    
    Model(const char* path)
    {
        objl::Loader loader;
        if(!loader.LoadFile(path))
        {
            fprintf(stderr, "Error loading a mesh!\n");
        }

        for(const auto &mesh : loader.LoadedMeshes)
        {
            for(const auto& vertex : mesh.Vertices)
            {
                vertices.push_back(vertex.Position.X);
                vertices.push_back(vertex.Position.Y);
                vertices.push_back(vertex.Position.Z);

                textCoords.push_back(vertex.TextureCoordinate.X);
                textCoords.push_back(vertex.TextureCoordinate.Y);

                normals.push_back(vertex.Normal.X);
                normals.push_back(vertex.Normal.Y);
                normals.push_back(vertex.Normal.Z);
            }

            for(const auto& index : mesh.Indices)
            {
                indices.push_back(index);
            }   

            diffuse = vmath::vec3(mesh.MeshMaterial.Kd.X, 
                                  mesh.MeshMaterial.Kd.Y,
                                  mesh.MeshMaterial.Kd.Z); 
            ambient = vmath::vec3(mesh.MeshMaterial.Ka.X, 
                                  mesh.MeshMaterial.Ka.Y,
                                  mesh.MeshMaterial.Ka.Z);
            specular = vmath::vec3(mesh.MeshMaterial.Ks.X, 
                                  mesh.MeshMaterial.Ks.Y,
                                  mesh.MeshMaterial.Ks.Z);
            specular_exponent = mesh.MeshMaterial.Ns;
        }

        glGenBuffers(1, &array_buffer);
        glBindBuffer(GL_ARRAY_BUFFER, array_buffer);
        glBufferData(GL_ARRAY_BUFFER, 
                     (vertices.size() + textCoords.size() + normals.size()) * sizeof(GLfloat), 
                     NULL, GL_STATIC_DRAW);
        glBufferSubData(GL_ARRAY_BUFFER, 
                     0,
                     vertices.size() * sizeof(float),
                     vertices.data());
        glBufferSubData(GL_ARRAY_BUFFER, 
                     vertices.size() * sizeof(GLfloat),
                     textCoords.size() * sizeof(GLfloat),
                     textCoords.data());
        glBufferSubData(GL_ARRAY_BUFFER, 
                     (vertices.size() + textCoords.size()) * sizeof(GLfloat),
                     normals.size() * sizeof(GLfloat),
                     normals.data());
        glGenBuffers(1, &element_buffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), 
                      indices.data(), GL_STATIC_DRAW);

        if(glGetError() != 0) 
        {
            fprintf(stderr, "Error setting up mesh data\n");
        }

        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
        glBindBuffer(GL_ARRAY_BUFFER, array_buffer);

        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 
            reinterpret_cast<void*>(vertices.size() * sizeof(GLfloat)));
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 
            reinterpret_cast<void*>((vertices.size() + textCoords.size()) * sizeof(GLfloat)));

        if(glGetError() != 0) 
        {
            fprintf(stderr, "Error setting vao!\n");
        }
    }

    void drawModel()
    {
        glBindVertexArray(vao);
        glBindBuffer(GL_ARRAY_BUFFER, array_buffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer);
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    }

    ~Model()
    {
        glDeleteBuffers(1, &array_buffer);
        glDeleteBuffers(1, &element_buffer);
        glDeleteVertexArrays(1, &vao);
    }

private:
    std::vector<GLfloat> vertices;
    std::vector<GLuint> indices;
    std::vector<GLfloat> textCoords;
    std::vector<GLfloat> normals;
    GLuint array_buffer = 0;
    GLuint element_buffer = 0;
    GLuint vao;
};
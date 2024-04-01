#include "Object.h"

void Object::init_buffer_objects()
{

    // TODO
    glGenBuffers(1, &position_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, position_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(aiVector3D) * pmesh_->mNumVertices, pmesh_->mVertices, GL_STATIC_DRAW);

    is_color = true;
    glGenBuffers(1, &color_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, color_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(aiColor4D) * pmesh_->mNumVertices, pmesh_->mColors[0], GL_STATIC_DRAW);

    for (unsigned int i = 0; i < pmesh_->mNumFaces; ++i)
    {
        aiFace face = pmesh_->mFaces[i];
        Face mesh_face;
        mesh_face.num_indices = face.mNumIndices;

        glGenBuffers(1, &mesh_face.index_buffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh_face.index_buffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * face.mNumIndices, face.mIndices, GL_STATIC_DRAW);

        faces.push_back(mesh_face);
    }
}

glm::mat4 Object::get_model_matrix() const
{
    glm::mat4 mat_model = glm::mat4(1.0f);

    // TODO
    mat_model = glm::translate(glm::mat4(1.0f), vec_translate_) *
                               glm::mat4(quat_rotate_) *
                               glm::scale(glm::mat4(1.0f), vec_scale_);

    return mat_model;
}

void Object::draw(int loc_a_position, int loc_a_color)
{
    // TODO
    glBindBuffer(GL_ARRAY_BUFFER, position_buffer);
    glVertexAttribPointer(loc_a_position, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(loc_a_position);

    glBindBuffer(GL_ARRAY_BUFFER, color_buffer);
    glVertexAttribPointer(loc_a_color, 4, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(loc_a_color);


    for (const auto& face : faces)
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, face.index_buffer);
        glDrawElements(GL_TRIANGLES, face.num_indices, GL_UNSIGNED_INT, 0);
    }

    glDisableVertexAttribArray(loc_a_position);

    glDisableVertexAttribArray(loc_a_color);

}

void Object::print_info()
{
    std::cout << "print mesh info" << std::endl;

    std::cout << "num vertices " << pmesh_->mNumVertices << std::endl;
    for (unsigned int i = 0; i < pmesh_->mNumVertices; ++i)
    {
        aiVector3D vertex = pmesh_->mVertices[i];
        std::cout << "  vertex  (" << vertex.x << ", " << vertex.y << ", " << vertex.z << ")" << std::endl;

        if (pmesh_->mColors[0] != NULL)
        {
            aiColor4D color = pmesh_->mColors[0][i];
            std::cout << "  color  (" << color.r << ", " << color.g << ", " << color.b << ", " << color.a << ")" << std::endl;
        }
    }
}

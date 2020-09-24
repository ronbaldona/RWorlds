#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices,
    std::vector<Texture> textures) {
    this->vertices = vertices;
    this->indices = indices;
    this->textures = textures;

    init();
}

void Mesh::init() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    // Bind the vertex buffer for reading
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex),
                 vertices.data(), GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int),
                 indices.data(), GL_STATIC_DRAW);

    // Tell OpenGL how to read the data
    // Vertex positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    // Vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (void*)offsetof(Vertex, normal));
    // Texture coordinates
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (void*)offsetof(Vertex, texCoords));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    
    std::cout << "Vertices: " << vertices.size() << std::endl;
    std::cout << "Indices: " << indices.size() << std::endl;

}

void Mesh::getCornerVecs(glm::vec3& minCorner, glm::vec3& maxCorner) const {
    glm::vec3 min(std::numeric_limits<float>::max());
    glm::vec3 max(std::numeric_limits<float>::lowest());
    for (const auto& vertex : vertices) {
        glm::vec3 pos(vertex.position);
        for (int i = 0; i < 3; ++i) {
            min[i] = (min[i] > pos[i]) ? pos[i] : min[i];
            max[i] = (max[i] < pos[i]) ? pos[i] : max[i];
        }
    }

    minCorner = min;
    maxCorner = max;
}

void Mesh::updateBuffers() const {
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferSubData(
        GL_ARRAY_BUFFER, // Target
        0, // Offset
        vertices.size() * sizeof(Vertex), // Size in bytes of data
        vertices.data() // Actual data
    );
}

void Mesh::draw(Shader shaderProg, glm::mat4 view, glm::mat4 projection) {
    // TODO: DEAL WITH TEXTURES LATER
    /*
    */
    // TODO Change this later
    shaderProg.use();
    shaderProg.setMat4("model", glm::mat4(1.0f));
    shaderProg.setMat4("view", view);
    shaderProg.setMat4("projection", projection);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, (int)indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}


void Mesh::draw(Shader shaderProg, glm::mat4& model, glm::mat4& view, 
    glm::mat4& projection) {

    // TODO Change this later
    shaderProg.setMat4("model", model);
    shaderProg.setMat4("view", view);
    shaderProg.setMat4("projection", projection);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, (int)indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

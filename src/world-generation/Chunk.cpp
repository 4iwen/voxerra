#include "Chunk.h"

void Chunk::GenerateChunk(FastNoiseLite iNoise, int posX,int posY,  int length, int width,int height)
{
    this->posX = posX;
    this->posY = posY;

    this->width = width;
    this->length = length;
    this->height = height;

    FillEmpty();

    GenerateNoise(iNoise);

    //Cunk size is 4x4x16 and the y is set to 4 rn so it should draw a 4x4x4 cube
    GenerateVertices(); //VERTS ALWAYS FIRST

    GenerateGLData();
}

void Chunk::FillEmpty()
{
    for (int x = 0; x < width; x++) // X coordinates
    {
        for (int y = 0; y < height; y++) // Y coordinates
        {
            for (int z = 0; z < length; z++) // Y coordinates
            {
                blockData[x][y][z].type = air;
            }
        }
    }
}

void Chunk::GenerateNoise(FastNoiseLite noise)
{
    for (int x = 0; x < width; x++) // X coordinates
    {
        for (int z = 0; z < length; z++) // Y coordinates
        {
            float y = abs(noise.GetNoise((float)x, (float)z) * 50);

            blockData[x][(int)y][z].type = grass;
            for (int j = (int)y; j >= 0; --j)
            {
                blockData[x][j][z].type = dirt;
            }
        }
    }
    //FOR WRITING OUT IN THE CONSOLE
    for (int x = 0; x < width; x++) // X coordinates
    {
        for (int z = 0; z < length; z++) // Y coordinates
        {
            int y = (int)abs(noise.GetNoise((float)x, (float)z) * 50);
            if(y > 9)
            {
                cout << y;
            }
            else
            {
                cout << y << " ";
            }
        }
        cout << endl;
    }
}

void Chunk::GenerateVertices() {
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            for (int z = 0; z < length; z++) {
                if (blockData[x][y][z].type != air) // If block is occupied we check around.
                {
                    if (CheckAround(glm::vec3(x, y, z) + vert::LEFT) || x - 1 < 0) // Checks Left
                    {
                        switch (blockData[x][y][z].type) {
                            case dirt:
                                AddLeft(x, y, z, blockData[x][y][z].r, blockData[x][y][z].g, blockData[x][y][z].b);
                                break;
                            case grass:
                                AddLeft(x, y, z, blockData[x][y][z].r, blockData[x][y][z].g, blockData[x][y][z].b);
                                break;
                            case stone:
                                AddLeft(x, y, z, blockData[x][y][z].r, blockData[x][y][z].g, blockData[x][y][z].b);
                                break;
                            case bedrock:
                                AddLeft(x, y, z, blockData[x][y][z].r, blockData[x][y][z].g, blockData[x][y][z].b);
                                break;
                        }
                    }
                    if (CheckAround(glm::vec3(x, y, z) + vert::RIGHT) || x + 1 > width)// Checks Right
                    {
                        switch (blockData[x][y][z].type) {
                            case dirt:
                                AddRight(x, y, z, blockData[x][y][z].r, blockData[x][y][z].g, blockData[x][y][z].b);
                                break;
                            case grass:
                                AddRight(x, y, z, blockData[x][y][z].r, blockData[x][y][z].g, blockData[x][y][z].b);
                                break;
                            case stone:
                                AddRight(x, y, z, blockData[x][y][z].r, blockData[x][y][z].g, blockData[x][y][z].b);
                                break;
                            case bedrock:
                                AddRight(x, y, z, blockData[x][y][z].r, blockData[x][y][z].g, blockData[x][y][z].b);
                                break;
                        }
                    }

                    if (CheckAround(glm::vec3(x, y, z) + vert::DOWN) || y - 1 < 0)// Checks Down
                    {
                        switch (blockData[x][y][z].type) {
                            case dirt:
                                AddBottom(x, y, z, blockData[x][y][z].r, blockData[x][y][z].g, blockData[x][y][z].b);
                                break;
                            case grass:
                                AddBottom(x, y, z, blockData[x][y][z].r, blockData[x][y][z].g, blockData[x][y][z].b);
                                break;
                            case stone:
                                AddBottom(x, y, z, blockData[x][y][z].r, blockData[x][y][z].g, blockData[x][y][z].b);
                                break;
                            case bedrock:
                                AddBottom(x, y, z, blockData[x][y][z].r, blockData[x][y][z].g, blockData[x][y][z].b);
                                break;
                        }
                    }
                    if (CheckAround(glm::vec3(x, y, z) + vert::UP))// Checks Top
                    {
                        switch (blockData[x][y][z].type) {
                            case dirt:
                                AddTop(x, y, z, blockData[x][y][z].r, blockData[x][y][z].g, blockData[x][y][z].b);
                                break;
                            case grass:
                                AddTop(x, y, z, blockData[x][y][z].r, blockData[x][y][z].g, blockData[x][y][z].b);
                                break;
                            case stone:
                                AddTop(x, y, z, blockData[x][y][z].r, blockData[x][y][z].g, blockData[x][y][z].b);
                                break;
                            case bedrock:
                                AddTop(x, y, z, blockData[x][y][z].r, blockData[x][y][z].g, blockData[x][y][z].b);
                                break;
                        }
                    }

                    if (CheckAround(glm::vec3(x, y, z) + vert::BACK) || z - 1 < 0)// Checks Back
                    {
                        switch (blockData[x][y][z].type) {
                            case dirt:
                                AddBack(x, y, z, blockData[x][y][z].r, blockData[x][y][z].g, blockData[x][y][z].b);
                                break;
                            case grass:
                                AddBack(x, y, z, blockData[x][y][z].r, blockData[x][y][z].g, blockData[x][y][z].b);
                                break;
                            case stone:
                                AddBack(x, y, z, blockData[x][y][z].r, blockData[x][y][z].g, blockData[x][y][z].b);
                                break;
                            case bedrock:
                                AddBack(x, y, z, blockData[x][y][z].r, blockData[x][y][z].g, blockData[x][y][z].b);
                                break;
                        }
                    }
                    if (CheckAround(glm::vec3(x, y, z) + vert::FRONT) || z + 1 > length)// Checks Forth
                    {
                        switch (blockData[x][y][z].type) {
                            case dirt:
                                AddForth(x, y, z, blockData[x][y][z].r, blockData[x][y][z].g, blockData[x][y][z].b);
                                break;
                            case grass:
                                AddForth(x, y, z, blockData[x][y][z].r, blockData[x][y][z].g, blockData[x][y][z].b);
                                break;
                            case stone:
                                AddForth(x, y, z, blockData[x][y][z].r, blockData[x][y][z].g, blockData[x][y][z].b);
                                break;
                            case bedrock:
                                AddForth(x, y, z, blockData[x][y][z].r, blockData[x][y][z].g, blockData[x][y][z].b);
                        }
                    }
                }
            }
        }
    }
}

bool Chunk::CheckAround(glm::vec3 input)
{
    return(blockData[(int)input.x][(int)input.y][(int)input.z].type == air);
}

void Chunk::AddVert(vert v)
{
    verts.push_back(v);
}

void Chunk::PushBackIndicies()
{
    GLindices.push_back(verts.size()-4);
    GLindices.push_back(verts.size()-3);
    GLindices.push_back(verts.size()-2);
    // TRAINGLE ONE

    GLindices.push_back(verts.size()-3);
    GLindices.push_back(verts.size()-2);
    GLindices.push_back(verts.size()-1);
    //TRIANGLE TWO
}

void Chunk::AddTop(int blockX,int blockY,int blockZ,int r ,int g ,int b)
{
    vert cornerOne(glm::vec3(blockX,blockY,blockZ) + vert::LEFT_TOP_BACK_CORNER,r / 255,g / 255,b / 255);
    AddVert(cornerOne);
    vert cornerTwo(glm::vec3(blockX,blockY,blockZ) + vert::RIGHT_TOP_BACK_CORNER,r / 255,g / 255,b / 255);
    AddVert(cornerTwo);
    vert cornerThree(glm::vec3(blockX,blockY,blockZ) + vert::LEFT_TOP_FRONT_CORNER,r / 255,g / 255,b / 255);
    AddVert(cornerThree);
    vert cornerFour(glm::vec3(blockX,blockY,blockZ) + vert::RIGHT_TOP_FRONT_CORNER,r / 255,g / 255,b / 255);
    AddVert(cornerFour);
    PushBackIndicies();
}
void Chunk::AddBottom(int blockX,int blockY,int blockZ,int r ,int g ,int b)
{
    vert cornerOne(glm::vec3(blockX,blockY,blockZ) + vert::LEFT_BOTTOM_BACK_CORNER ,r / 255,g / 255,b / 255);
    AddVert(cornerOne);
    vert cornerTwo(glm::vec3(blockX,blockY,blockZ) + vert::RIGHT_BOTTOM_BACK_CORNER,r / 255,g / 255,b / 255);
    AddVert(cornerTwo);
    vert cornerThree(glm::vec3(blockX,blockY,blockZ) + vert::LEFT_BOTTOM_FRONT_CORNER,r / 255,g / 255,b / 255);
    AddVert(cornerThree);
    vert cornerFour(glm::vec3(blockX,blockY,blockZ) + vert::RIGHT_BOTTOM_FRONT_CORNER,r / 255,g / 255,b / 255);
    AddVert(cornerFour);
    PushBackIndicies();
}
void Chunk::AddBack(int blockX,int blockY,int blockZ,int r ,int g ,int b)
{
    vert cornerOne(glm::vec3(blockX,blockY,blockZ) + vert::LEFT_BOTTOM_BACK_CORNER,r / 255,g / 255,b / 255);
    AddVert(cornerOne);
    vert cornerTwo(glm::vec3(blockX,blockY,blockZ) + vert::RIGHT_BOTTOM_BACK_CORNER,r / 255,g / 255,b / 255);
    AddVert(cornerTwo);
    vert cornerThree(glm::vec3(blockX,blockY,blockZ) + vert::LEFT_TOP_BACK_CORNER,r / 255,g / 255,b / 255);
    AddVert(cornerThree);
    vert cornerFour(glm::vec3(blockX,blockY,blockZ) + vert::RIGHT_TOP_BACK_CORNER,r / 255,g / 255,b / 255);
    AddVert(cornerFour);
    PushBackIndicies();
}
void Chunk::AddForth(int blockX,int blockY,int blockZ,int r ,int g ,int b)
{
    vert cornerOne(glm::vec3(blockX,blockY,blockZ) + vert::LEFT_BOTTOM_FRONT_CORNER,r / 255,g / 255,b / 255);
    AddVert(cornerOne);
    vert cornerTwo(glm::vec3(blockX,blockY,blockZ) + vert::RIGHT_BOTTOM_FRONT_CORNER,r / 255,g / 255,b / 255);
    AddVert(cornerTwo);
    vert cornerThree(glm::vec3(blockX,blockY,blockZ) + vert::LEFT_TOP_FRONT_CORNER,r / 255,g / 255,b / 255);
    AddVert(cornerThree);
    vert cornerFour(glm::vec3(blockX,blockY,blockZ) + vert::RIGHT_TOP_FRONT_CORNER,r / 255,g / 255,b / 255);
    AddVert(cornerFour);
    PushBackIndicies();
}
void Chunk::AddLeft(int blockX,int blockY,int blockZ,int r ,int g ,int b)
{
    vert cornerOne(glm::vec3(blockX,blockY,blockZ) + vert::LEFT_BOTTOM_BACK_CORNER,r / 255,g / 255,b / 255);
    AddVert(cornerOne);
    vert cornerTwo(glm::vec3(blockX,blockY,blockZ) + vert::LEFT_BOTTOM_FRONT_CORNER,r / 255,g / 255,b / 255);
    AddVert(cornerTwo);
    vert cornerThree(glm::vec3(blockX,blockY,blockZ) + vert::LEFT_TOP_BACK_CORNER,r / 255,g / 255,b / 255);
    AddVert(cornerThree);
    vert cornerFour(glm::vec3(blockX,blockY,blockZ) + vert::LEFT_TOP_FRONT_CORNER,r / 255,g / 255,b / 255);
    AddVert(cornerFour);
    PushBackIndicies();
}
void Chunk::AddRight(int blockX,int blockY,int blockZ,int r ,int g ,int b)
{
    vert cornerOne(glm::vec3(blockX,blockY,blockZ) + vert::RIGHT_BOTTOM_BACK_CORNER,r / 255,g / 255,b / 255);
    AddVert(cornerOne);
    vert cornerTwo(glm::vec3(blockX,blockY,blockZ) + vert::RIGHT_BOTTOM_FRONT_CORNER,r / 255,g / 255,b / 255);
    AddVert(cornerTwo);
    vert cornerThree(glm::vec3(blockX,blockY,blockZ) + vert::RIGHT_TOP_BACK_CORNER,r / 255,g / 255,b / 255);
    AddVert(cornerThree);
    vert cornerFour(glm::vec3(blockX,blockY,blockZ) + vert::RIGHT_TOP_FRONT_CORNER,r / 255,g / 255,b / 255);
    AddVert(cornerFour);
    PushBackIndicies();
}

void Chunk::GenerateGLData()
{
    for (int c = 0; c < verts.size(); c++) // X coordinates
    {
        GLvertices.push_back(verts[c].position.x);
        GLvertices.push_back(verts[c].position.y);
        GLvertices.push_back(verts[c].position.z);
        GLvertices.push_back(verts[c].red);
        GLvertices.push_back(verts[c].green);
        GLvertices.push_back(verts[c].blue);
    }
}

vector<GLuint>* Chunk::ReturnIndecies()
{
    return &GLindices;
}
vector<GLfloat>* Chunk::ReturnVerticies()
{
    return &GLvertices;
}
int Chunk::ReturnIndeciesSize()
{
    return GLindices.size();
}
int Chunk::ReturnVerticiesSize()
{
    return GLvertices.size();
}

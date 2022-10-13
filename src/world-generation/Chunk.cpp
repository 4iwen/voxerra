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
    GenerateIndicies();

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
                blockData[x][y][z] = air;
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
            //float y = abs(noise.GetNoise((float)x, (float)z) * 50);

            int y = 4;

            blockData[x][(int)y][z] = grass;
            for (int j = (int)y; j >= 0; --j)
            {
                blockData[x][j][z] = dirt;
            }
        }
    }
    //FOR WRITING OUT IN THE CONSOLE
    for (int x = 0; x < width; x++) // X coordinates
    {
        for (int z = 0; z < length; z++) // Y coordinates
        {
            //int y = (int)abs(noise.GetNoise((float)x, (float)z) * 50);
            //if(y > 9)
            //{
            //    cout << y;
            //}
            //else
            //{
            //    cout << y << " ";
            //}
            cout << "4";
        }
        cout << endl;
    }
}

void Chunk::GenerateVertices()
{
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            for (int z = 0; z < length; z++) {
                if(blockData[x][y][z] != air) // If block is occupied we check around.
                    {
                    if(CheckAround(x - 1,y,z) || x - 1 < 0) // Checks Left
                    {
                        AddLeft(x,y,z);
                    }
                    if(CheckAround(x + 1,y,z) || x + 1 > width)// Checks Right
                    {
                        AddRight(x,y,z);
                    }
                    if(CheckAround(x,y - 1,z) || y - 1 < 0)// Checks Down
                    {
                        AddBottom(x,y,z);
                    }
                    if(CheckAround(x,y + 1,z))// Checks Top
                    {
                        AddTop(x,y,z);
                    }

                    if(CheckAround(x,y,z - 1) || z - 1 < 0)// Checks Back
                    {
                        AddBack(x,y,z);
                    }
                    if(CheckAround(x,y,z + 1) || z + 1 > length)// Checks Forth
                    {
                        AddForth(x, y, z);
                    }
                }
            }
        }
    }
}

bool Chunk::CheckAround(int blockX,int blockY,int blockZ)
{
    return(blockData[blockX][blockY][blockZ] == air);
}

void Chunk::AddVert(vert v)
{
    for (int i = 0; i < verts.size(); i++)
    {
        if(verts[i].position == v.position)
        {
            verts.erase(verts.begin() + i);
            return;
        }
    }
    verts.push_back(v);
}

void Chunk::GenerateIndicies() {
    for (int x = 0; x < verts.size(); x++) {
        for (int y = 0; y < verts.size(); y++) {
            for (int z = 0; z < verts.size(); z++) {
                if (verts[x].position == verts[y].position && verts[x].position != verts[z].position) {
                    if(verts[x].position.x == verts[z].position.x && verts[x].position.y + 1 == verts[z].position.y && verts[x].position.z == verts[y].position.z
                    && verts[x].position.x == verts[y].position.x && verts[x].position.y == verts[y].position.y && verts[x].position.z + 1 == verts[y].position.z
                    )
                    {
                        GLindices.push_back(z);
                    }
                }
            }
        }
    }
}

void Chunk::AddTop(int blockX,int blockY,int blockZ)
{
    vert cornerOne(glm::vec3(blockX,blockY + 1,blockZ),1,1,1);
    AddVert(cornerOne);
    vert cornerTwo(glm::vec3(blockX + 1,blockY + 1,blockZ),1,1,1);
    AddVert(cornerTwo);
    vert cornerThree(glm::vec3(blockX,blockY + 1,blockZ + 1),1,1,1);
    AddVert(cornerThree);
    vert cornerFour(glm::vec3(blockX + 1,blockY + 1,blockZ + 1),1,1,1);
    AddVert(cornerFour);

}
void Chunk::AddBottom(int blockX,int blockY,int blockZ)
{
    vert cornerOne(glm::vec3(blockX,blockY,blockZ),1,1,1);
    AddVert(cornerOne);
    vert cornerTwo(glm::vec3(blockX + 1,blockY,blockZ),1,1,1);
    AddVert(cornerTwo);
    vert cornerThree(glm::vec3(blockX,blockY,blockZ + 1),1,1,1);
    AddVert(cornerThree);
    vert cornerFour(glm::vec3(blockX + 1,blockY,blockZ + 1),1,1,1);
    AddVert(cornerFour);
}
void Chunk::AddBack(int blockX,int blockY,int blockZ)
{
    vert cornerOne(glm::vec3(blockX,blockY,blockZ),1,1,1);
    AddVert(cornerOne);
    vert cornerTwo(glm::vec3(blockX + 1,blockY,blockZ),1,1,1);
    AddVert(cornerTwo);
    vert cornerThree(glm::vec3(blockX,blockY + 1,blockZ),1,1,1);
    AddVert(cornerThree);
    vert cornerFour(glm::vec3(blockX + 1,blockY + 1,blockZ),1,1,1);
    AddVert(cornerFour);
}
void Chunk::AddForth(int blockX,int blockY,int blockZ)
{
    vert cornerOne(glm::vec3(blockX,blockY,blockZ + 1),1,1,1);
    AddVert(cornerOne);
    vert cornerTwo(glm::vec3(blockX + 1,blockY,blockZ + 1),1,1,1);
    AddVert(cornerTwo);
    vert cornerThree(glm::vec3(blockX,blockY + 1,blockZ + 1),1,1,1);
    AddVert(cornerThree);
    vert cornerFour(glm::vec3(blockX + 1,blockY + 1,blockZ + 1),1,1,1);
    AddVert(cornerFour);
}
void Chunk::AddLeft(int blockX,int blockY,int blockZ)
{
    vert cornerOne(glm::vec3(blockX,blockY,blockZ),1,1,1);
    AddVert(cornerOne);
    vert cornerTwo(glm::vec3(blockX,blockY,blockZ + 1),1,1,1);
    AddVert(cornerTwo);
    vert cornerThree(glm::vec3(blockX,blockY + 1,blockZ),1,1,1);
    AddVert(cornerThree);
    vert cornerFour(glm::vec3(blockX,blockY + 1,blockZ + 1),1,1,1);
    AddVert(cornerFour);
}
void Chunk::AddRight(int blockX,int blockY,int blockZ)
{
    vert cornerOne(glm::vec3(blockX + 1,blockY,blockZ),1,1,1);
    AddVert(cornerOne);
    vert cornerTwo(glm::vec3(blockX + 1,blockY,blockZ + 1),1,1,1);
    AddVert(cornerTwo);
    vert cornerThree(glm::vec3(blockX + 1,blockY + 1,blockZ),1,1,1);
    AddVert(cornerThree);
    vert cornerFour(glm::vec3(blockX + 1,blockY + 1,blockZ + 1),1,1,1);
    AddVert(cornerFour);
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


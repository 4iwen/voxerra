#include "Chunk.h"

void Chunk::GenerateChunk(FastNoiseLite noise, int iPosX,int iPosY,  int iLength, int iWidth,int iHeight)
{
    cout << ("Generating Chunk");

    posX = iPosX;
    posY = iPosY;

    width = iWidth;
    length = iLength;
    height = iHeight;



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

    for (int x = 0; x < width; x++) // X coordinates
    {
        for (int z = 0; z < length; z++) // Y coordinates
        {
            int y = noise.GetNoise((float)x, (float)y) * 10;
            blockData[x][y][z] = grass;
            for (int j = y; j >= 0; --j)
            {
                blockData[x][j][z] = dirt;
            }
        }
    }
}
void Chunk::GenerateData()
{
    cout << indices.size()<<endl;
    cout << ("Generating GL Chunk")<<endl;


    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            for (int z = 0; z < length; z++) {
                if(blockData[x][y][z] != air) // If block is occupied we check around.
                {
                    if(x >= 0 && CheckAround(x - 1,y,z)) // Checks Left
                        AddLeft(x,y,z);
                    if(x < width && CheckAround(x + 1,y,z))// Checks Right
                        AddRight(x,y,z);

                    if(y >= 0 && CheckAround(x,y - 1,z))// Checks Down
                        AddBottom(x,y,z);
                    if(y < height && CheckAround(x,y + 1,z))// Checks Top
                        AddTop(x,y,z);

                    if(z >= 0 && CheckAround(x,y,z - 1))// Checks Back
                        AddBack(x,y,z);
                    if(z < length && CheckAround(x,y,z + 1))// Checks Forth
                        AddForth(x,y,z);
                }
            }
        }
    }
}

void Chunk::GenerateGLData()
{
    cout << ("Generating GL Chunk");

    GLindices[0] = indices[0].x;
    GLindices[1] = indices[1].y;
    GLindices[2] = indices[2].z;
    GLindices[3] = indices[3].red;
    GLindices[4] = indices[4].green;
    GLindices[5] = indices[5].blue;
    for (int c = 1; c < indices.size(); c++) // X coordinates
    {
        GLindices[(c * 6) + 0] = indices[c].x;
        GLindices[(c * 6) + 1] = indices[c].y;
        GLindices[(c * 6) + 2] = indices[c].z;
        GLindices[(c * 6) + 3] = indices[c].red;
        GLindices[(c * 6) + 4] = indices[c].green;
        GLindices[(c * 6) + 5] = indices[c].blue;
    }
}

void Chunk::AddTop(int blockX,int blockY,int blockZ)
{
    indi curIndi;
    curIndi.x = blockX;
    curIndi.y = blockY + 1;
    curIndi.z = blockZ;
    curIndi.red = 1;
    curIndi.green = 1;
    curIndi.blue = 1;
    indices.push_back(curIndi);
    curIndi.x = blockX + 1;
    curIndi.y = blockY + 1;
    curIndi.z = blockZ;
    curIndi.red = 1;
    curIndi.green = 1;
    curIndi.blue = 1;
    indices.push_back(curIndi);
    curIndi.x = blockX;
    curIndi.y = blockY + 1;
    curIndi.z = blockZ + 1;
    curIndi.red = 1;
    curIndi.green = 1;
    curIndi.blue = 1;
    indices.push_back(curIndi);
    curIndi.x = blockX + 1;
    curIndi.y = blockY + 1;
    curIndi.z = blockZ + 1;
    curIndi.red = 1;
    curIndi.green = 1;
    curIndi.blue = 1;
    indices.push_back(curIndi);

    GLvertices[v] = i - 3;
    v++;
    GLvertices[v] = i - 2;
    v++;
    GLvertices[v] = i - 1;
    v++;

    GLvertices[v] = i;
    v++;
    GLvertices[v] = i - 1;
    v++;
    GLvertices[v] = i - 2;
    v++;
}

void Chunk::AddBottom(int blockX,int blockY,int blockZ)
{
    indices[i].x = blockX;
    indices[i].y = blockY;
    indices[i].z = blockZ;
    indices[i].red = 1;
    indices[i].green = 1;
    indices[i].blue = 1;
    i++;
    indices[i].x = blockX + 1;
    indices[i].y = blockY;
    indices[i].z = blockZ;
    indices[i].red = 1;
    indices[i].green = 1;
    indices[i].blue = 1;
    i++;
    indices[i].x = blockX;
    indices[i].y = blockY;
    indices[i].z = blockZ + 1;
    indices[i].red = 1;
    indices[i].green = 1;
    indices[i].blue = 1;
    i++;
    indices[i].x = blockX + 1;
    indices[i].y = blockY;
    indices[i].z = blockZ + 1;
    indices[i].red = 1;
    indices[i].green = 1;
    indices[i].blue = 1;
    i++;

    GLvertices[v] = i - 3;
    v++;
    GLvertices[v] = i - 2;
    v++;
    GLvertices[v] = i - 1;
    v++;

    GLvertices[v] = i;
    v++;
    GLvertices[v] = i - 1;
    v++;
    GLvertices[v] = i - 2;
    v++;
}

void Chunk::AddBack(int blockX,int blockY,int blockZ)
{
    indices[i].x = blockX;
    indices[i].y = blockY;
    indices[i].z = blockZ;
    indices[i].red = 1;
    indices[i].green = 1;
    indices[i].blue = 1;
    i++;
    indices[i].x = blockX;
    indices[i].y = blockY + 1;
    indices[i].z = blockZ;
    indices[i].red = 1;
    indices[i].green = 1;
    indices[i].blue = 1;
    i++;
    indices[i].x = blockX;
    indices[i].y = blockY + 1;
    indices[i].z = blockZ + 1;
    indices[i].red = 1;
    indices[i].green = 1;
    indices[i].blue = 1;
    i++;
    indices[i].x = blockX;
    indices[i].y = blockY;
    indices[i].z = blockZ + 1;
    indices[i].red = 1;
    indices[i].green = 1;
    indices[i].blue = 1;
    i++;

    GLvertices[v] = i - 3;
    v++;
    GLvertices[v] = i - 2;
    v++;
    GLvertices[v] = i - 1;
    v++;

    GLvertices[v] = i;
    v++;
    GLvertices[v] = i - 1;
    v++;
    GLvertices[v] = i - 2;
    v++;
}

void Chunk::AddForth(int blockX,int blockY,int blockZ)
{
    indices[i].x = blockX + 1;
    indices[i].y = blockY;
    indices[i].z = blockZ;
    indices[i].red = 1;
    indices[i].green = 1;
    indices[i].blue = 1;
    i++;
    indices[i].x = blockX + 1;
    indices[i].y = blockY + 1;
    indices[i].z = blockZ;
    indices[i].red = 1;
    indices[i].green = 1;
    indices[i].blue = 1;
    i++;
    indices[i].x = blockX + 1;
    indices[i].y = blockY;
    indices[i].z = blockZ + 1;
    indices[i].red = 1;
    indices[i].green = 1;
    indices[i].blue = 1;
    i++;
    indices[i].x = blockX + 1;
    indices[i].y = blockY + 1;
    indices[i].z = blockZ + 1;
    indices[i].red = 1;
    indices[i].green = 1;
    indices[i].blue = 1;
    i++;

    GLvertices[v] = i - 3;
    v++;
    GLvertices[v] = i - 2;
    v++;
    GLvertices[v] = i - 1;
    v++;

    GLvertices[v] = i;
    v++;
    GLvertices[v] = i - 1;
    v++;
    GLvertices[v] = i - 2;
    v++;
}

void Chunk::AddLeft(int blockX,int blockY,int blockZ)
{
    indices[i].x = blockX;
    indices[i].y = blockY;
    indices[i].z = blockZ;
    indices[i].red = 1;
    indices[i].green = 1;
    indices[i].blue = 1;
    i++;
    indices[i].x = blockX;
    indices[i].y = blockY + 1;
    indices[i].z = blockZ;
    indices[i].red = 1;
    indices[i].green = 1;
    indices[i].blue = 1;
    i++;
    indices[i].x = blockX + 1;
    indices[i].y = blockY + 1;
    indices[i].z = blockZ;
    indices[i].red = 1;
    indices[i].green = 1;
    indices[i].blue = 1;
    i++;
    indices[i].x = blockX + 1;
    indices[i].y = blockY;
    indices[i].z = blockZ + 1;
    indices[i].red = 1;
    indices[i].green = 1;
    indices[i].blue = 1;
    i++;

    GLvertices[v] = i - 3;
    v++;
    GLvertices[v] = i - 2;
    v++;
    GLvertices[v] = i - 1;
    v++;

    GLvertices[v] = i;
    v++;
    GLvertices[v] = i - 1;
    v++;
    GLvertices[v] = i - 2;
    v++;
}

void Chunk::AddRight(int blockX,int blockY,int blockZ)
{
    indices[i].x = blockX + 1;
    indices[i].y = blockY;
    indices[i].z = blockZ;
    indices[i].red = 1;
    indices[i].green = 1;
    indices[i].blue = 1;
    i++;
    indices[i].x = blockX + 1;
    indices[i].y = blockY + 1;
    indices[i].z = blockZ;
    indices[i].red = 1;
    indices[i].green = 1;
    indices[i].blue = 1;
    i++;
    indices[i].x = blockX + 1;
    indices[i].y = blockY + 1;
    indices[i].z = blockZ + 1;
    indices[i].red = 1;
    indices[i].green = 1;
    indices[i].blue = 1;
    i++;
    indices[i].x = blockX + 1;
    indices[i].y = blockY;
    indices[i].z = blockZ + 1;
    indices[i].red = 1;
    indices[i].green = 1;
    indices[i].blue = 1;
    i++;

    GLvertices[v] = i - 3;
    v++;
    GLvertices[v] = i - 2;
    v++;
    GLvertices[v] = i - 1;
    v++;

    GLvertices[v] = i;
    v++;
    GLvertices[v] = i - 1;
    v++;
    GLvertices[v] = i - 2;
    v++;
}



bool Chunk::CheckAround(int blockX,int blockY,int blockZ)
{
    cout << "check " << blockX << blockY << blockZ << endl;
    return(blockData[blockX][blockY][blockZ] == air);
}

vector<GLuint>* Chunk::ReturnIndecies()
{
    return &GLindices;
}
vector<GLfloat>* Chunk::ReturnVerticies()
{
    return &GLvertices;
}


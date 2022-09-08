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

    GLvertices[0] = verts[0].x;
    GLvertices[1] = verts[1].y;
    GLvertices[2] = verts[2].z;
    GLvertices[3] = verts[3].red;
    GLvertices[4] = verts[4].green;
    GLvertices[5] = verts[5].blue;
    for (int c = 1; c < verts.size(); c++) // X coordinates
    {
        GLvertices[(c * 6) + 0] = verts[c].x;
        GLvertices[(c * 6) + 1] = verts[c].y;
        GLvertices[(c * 6) + 2] = verts[c].z;
        GLvertices[(c * 6) + 3] = verts[c].red;
        GLvertices[(c * 6) + 4] = verts[c].green;
        GLvertices[(c * 6) + 5] = verts[c].blue;
    }
}

//function that deletes overlapping indices
void Chunk::AddVert(vert v)
{
    for (int c = 0; c < verts.size(); c++) // X coordinates
    {
        if(verts[c].x == v.x && verts[c].y == v.y && verts[c].z == v.z)
        {
            verts.erase(verts.begin() + c);
            return;
        }
    }
    verts.push_back(v);
}

void Chunk::GenerateIndicies() {
    for(int one = 0; one > verts.size();one++)
    {
        for(int two = 0; two > verts.size();two++)
        {
            for(int three = 0; three > verts.size();three++)
            {
                if(one != two && two != three && one != three)
                {
                    if(verts[one].x == verts[three].x + 1 && verts[one].y == verts[three].y && verts[one].z == verts[three].z)
                    {
                        if(verts[one].x == verts[three].x && verts[one].y == verts[three].y + 1 && verts[one].z == verts[three].z)
                        {
                            indices.push_back(one);
                            indices.push_back(two);
                            indices.push_back(three);
                            cout << ("Added 3 Triangles ") << indices.size() << endl;
                        }
                    }
                    if(verts[one].x == verts[three].x - 1 && verts[one].y == verts[three].y && verts[one].z == verts[three].z)
                    {
                        if(verts[one].x == verts[three].x && verts[one].y == verts[three].y - 1 && verts[one].z == verts[three].z)
                        {
                            indices.push_back(one);
                            indices.push_back(two);
                            indices.push_back(three);
                            cout << ("Added 3 Triangles ") << indices.size() << endl;
                        }
                    }
                }
            }
        }
    }
}

void Chunk::AddTop(int blockX,int blockY,int blockZ)
{
    vert curVert;
    curVert.x = blockX;
    curVert.y = blockY + 1;
    curVert.z = blockZ;
    curVert.red = 1;
    curVert.green = 1;
    curVert.blue = 1;
    AddVert(curVert);
    cout << curVert.x << " " << curVert.y << " " << curVert.z << endl;

    curVert.x = blockX + 1;
    curVert.y = blockY + 1;
    curVert.z = blockZ;
    curVert.red = 1;
    curVert.green = 1;
    curVert.blue = 1;
    AddVert(curVert);
    cout << curVert.x << " " << curVert.y << " " << curVert.z << endl;

    curVert.x = blockX;
    curVert.y = blockY + 1;
    curVert.z = blockZ + 1;
    curVert.red = 1;
    curVert.green = 1;
    curVert.blue = 1;
    AddVert(curVert);
    cout << curVert.x << " " << curVert.y << " " << curVert.z << endl;

    curVert.x = blockX + 1;
    curVert.y = blockY + 1;
    curVert.z = blockZ + 1;
    curVert.red = 1;
    curVert.green = 1;
    curVert.blue = 1;
    AddVert(curVert);
    cout << curVert.x << " " << curVert.y << " " << curVert.z << endl;
}

void Chunk::AddBottom(int blockX,int blockY,int blockZ)
{
    vert curVert;
    curVert.x = blockX;
    curVert.y = blockY;
    curVert.z = blockZ;
    curVert.red = 1;
    curVert.green = 1;
    curVert.blue = 1;
    AddVert(curVert);

    curVert.x = blockX + 1;
    curVert.y = blockY;
    curVert.z = blockZ;
    curVert.red = 1;
    curVert.green = 1;
    curVert.blue = 1;
    AddVert(curVert);

    curVert.x = blockX;
    curVert.y = blockY;
    curVert.z = blockZ + 1;
    curVert.red = 1;
    curVert.green = 1;
    curVert.blue = 1;
    AddVert(curVert);

    curVert.x = blockX + 1;
    curVert.y = blockY;
    curVert.z = blockZ + 1;
    curVert.red = 1;
    curVert.green = 1;
    curVert.blue = 1;
    AddVert(curVert);
}

void Chunk::AddBack(int blockX,int blockY,int blockZ)
{

}

void Chunk::AddForth(int blockX,int blockY,int blockZ)
{
    vert curVert;
    curVert.x = blockX + 1;
    curVert.y = blockY;
    curVert.z = blockZ;
    curVert.red = 1;
    curVert.green = 1;
    curVert.blue = 1;
    AddVert(curVert);

    curVert.x = blockX + 1;
    curVert.y = blockY + 1;
    curVert.z = blockZ;
    curVert.red = 1;
    curVert.green = 1;
    curVert.blue = 1;
    AddVert(curVert);

    curVert.x = blockX + 1;
    curVert.y = blockY;
    curVert.z = blockZ + 1;
    curVert.red = 1;
    curVert.green = 1;
    curVert.blue = 1;
    AddVert(curVert);

    curVert.x = blockX + 1;
    curVert.y = blockY + 1;
    curVert.z = blockZ + 1;
    curVert.red = 1;
    curVert.green = 1;
    curVert.blue = 1;
    AddVert(curVert);
}

void Chunk::AddLeft(int blockX,int blockY,int blockZ)
{
    vert curVert;
    curVert.x = blockX;
    curVert.y = blockY;
    curVert.z = blockZ;
    curVert.red = 1;
    curVert.green = 1;
    curVert.blue = 1;
    AddVert(curVert);

    curVert.x = blockX;
    curVert.y = blockY + 1;
    curVert.z = blockZ;
    curVert.red = 1;
    curVert.green = 1;
    curVert.blue = 1;
    AddVert(curVert);

    curVert.x = blockX + 1;
    curVert.y = blockY + 1;
    curVert.z = blockZ;
    curVert.red = 1;
    curVert.green = 1;
    curVert.blue = 1;
    AddVert(curVert);

    curVert.x = blockX + 1;
    curVert.y = blockY;
    curVert.z = blockZ + 1;
    curVert.red = 1;
    curVert.green = 1;
    curVert.blue = 1;
    AddVert(curVert);
}

void Chunk::AddRight(int blockX,int blockY,int blockZ)
{
    vert curVert;
    curVert.x = blockX + 1;
    curVert.y = blockY;
    curVert.z = blockZ;
    curVert.red = 1;
    curVert.green = 1;
    curVert.blue = 1;
    AddVert(curVert);

    curVert.x = blockX + 1;
    curVert.y = blockY + 1;
    curVert.z = blockZ;
    curVert.red = 1;
    curVert.green = 1;
    curVert.blue = 1;
    AddVert(curVert);

    curVert.x = blockX + 1;
    curVert.y = blockY + 1;
    curVert.z = blockZ + 1;
    curVert.red = 1;
    curVert.green = 1;
    curVert.blue = 1;
    AddVert(curVert);

    curVert.x = blockX + 1;
    curVert.y = blockY + 1;
    curVert.z = blockZ + 1;
    curVert.red = 1;
    curVert.green = 1;
    curVert.blue = 1;
    AddVert(curVert);
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


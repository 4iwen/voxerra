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

//function that only adds the vertices to the vector if they dont overlap with another vert
void Chunk::AddVert(vert v)
{
    for (int i = 0; i < verts.size(); i++)
    {
        if(verts[i].x == v.x && verts[i].y == v.y && verts[i].z == v.z)
        {
            verts.erase(verts.begin() + i);
            return;
        }
    }
    verts.push_back(v);
}

void Chunk::GenerateIndicies() {
    for(int one = 0; one < verts.size();one++)
    {
        for(int two = 0; two < verts.size();two++)
        {
            for(int three = 0; three < verts.size();three++)
            {
                for(int four = 0; four < verts.size();four++)
                {
                    if(verts[two].x == verts[one].x && verts[two].y == verts[one].y + 1 && verts[two].z == verts[one].z)//LEFT TYPE WALL
                    {
                        if(verts[three].x == verts[one].x + 1 && verts[three].y == verts[one].y && verts[three].z == verts[one].z &&
                           verts[four].x == verts[one].x + 1 && verts[four].y == verts[one].y + 1 && verts[four].z == verts[one].z)
                        {
                            PushBackIndice(one,two,four);
                            PushBackIndice(one,three,four);
                        }
                    }

                    if(verts[two].x == verts[one].x && verts[two].y == verts[one].y + 1 && verts[two].z == verts[one].z)//RIGHT TYPE WALL
                    {
                        if(verts[three].x == verts[one].x && verts[three].y == verts[one].y && verts[three].z == verts[one].z  + 1 &&
                           verts[four].x == verts[one].x && verts[four].y == verts[one].y + 1 && verts[four].z == verts[one].z  + 1 )
                        {
                            PushBackIndice(one,two,four);
                            PushBackIndice(one,three,four);
                        }
                    }

                    if(verts[two].x == verts[one].x + 1 && verts[two].y == verts[one].y && verts[two].z == verts[one].z)//FLOOR
                    {
                        if(verts[three].x == verts[one].x && verts[three].y == verts[one].y && verts[three].z == verts[one].z  + 1 &&
                           verts[four].x == verts[one].x + 1 && verts[four].y == verts[one].y && verts[four].z == verts[one].z  + 1 )
                        {
                            PushBackIndice(one,two,four);
                            PushBackIndice(one,three,four);
                        }
                    }
                }
            }
        }
    }
}

void Chunk::PushBackIndice(int one, int two, int three)
{
    GLindices.push_back(one);
    GLindices.push_back(two);
    GLindices.push_back(three);
}

void Chunk::AddTop(int blockX,int blockY,int blockZ)
{
    vert curVert;
    curVert.x = blockX;
    curVert.y = blockY + 1;
    curVert.z = blockZ;
    curVert.red = .1;
    curVert.green = .1;
    curVert.blue = .1;
    AddVert(curVert);

    curVert.x = blockX + 1;
    curVert.y = blockY + 1;
    curVert.z = blockZ;
    curVert.red = .1;
    curVert.green = .1;
    curVert.blue = .1;
    AddVert(curVert);

    curVert.x = blockX + 1;
    curVert.y = blockY + 1;
    curVert.z = blockZ + 1;
    curVert.red = .1;
    curVert.green = .1;
    curVert.blue = .1;
    AddVert(curVert);

    curVert.x = blockX;
    curVert.y = blockY + 1;
    curVert.z = blockZ + 1;
    curVert.red = .1;
    curVert.green = .1;
    curVert.blue = .1;
    AddVert(curVert);

    //cout<<"added top"<<endl;
}

void Chunk::AddBottom(int blockX,int blockY,int blockZ)
{
    vert curVert;
    curVert.x = blockX;
    curVert.y = blockY;
    curVert.z = blockZ;
    curVert.red = .3;
    curVert.green = .3;
    curVert.blue = .3;
    AddVert(curVert);

    curVert.x = blockX + 1;
    curVert.y = blockY;
    curVert.z = blockZ;
    curVert.red = .3;
    curVert.green = .3;
    curVert.blue = .3;
    AddVert(curVert);

    curVert.x = blockX + 1;
    curVert.y = blockY;
    curVert.z = blockZ + 1;
    curVert.red = .3;
    curVert.green = .3;
    curVert.blue = .3;
    AddVert(curVert);

    curVert.x = blockX;
    curVert.y = blockY;
    curVert.z = blockZ + 1;
    curVert.red = .3;
    curVert.green = .3;
    curVert.blue = .3;
    AddVert(curVert);

    //cout<<"added bottom"<<endl;
}

void Chunk::AddBack(int blockX,int blockY,int blockZ)
{
    vert curVert;
    curVert.x = blockX;
    curVert.y = blockY;
    curVert.z = blockZ;
    curVert.red = .5;
    curVert.green = 1;
    curVert.blue = .5;
    AddVert(curVert);

    curVert.x = blockX;
    curVert.y = blockY;
    curVert.z = blockZ + 1;
    curVert.red = .5;
    curVert.green = 1;
    curVert.blue = .5;
    AddVert(curVert);

    curVert.x = blockX;
    curVert.y = blockY + 1;
    curVert.z = blockZ + 1;
    curVert.red = .5;
    curVert.green = 1;
    curVert.blue = .5;
    AddVert(curVert);

    curVert.x = blockX;
    curVert.y = blockY + 1;
    curVert.z = blockZ;
    curVert.red = .5;
    curVert.green = 1;
    curVert.blue = .5;
    AddVert(curVert);

    //cout<<"added back"<<endl;
}

void Chunk::AddForth(int blockX,int blockY,int blockZ)
{
    vert curVert;
    curVert.x = blockX + 1;
    curVert.y = blockY;
    curVert.z = blockZ;
    curVert.red = .7;
    curVert.green = 1;
    curVert.blue = .7;
    AddVert(curVert);

    curVert.x = blockX + 1;
    curVert.y = blockY;
    curVert.z = blockZ + 1;
    curVert.red = .7;
    curVert.green = 1;
    curVert.blue = .7;
    AddVert(curVert);

    curVert.x = blockX + 1;
    curVert.y = blockY + 1;
    curVert.z = blockZ + 1;
    curVert.red = .7;
    curVert.green = 1;
    curVert.blue = .7;
    AddVert(curVert);

    curVert.x = blockX;
    curVert.y = blockY + 1;
    curVert.z = blockZ + 1;
    curVert.red = .7f;
    curVert.green = 1;
    curVert.blue = .7f;
    AddVert(curVert);

    //cout<<"added forth"<<endl;
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

    curVert.x = blockX;
    curVert.y = blockY + 1;
    curVert.z = blockZ;
    curVert.red = 1;
    curVert.green = 1;
    curVert.blue = 1;
    AddVert(curVert);
    //cout<<"added lefts"<<endl;
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

    curVert.x = blockX;
    curVert.y = blockY + 1;
    curVert.z = blockZ + 1;
    curVert.red = 1;
    curVert.green = 1;
    curVert.blue = 1;
    AddVert(curVert);
    //cout<<"added right"<<endl;
}

void Chunk::GenerateGLData()
{
    for (int c = 0; c < verts.size(); c++) // X coordinates
    {
        GLvertices.push_back(verts[c].x);
        GLvertices.push_back(verts[c].y);
        GLvertices.push_back(verts[c].z);
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


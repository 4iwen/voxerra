#include "Chunk.h"

void Chunk::GenerateChunk(FastNoiseLite iNoise, int iPosX,int iPosY,  int iLength, int iWidth,int iHeight)
{
    //cout << ("Generating Chunk");
    posX = iPosX;
    posY = iPosY;

    width = iWidth;
    length = iLength;
    height = iHeight;

    FillEmpty();

    GenerateNoise(iNoise);



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

            int y = 3;

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
            cout << "3";
        }
        cout << endl;
    }
}

void Chunk::GenerateVertices()
{
    for (int x = 0; x < width; x++) {
        for (int z = 0; z < length; z++) {
            for (int y = 0; y < height; y++) {
                if(blockData[x][y][z] != air) // If block is occupied we check around.
                    {
                    if(x - 1 < 0 || CheckAround(x - 1,y,z)) // Checks Left
                    {
                        AddLeft(x,y,z);
                    }
                    if(x + 1 < width || CheckAround(x,y,z + 1))// Checks Right
                    {
                        AddRight(x,y,z);
                    }
                    if(y - 1 > 0 || CheckAround(x,y - 1,z))// Checks Down
                    {
                        AddBottom(x,y,z);
                    }
                    if(y + 1 < height || CheckAround(x,y + 1,z))// Checks Top
                    {
                        AddTop(x,y,z);
                    }

                    if(z - 1 > 0 || CheckAround(x - 1,y,z))// Checks Back
                    {
                        AddBack(x,y,z);
                    }
                    if(z + 1 < length || CheckAround(x + 1,y,z))// Checks Forth
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
    for (int c = 0; c < verts.size(); c++)
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
    //cout<< GLindices.size()  << " GLINDICES " << endl;

    for (int c = 0; c < verts.size(); c++) // X coordinates
    {
        GLvertices.push_back(verts[c].x);
        GLvertices.push_back(verts[c].y);
        GLvertices.push_back(verts[c].z);
        GLvertices.push_back(verts[c].red);
        GLvertices.push_back(verts[c].green);
        GLvertices.push_back(verts[c].blue);
    }
    //cout<< verts.size() << " VERTICES " << endl;
    //cout<< GLvertices.size() << " GLVERTICES " << endl;
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


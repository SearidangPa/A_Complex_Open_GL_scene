#pragma once

#include "DisplayableObject.h"
#include <string>
#include <vector>
#include <string>

class Tree:
public DisplayableObject
{
public:
    Tree();
    Tree(const std::string& filename);
    ~Tree(){}
    
    void Display();
    void addReplaceString(char flag, std::string str);
    void setReplaceString(char flag, std::string str);
    void setNumIter(unsigned int num);
    void setInitString(std::string str);
    
private:
    void branch();
    GLint texID;
    void getSequence();
    int iter = 2;
    std::string init = "ff-[-&^ f + ff + <][-& f] [+^ ff +] < + [+>f--f&-f]";
    std::vector<std::string> change;
    std::vector<char> flags;
    std::string sequence;
    bool toTexture = false;     // Flag to check if texture loaded correctly
};


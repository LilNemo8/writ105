#ifndef MAT_H
#define MAT_H
#include <vector>
#include <string>

class mat{
    bool exist;
    std::string color;

    public:
    mat();

    void manager_dialogue(int dialogue);
    void visuals_dialogue(int dialogue);
    void games_dialogue(int dialogue);



    void update_existence();
    bool exists();

};


#endif
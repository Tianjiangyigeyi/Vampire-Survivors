#include "../common/config.h"
#include "../util/Utility.h"

void ValLine::Render(bool Is_Changed, int id)
{
    float ratio = (float)val_left / (float)max_val;
    int l_len = ratio * actual_length;
    
    // std::cout<<"l_len: "<<l_len<<"actual_length: "<<actual_length<<"ratio: "<<ratio<<"val_left: "<<val_left<<"max_val: "<<max_val<<std::endl;
    int r_len = actual_length - l_len;
    int l_posx = posx;
    int r_posx = posx + l_len;
    Utility::generateBackgroundColorTexture(l_posx, posy, l_len, actual_height, color_left.r, color_left.g, color_left.b, Is_Changed, id);
    Utility::generateBackgroundColorTexture(r_posx, posy, r_len, actual_height, color_right.r, color_right.g, color_right.b, Is_Changed, id+100);

}
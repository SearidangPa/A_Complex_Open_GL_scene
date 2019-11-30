#include "DisplayableObject.h"
#include "Animation.h"
#include "Camera.h"
class Robot :
public DisplayableObject,
public Animation,
public Input
{
public:
    Robot();
    ~Robot();
    
    void Display();                             // define display function (to be called by MyScene)
    void Update(const double& deltaTime);        // define update function (to be called by MyScene)
    void HandleKey(unsigned char key, int state, int mx, int my);
private:
    /* draw functions */
    void DrawRobot();
    void DrawLeftLeg();
    void DrawRightLeg();
    void Draw_left_Arm();
    void Draw_right_Arm();
    void box(float sx, float sy, float sz);
    
    /*----------------------------------Initialize variables------------------------------*/
    float animationTime;
    float aT=0;
    
    //head and body parameters
    float r_head = 1.5f;
    float body_width = 5.f; float body_height = 8.f; float body_thickness = 1.5f;
    
    //joint params
    float r_big_joint= 0.5f; float r_small_joint = 0.35f;
    //legs params
    float up_leg_width = 1.5f; float up_leg_length = 4.5f; float up_leg_thickness = 1.5f;
    float low_leg_width = 1.7f; float low_leg_length = 5.f; float low_leg_thickness = 1.25f;
    
    //arms params
    float up_arm_width = 1.f; float up_arm_length = 3.75f; float up_arm_thickness = 1.25f;
    float low_arm_width = 1.f; float low_arm_length = 4.5f; float low_arm_thickness = 0.8f;
    
    //feet param
    float feet_length = 2.5f;
    
    //rotattion params for legs and arms
    float rotate_right_up_arm=0; float rotate_right_low_arm =0;
    float rotate_left_up_arm=0; float rotate_left_low_arm=0;
    float rotate_left_upper_leg=0; float rotate_left_low_leg=0;
    float rotate_right_upper_leg=0; float rotate_right_low_leg=0;
    
    //direction of translation of the robot and the orientation of the robot depending on the user's input
    int dir=1; int orient = 0;
    bool stop = false;              //whether the user want the robot to stand still
    
    float adjust_sit_down = 0;      //how much translation the robot should sink down for sitting
    float speed;                    //speed of the robot walking
};


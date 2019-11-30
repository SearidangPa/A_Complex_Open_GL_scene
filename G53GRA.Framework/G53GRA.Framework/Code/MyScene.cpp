#include "MyScene.h"
#include "Chair.h"
#include "Lamp_post.h"
#include "Bus_shelter.h"
#include "Tree.h"
#include "Floor.h"
#include "Terrain.h"
#include "Sun.h"
#include "Skybox.h"
#include "Bus_Stand_Pole.h"
#include "Robot.h"
#include "Light.h"

MyScene::MyScene(int argc, char** argv, const char *title, const int& windowWidth, const int& windowHeight)
	: Scene(argc, argv, title, windowWidth, windowHeight)
{}
void MyScene::Initialise()
{
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    /* create our skybox */
    GLuint up = Scene::GetTexture("Texture/top.bmp");
    GLuint back = Scene::GetTexture("Texture/back.bmp");
    GLuint left = Scene::GetTexture("Texture/left.bmp");
    GLuint right = Scene::GetTexture("Texture/right.bmp");
    GLuint front = Scene::GetTexture("Texture/front.bmp");
	Skybox *skybox = new Skybox(up, left, right, back, front);
    skybox->size(15000.0f, 3000.0f, 15000.0f);
    skybox->position(0,2400,-10000);

    /* create our sun */
	Sun *sun = new Sun();
	sun->position(2000.0f, 5000.0f, -200.0f);

    /* create our chair */
    Chair* chair = new Chair("Texture/wood.bmp");
    chair->size(28.0f);
    chair->position(-3800,-350,3600);
    chair->orientation(0,180,0);
    
    /* create our bus stop */
    Bus_shelter* bus_shelter = new Bus_shelter("Texture/merge_ads_vertical.bmp",  "Texture//bus_schedule.bmp", "Texture//bus_shelter_sign.bmp");
    bus_shelter->size(25.0f);
    bus_shelter->position(-2500,-400,3700);
    bus_shelter->orientation(0,180,0);
    
    /* create our Bus stand pole displaying information */
    Bus_Stand_Pole* pole = new Bus_Stand_Pole("Texture//pole_texture.bmp", "Texture/bus_stop_flag.bmp", "Texture/bus_schedule_1.bmp", "Texture/bus_schedule_2.bmp", "Texture/bus_schedule_3.bmp", "Texture/display1.bmp", "Texture/display2.bmp", "Texture/display3.bmp");
    pole->size(30.0f);
    pole->position(-1500, -440, 3600);
    
    /* create our robot */
    Robot* robot = new Robot();
    robot->size(20);
    robot->position(-500, 350, 3200);

    /* create our terrain */
    Terrain* terr = new Terrain("Texture/grass.bmp");
    terr->position(-1500,-450,-9400);
    terr->size(30000, 19000, 19000);
    
    /* create our grass lawn next to the sidewalk */
    Floor* grass = new Floor("Texture/grass.bmp", 1, 1000);
    grass->position(-2500,-440,4500);
    grass->size(9);
    
    /* create our road */
    Floor* road = new Floor("Texture/road.bmp", 1, 1000);
    road->position(-2500,-440,1500);
    road->size(12);

    /* add our objects to scene*/
    AddObjectToScene(pole);
    AddObjectToScene(bus_shelter);
    AddObjectToScene(chair);
    AddObjectToScene(robot);
    Draw_Trees();
    Draw_Street_Lamp();
    
    /* Environment */
    AddObjectToScene(sun);
    AddObjectToScene(skybox);
    AddObjectToScene(terr);
    AddObjectToScene(grass);
    Draw_sidewalk();
    AddObjectToScene(road);
    Draw_yellow_strip();
    Draw_road_divide();
}

/*draw three street lamps. Place them on the sidewalk separated by incr in the x direction */
void MyScene::Draw_Street_Lamp(){
    Lamp_post* lamp[3];
    Light* light[3];
    
    float x_pos = -8000; //initialize the position of the first lamp post
    int incr = 5000;     //how much the lamp posts are separated from each other by
    
    for (int i = 0; i < 3; i++){
        lamp[i] = new Lamp_post("Texture/lamp_tex.bmp", "Texture/traffic_sign.bmp", "Texture/lamp_number.bmp" );
        lamp[i]->position(x_pos,-450, 3000);
        lamp[i]->size(40);
        lamp[i]->orientation(0,90,0);
        
        /* create three light object at the same position. The position must be a static variable,
         therefore explicit number must be specified here. */
        if (i == 0){
            static GLfloat position[] = {-8000, 50*13, 2615, 1};
            light[i] = new Light(i, position, GL_LIGHT1, GL_LIGHT2);
        }
        if (i == 1){
            static GLfloat position[] = {-3000, 50*13, 2615, 1};
            light[i] = new Light(i, position, GL_LIGHT3, GL_LIGHT4);
        }
        if (i == 2){
            static GLfloat position[] = {2000, 50*13, 2615, 1};
            light[i] = new Light(i, position, GL_LIGHT5, GL_LIGHT6);
        }
        x_pos += incr;
        AddObjectToScene(lamp[i]);
        AddObjectToScene(light[i]);
    }
}
/* draw four trees on each side of the road, separated from each other by incr in the x direction */
void MyScene::Draw_Trees(){
    int num_trees = 4;
    Tree* tree[num_trees];
    
    int x_pos = -8000; //initialize the position of the first trees
    int incr = 3500;   //how much the trees are separated from each other by
    
    std::string sequence1 = "ff[^ff-<ff>][+ff-]";
    std::string sequence2 = "ff[<f&-f][^ff-<f>]";
    /* the trees on the sidewalk */
    for (int i = 0; i < num_trees; i++){
        tree[i] = new Tree ("Texture/bark.bmp");
        tree[i]->position(x_pos,-500, -1300);
        tree[i]->size(300);
        
        /*alternate the sequence so that not all trees look the same*/
        if (i % 2==1){
            tree[i]->setReplaceString('f', sequence1);
        }else{
            tree[i]->setReplaceString('f', sequence2);
        }
        x_pos += incr;
        AddObjectToScene(tree[i]);
    }
    /* the trees on the right side of the road*/
    x_pos = -8000;
    for (int i = 0; i < num_trees; i++){
        tree[i] = new Tree ("Texture//bark.bmp");
        tree[i]->position(x_pos,-500, 4500);
        tree[i]->size(300);
        
        /*alternate the sequence so that not all trees look the same*/
        if (i % 2==1){
            tree[i]->setReplaceString('f', sequence1);
        }else{
            tree[i]->setReplaceString('f', sequence2);
        }
        x_pos += incr;
        AddObjectToScene(tree[i]);
    }
}
/* draw a dark red sidewalk */
void MyScene::Draw_sidewalk(){
    /* the floor on which the robot walks on */
    Floor* sidewalk = new Floor("Texture/road.bmp", 2, 1000);
    sidewalk->position(-2500,-400,3400);
    sidewalk->size(7);
    
    /* create our slope that connects the sidewalk to the road */
    Floor* connect= new Floor("Texture/road.bmp", 3, 3000);
    connect->position(0,-440,2950);
    connect->orientation(-90, 0, 0);
    connect->size(2);
    
    /* add the objects to the screen */
    AddObjectToScene(sidewalk);
    AddObjectToScene(connect);
}


/*draw the white rectangular stripe in the middle of the road */
void MyScene::Draw_road_divide(){
    int num_stripe = 9;
    Floor* white_strip[num_stripe*2];
    int x_pos = 1150; int incr = 1500;
    for (int i = 0; i < num_stripe; i++){
        white_strip[i]= new Floor("Texture/road.bmp", 5, 100);
        white_strip[i]->position(x_pos,-400, 1450);
        white_strip[i]->size(2);
        x_pos += incr;
        AddObjectToScene(white_strip[i]);
    }
    x_pos = 1150 - incr;
    for (int i = num_stripe; i < 2*num_stripe; i++){
        white_strip[i]= new Floor("Texture/road.bmp", 5, 100);
        white_strip[i]->position(x_pos,-400, 1450);
       white_strip[i]->size(2);
        x_pos -= incr;
        AddObjectToScene(white_strip[i]);
    }
    
}
/*draw long yellow strip on each side of the road */
void MyScene::Draw_yellow_strip(){
    /* the left side of the road*/
    Floor* yellow_strip_left = new Floor("Texture/road.bmp", 4, 4000);
    yellow_strip_left->position(0,-430, 2650);
    yellow_strip_left->size(2);
    
    /* the right side of the road*/
    Floor* yellow_strip_right= new Floor("Texture/road.bmp", 4, 4000);
    yellow_strip_right->position(0,-430, 300);
    yellow_strip_right->size(2);
    
    AddObjectToScene(yellow_strip_left);
    AddObjectToScene(yellow_strip_right);
}

void MyScene::Projection()
{
	GLdouble aspect = static_cast<GLdouble>(windowWidth) / static_cast<GLdouble>(windowHeight);
	gluPerspective(60.0, aspect, 1.0, 35000.0);
}

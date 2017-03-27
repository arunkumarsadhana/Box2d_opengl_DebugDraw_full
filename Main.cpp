#define GLEW_STATIC
#include <GLFW\glfw3.h>
#include <Box2D\Box2D.h>
#include "Physics.h"
#include <vector>
using namespace std;
int main() {
    // Initialize window (this is GLFW-specific)
    GLFWwindow* window;
    if (!glfwInit()) return 1;
    window = glfwCreateWindow(960, 540, "Box2D Debug Draw", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return 2;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);//const b2Vec2 &p,float32 size,const b2Color &c

    DebugDraw debugDraw; // Declare an instance of our DebugDraw class so we can actually use it
	
    // Set up Box2D world, bodies, etc. (you should be familiar with most of this)
    int velocityIterations = 8;
    int positionIterations = 3;
    b2World* world;
    b2Body* groundBody;
    b2Body* testBody;
	b2Body* circleBody;
	b2Body* triangleBody;
    {
        b2Vec2 gravity(0.0f, -10.0f);
        world = new b2World(gravity);
        world->SetDebugDraw(&debugDraw); // YOU NEED THIS SO BOX2D KNOWS WHERE TO LOOK FOR DRAWING CALLBACKS
        debugDraw.SetFlags(b2Draw::e_shapeBit);
    }
    {
        b2BodyDef gbDef;
        gbDef.position.Set(0.0f, -10.0f);
        groundBody = world->CreateBody(&gbDef);

        b2PolygonShape gbShape;
        gbShape.SetAsBox(50.0f, 10.0f);

        groundBody->CreateFixture(&gbShape, 0.0f);
    }
    {
        b2BodyDef tbDef;
        tbDef.type = b2_dynamicBody;
        tbDef.position.Set(0.0f, 10.0f);
        testBody = world->CreateBody(&tbDef);

        b2PolygonShape tbShape;
        tbShape.SetAsBox(1.0f, 1.0f);

        b2FixtureDef tbFix;
        tbFix.shape = &tbShape;
        tbFix.density = 1.0f;
        tbFix.friction = 0.3f;
		tbFix.restitution=0.9f;
        testBody->CreateFixture(&tbFix);
    }
	{
		b2BodyDef tbDef1;
        tbDef1.type = b2_dynamicBody;
        
        circleBody = world->CreateBody(&tbDef1);

        b2CircleShape shape;
		shape.m_radius=0.5;
		shape.m_p.Set(10.0f,20.0f);
		b2FixtureDef fixtureDef;
		fixtureDef.shape=&shape;
		fixtureDef.density=1.0;
		fixtureDef.friction=0.0;
		fixtureDef.restitution=0.8;
		circleBody->CreateFixture(&fixtureDef);       
	}
	{
 b2BodyDef my_body;
my_body.position.Set(20.0f,30.0f);
my_body.type = b2_dynamicBody;
b2PolygonShape my_box;
triangleBody=world->CreateBody(&my_body);
b2Vec2 my_vertices[4];
my_vertices[0]=b2Vec2(0,-0.4);
my_vertices[1]=b2Vec2(1,1);
my_vertices[2]=b2Vec2(-1.2,1);
my_vertices[3]=b2Vec2(-0.4,1);
my_box.Set(my_vertices, 4);         
b2FixtureDef my_fixture;
my_fixture.density=1.0;
my_fixture.friction=0.8;
my_fixture.restitution=0.8;
my_fixture.shape=&my_box;
triangleBody->CreateFixture(&my_fixture);				
			}
    // Loop until user exits
    b2Timer timer;
    float last = timer.GetMilliseconds();
    while (!glfwWindowShouldClose(window)) {
        float now = timer.GetMilliseconds();
        world->Step((now - last) / 1000, 8, 3); // Step simulation forward by amount of time since last step
        last = now;

        glClear(GL_COLOR_BUFFER_BIT); // Clear screen
        glPushMatrix(); // Push matrix so we can revert after doing some transformations
        glScalef(40.0f / 960.0f, 40.0f / 540.0f, 1.0f); // Zoom out
        glTranslatef(0.0f, -5.0f, 0.0f); // Pan up
        world->DrawDebugData(); // CALL THE DRAWING CALLBACKS WE SET UP IN PHYSICS CLASS
        glPopMatrix(); // Revert transformations

        glfwSwapBuffers(window); // Push updated buffers to window
        glfwPollEvents(); // Poll user events so OS doesn't think app is frozen
    }

    // Garbage collection
    delete world;
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

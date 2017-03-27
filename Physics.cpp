#include <GL\glew.h>
#include "Physics.h"

void DebugDraw::DrawPolygon(const b2Vec2* vertices,int32 vertexCount,const b2Color& color)
{
	glColor3f(color.r,color.g,color.b);
	glBegin(GL_LINE_LOOP);
	for(int32 i=0;i<vertexCount;++i)
	{
		glVertex2f(vertices[i].x,vertices[i].y);
	}
	glEnd();
}
void DebugDraw::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) {
    // Standard OpenGL rendering stuff
    glColor4f(color.r, color.g, color.b, color.a);
    glBegin(GL_POLYGON); 
    for (int i = 0; i < vertexCount; i++) {
        glVertex2f(vertices[i].x, vertices[i].y);
    }
    glEnd();
}

/*void DebugDraw::DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color) {
    const float32 k_segments = 16.0f;
    const int vertexCount = 16;
    const float32 k_increment = 2.0f * b2_pi / k_segments;
    float32 theta = 0.0f;

    glColor4f(color.r, color.g, color.b, 0.5f);
    glBegin(GL_TRIANGLE_FAN);
    GLfloat glVertices[vertexCount * 2];
    for (int32 i = 0; i < k_segments; ++i) {
        b2Vec2 v = center + radius * b2Vec2(cos(theta), sin(theta));
        glVertex2f(v.x, v.y);
        theta += k_increment;
    }
    glEnd();

    DrawSegment(center, center + radius*axis, color);
}*/
void DebugDraw::DrawSolidCircle(const b2Vec2& center,float32 radius,const b2Vec2& axis,const b2Color& color)
{
	const float32 k_segments=16.0f;
	const float32 k_increment=2.0f*b2_pi/k_segments;
	float32 theta=0.0f;
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(0.5f*color.r,0.5f*color.g,0.5f*color.b,0.5f);
	glBegin(GL_TRIANGLE_FAN);
	for(int32 i=0;i<k_segments;i++)
	{
		b2Vec2 v=center+radius*b2Vec2(cosf(theta),sinf(theta));
		glVertex2f(v.x,v.y);
		theta+=k_increment;
	}
	glEnd();
	glDisable(GL_BLEND);
	theta=0.0f;
	glColor4f(color.r,color.g,color.b,1.0f);
	glBegin(GL_LINE_LOOP);
	for(int32 i=0;i<k_segments;++i)
	{
		b2Vec2 v=center+radius*b2Vec2(cosf(theta),sinf(theta));
		glVertex2f(v.x,v.y);
		theta+=k_increment;
	}
	glEnd();
	b2Vec2 p = center + radius*axis;
	glBegin(GL_LINES);
	glVertex2f(p.x,p.y);
	glEnd();
}
void DebugDraw::DrawCircle(const b2Vec2& center,float32 radius,const b2Color& color){
const float32 k_segments=16.0f;
const float32 k_increment=2.0f*b2_pi/k_segments;
float32 theta=0.0f;
glColor3f(color.r,color.g,color.b);
glBegin(GL_LINE_LOOP);
for(int32 i=0;i<k_segments;i++)
{
	b2Vec2 v=center+radius*b2Vec2(cosf(theta),sinf(theta));
	glVertex2f(v.x,v.y);
	theta+=k_increment;
}
glEnd();
}
void DebugDraw::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color) {
    glColor4f(color.r, color.g, color.b, 1);
    glBegin(GL_LINES);
    glVertex2f(p1.x, p1.y);
    glVertex2f(p2.x, p2.y);
    glEnd();
}




// We just need to have these to prevent override errors, they don't actually do anything right now
//void DebugDraw::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) {}
//void DebugDraw::DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color) {}
//void DebugDraw::DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color) {}
//void DebugDraw::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color) {}
void DebugDraw::DrawTransform(const b2Transform& xf) {}

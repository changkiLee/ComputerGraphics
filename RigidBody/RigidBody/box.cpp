#include "box.h"
#include <gl/glut.h>

Box::Box()
{
	box_x = box_y = box_z = 1;
	m = 1;
	n = 0;

	rot.SetIdentity();
	intertia.SetIdentity();
	intertia[0][0] = (box_y*box_y + box_z*box_z) * m/12;
	intertia[1][1] = (box_x*box_x + box_z*box_z) * m/12;
	intertia[2][2] = (box_x*box_x + box_y*box_y) * m/12;
}

Box::Box(float x, float y, float z)
{
	box_x = x;
	box_y = y;
	box_z = z;
	m = 1;
	n = 0;
	
	rot.SetIdentity();
	intertia.SetIdentity();
	intertia[0][0] = (box_y*box_y + box_z*box_z) * m/12;
	intertia[1][1] = (box_x*box_x + box_z*box_z) * m/12;
	intertia[2][2] = (box_x*box_x + box_y*box_y) * m/12;	
}

Box::Box(float x, float y, float z, float _m)
{
	box_x = x;
	box_y = y;
	box_z = z;
	m = _m;
	n = 0;

	rot.SetIdentity();
	intertia.SetIdentity();
	intertia[0][0] = (box_y*box_y + box_z*box_z) * m/12;
	intertia[1][1] = (box_x*box_x + box_z*box_z) * m/12;
	intertia[2][2] = (box_x*box_x + box_y*box_y) * m/12;	
}

Box::Box(Box &r)
{
	pos = r.pos;
	force = r.force;
	torq = r.torq;
	box_x = r.box_x;
	box_y = r.box_y;
	box_z = r.box_z;
	m = r.m;
	n = r.n;
 
	rot = r.rot;
	intertia = r.intertia;
}

Box::~Box()
{

}

void Box::addForce(GVector3 _f)
{
	force = force + _f;
}

void Box::setType(int _n)
{
	n = _n;
}

void Box::ForceApply(float dt)
{	
	// 선운동량과 위치
	pos = pos + p/m * dt;
	p = p + force * dt;
	v = v + (force / m) * dt;
}

void Box::RotApply(float dt)
{
	// 각운동량과 방향
	GVector p_0;		// 힘의 초기 작용점
	GVector3 tmp;
	if(n == 1)
	{
		p_0 = GVector(4, box_x/2, -box_y/2, -box_z/2, 0);
		p_0 = rot * p_0;
		tmp = GVector3(p_0[0], p_0[1], p_0[2]);
		torq = tmp^force;
	}

	if(n == 2)
	{
		p_0 = GVector(4, -box_x/2, -box_y/2, -box_z/2, 0);
		p_0 = rot * p_0;
		tmp = GVector3(p_0[0], p_0[1], p_0[2]);
		torq = tmp^force;
	}

	if(n == 3)
	{
		p_0 = GVector(4, -box_x/2, -box_y/2, box_z/2, 0);
		p_0 = rot * p_0;
		tmp = GVector3(p_0[0], p_0[1], p_0[2]);
		torq = tmp^force;
	}

	if(n == 4)
	{
		p_0 = GVector(4, box_x/2, -box_y/2, box_z/2, 0);
		p_0 = rot * p_0;
		tmp = GVector3(p_0[0], p_0[1], p_0[2]);
		torq = tmp^force;
	}

	l = l + torq * dt;

	GMatrix trans_rot = rot;
	trans_rot.SetTranspose();
	GMatrix inv_intertia = rot * inv(intertia) * trans_rot;

	GVector t_l = GVector(4, l[0], l[1], l[2], 0);
	w = cast_vec3(inv_intertia * t_l);

	GQuater t_w(0, w[0], w[1], w[2]);

	q = q + t_w*q*dt/2;	
	q.Normalize();

	if(q.W < -1 || q.W > 1 || q.X < -1 || q.X > 1 || q.Y < -1 || q.Y > 1 || q.Z < -1 || q.Z > 1)
	{
		q = GQuater(1.0, 0.0, 0.0, 0.0);
		rot.SetIdentity();
	}

	rot[0][0] = 1 - 2*q.Y*q.Y - 2*q.Z*q.Z;
	rot[0][1] = 2*q.X*q.Y - 2*q.W*q.Z;
	rot[0][2] = 2*q.X*q.Z + 2*q.W*q.Y;

	rot[1][0] = 2*q.X*q.Y + 2*q.W*q.Z;
	rot[1][1] = 1 - 2*q.X*q.X - 2*q.Z*q.Z;
	rot[1][2] = 2*q.Y*q.Z - 2*q.W*q.X;

	rot[2][0] = 2*q.X*q.Z - 2*q.W*q.Y;
	rot[2][1] = 2*q.Y*q.Z + 2*q.W*q.X;
	rot[2][2] = 1 - 2*q.X*q.X - 2*q.Y*q.Y;	
}

void Box::find_all_collisions()
{
	// 충돌가능한 모서리의 위치를 계산
	GVector p_0;
	GVector3 tmp0;

	p_0 = GVector(4, box_x/2, -box_y/2, -box_z/2, 0);
	p_0 = rot * p_0;
	tmp0 = GVector3(p_0[0], p_0[1], p_0[2]);
	corner[0] = tmp0 + pos;

	p_0 = GVector(4, -box_x/2, -box_y/2, -box_z/2, 0);
	p_0 = rot * p_0;
	tmp0 = GVector3(p_0[0], p_0[1], p_0[2]);
	corner[1] = tmp0 + pos;

	p_0 = GVector(4, -box_x/2, -box_y/2, box_z/2, 0);
	p_0 = rot * p_0;
	tmp0 = GVector3(p_0[0], p_0[1], p_0[2]);
	corner[2] = tmp0 + pos;
	
	p_0 = GVector(4, box_x/2, -box_y/2, box_z/2, 0);
	p_0 = rot * p_0;
	tmp0 = GVector3(p_0[0], p_0[1], p_0[2]);
	corner[3] = tmp0 + pos;
	
	p_0 = GVector(4, box_x/2, box_y/2, -box_z/2, 0);
	p_0 = rot * p_0;
	tmp0 = GVector3(p_0[0], p_0[1], p_0[2]);
	corner[4] = tmp0 + pos;
	
	p_0 = GVector(4, -box_x/2, box_y/2, -box_z/2, 0);
	p_0 = rot * p_0;
	tmp0 = GVector3(p_0[0], p_0[1], p_0[2]);
	corner[5] = tmp0 + pos;
	
	p_0 = GVector(4, -box_x/2, box_y/2, box_z/2, 0);
	p_0 = rot * p_0;
	tmp0 = GVector3(p_0[0], p_0[1], p_0[2]);
	corner[6] = tmp0 + pos;
	
	p_0 = GVector(4, box_x/2, box_y/2, box_z/2, 0);
	p_0 = rot * p_0;
	tmp0 = GVector3(p_0[0], p_0[1], p_0[2]);
	corner[7] = tmp0 + pos;

	for(int i = 0; i < 8; i++)
	{
		if(corner[i][1] <= 0)
		{
			//cout << "충돌 발생" << endl;
			contact = corner[i];

			// 충돌 종류 판단 및 충돌량 계산
			bool had_collision;
			double epsilon = 0.7;

			had_collision = false;

			if(colliding())
			{
				collision(epsilon);
				had_collision = true;
				//cout << "Colliding Contact!" << endl;
			}
			//
		}
	}
}

bool Box::colliding()
{
	GVector3 padot = pt_velocity(contact);			// 박스
	GVector3 pbdot(0.0, 0.0, 0.0);					// 바닥
	GVector3 f_n(0.0, 1.0, 0.0);
	double vrel = f_n * (padot - pbdot);

 	if(vrel >= 0)
 	{
 		return false;
 	}
 	else{
 		return true;
 	}
}

GVector3 Box::pt_velocity(GVector3 contact_pos)
{
	return v + (w^(contact_pos - pos));
}

void Box::collision(double _eps)
{
	GVector3 padot = pt_velocity(contact);			// 박스
	GVector3 pbdot(0.0, 0.0, 0.0);					// 바닥
	GVector3 f_n(0.0, 1.0, 0.0);
	GVector3 ra = contact - pos;
	GVector3 rb = contact - GVector3(0.0, 0.0, 0.0);
	double vrel = f_n * (padot - pbdot);
	double numerator = -(1 + _eps) * vrel;

	GMatrix trans_rot = rot;
	trans_rot.SetTranspose();
	GMatrix inv_intertia = rot * inv(intertia) * trans_rot;

	double term1 = 1 / m;
	//double term2
	GVector3 tmp0 = ra^f_n;
	GVector tmp1(4, tmp0[0], tmp0[1], tmp0[2], 0);
	double term3 = f_n * ((cast_vec3(inv_intertia * tmp1))^ra);
	//double term4

	double j = numerator / (term1 + term3);
	GVector3 col_force = j * f_n;

	p += col_force;
	l += ra ^ col_force;

	v = p / m;
	
	GVector t_l = GVector(4, l[0], l[1], l[2], 0);
	w = cast_vec3(inv_intertia * t_l);
}

void Box::setPos(GVector3 p)
{
	pos = p;
}

void Box::RenderBox()
{
	glPushMatrix();
	{	
		glTranslatef(pos[0], pos[1], pos[2]);
		
		float t_rot[16];
		for(int i = 0; i < 4; i++)
			for(int j = 0; j < 4; j++)
				t_rot[4*i + j] = rot[i][j];
		glMultMatrixf(t_rot);

		glScaled(box_x, box_y, box_z);
		glutSolidCube(1);
		
		
// 		상자 그리기
// 			glColor3f(0.0f, 1.0f, 0.0f);
// 			glBegin(GL_TRIANGLES);
// 			{
// 				// 밑면
// 				glVertex3f(-box_x/2, -box_y/2, box_z/2);
// 				glVertex3f(-box_x/2, -box_y/2, -box_z/2);
// 				glVertex3f(box_x/2, -box_y/2, -box_z/2);
// 				glVertex3f(-box_x/2, -box_y/2, box_z/2);
// 				glVertex3f(box_x/2, -box_y/2, box_z/2);
// 				glVertex3f(box_x/2, -box_y/2, -box_z/2);
// 	
// 				// 윗면
// 				glVertex3f(-box_x/2, box_y/2, box_z/2);
// 				glVertex3f(-box_x/2, box_y/2, -box_z/2);
// 				glVertex3f(box_x/2, box_y/2, -box_z/2);
// 				glVertex3f(-box_x/2, box_y/2, box_z/2);
// 				glVertex3f(box_x/2, box_y/2, box_z/2);
// 				glVertex3f(box_x/2, box_y/2, -box_z/2);
// 	
// 				// 좌측면
// 				glVertex3f(-box_x/2, box_y/2, -box_z/2);
// 				glVertex3f(-box_x/2, -box_y/2, -box_z/2);
// 				glVertex3f(-box_x/2, -box_y/2, box_z/2);
// 				glVertex3f(-box_x/2, -box_y/2, box_z/2);
// 				glVertex3f(-box_x/2, box_y/2, box_z/2);
// 				glVertex3f(-box_x/2, box_y/2, -box_z/2);
// 	
// 				// 우측면
// 				glVertex3f(box_x/2, box_y/2, -box_z/2);
// 				glVertex3f(box_x/2, -box_y/2, -box_z/2);
// 				glVertex3f(box_x/2, -box_y/2, box_z/2);
// 				glVertex3f(box_x/2, -box_y/2, box_z/2);
// 				glVertex3f(box_x/2, box_y/2, box_z/2);
// 				glVertex3f(box_x/2, box_y/2, -box_z/2);
// 	
// 				// 앞면
// 				glVertex3f(-box_x/2, box_y/2, -box_z/2);
// 				glVertex3f(-box_x/2, -box_y/2, -box_z/2);
// 				glVertex3f(box_x/2, -box_y/2, -box_z/2);
// 				glVertex3f(box_x/2, box_y/2, -box_z/2);
// 				glVertex3f(-box_x/2, box_y/2, -box_z/2);
// 				glVertex3f(box_x/2, -box_y/2, -box_z/2);
// 	
// 	
// 				// 뒷면
// 				glVertex3f(-box_x/2, box_y/2, box_z/2);
// 				glVertex3f(-box_x/2, -box_y/2, box_z/2);
// 				glVertex3f(box_x/2, -box_y/2, box_z/2);
// 				glVertex3f(box_x/2, box_y/2, box_z/2);
// 				glVertex3f(-box_x/2, box_y/2, box_z/2);
// 				glVertex3f(box_x/2, -box_y/2, box_z/2);
// 			}
// 			glEnd();
// 	
// 			// 꼭지점 그리기
// 			glColor3f(1.0f, 0.0f, 0.0f);
// 			glPointSize(5.0f);
// 			glBegin(GL_POINTS);
// 			{
// 				glVertex3f(-box_x/2, -box_y/2, box_z/2);
// 				glVertex3f(-box_x/2, -box_y/2, -box_z/2);
// 				glVertex3f(-box_x/2, box_y/2, box_z/2);
// 				glVertex3f(-box_x/2, box_y/2, -box_z/2);
// 	
// 				glVertex3f(box_x/2, box_y/2, box_z/2);
// 				glVertex3f(box_x/2, box_y/2, -box_z/2);
// 				glVertex3f(box_x/2, -box_y/2, box_z/2);
// 				glVertex3f(box_x/2, -box_y/2, -box_z/2);
// 	
// 			}
// 			glEnd();
	}
	glPopMatrix();
}

#include <iostream>
#include <cxtypes.h>
#include "math.h"
#include "Vector.h"
#include "Light.h"
#include "Object.h"
#include "ObjInfo.h"
#define PI 3.141592653589793238462643383279

using namespace std;

Vector Trace(Vector _ray, int _recursNumber);
ObjInfo closest_intersection(Vector _ray, Vector _eye);
Vector Shade(ObjInfo _object_point, Vector _ray, int _recursNumber);
bool Shadow_Ray(ObjInfo _object_point, Vector _ray, Light _source);
Vector Local_Illumination(ObjInfo _object_point, Vector _ray, Light _source);
Vector reflected_ray(ObjInfo _object_point, Vector _ray);
Vector refracted_ray(ObjInfo _object_point, Vector _ray);
int pMin(float a, float b, float c);
float specN(float x, int n);

// 빛의 개수
int num_light = 2;
// 물체의 개수
int num_object = 3;

// [Camera] eye, look, up, fovx
Vector eye(0.0f, 0.0f, 0.0f);
Vector look(0.0f, 0.0f, -1.0f);
Vector up(0.0f, 1.0f, 0.0f);
float fovx = 80.0;

// Light & Object
Light Light_0;
Light Light_1;
Object Object_0;
Object Object_1;
Object Object_2;

int main()
{
	///////////*   Light & Object setting   *///////////

	// Light0
	Light_0.SetCat(1);	// point light
	Light_0.SetPosition(3.0f, 3.0f, 3.0f);
	Light_0.SetAmb(1.0f, 0.3f, 0.1f);
	Light_0.SetDiff(1.0f, 1.0f, 1.0f);
	Light_0.SetSpec(1.0f, 1.0f, 1.0f);
	Light_0.SetAtt(1.0f, 0.3f, 0.1f);

	// Light1
	Light_1.SetCat(0);	// directional light
	Light_1.SetDirection(0.0f, -1.0f, 0.0f);
	Light_1.SetAmb(0.1f, 0.1f, 0.1f);
	Light_1.SetDiff(0.3f, 0.3f, 0.3f);
	Light_1.SetSpec(0.2f, 0.2f, 0.2f);

	// Object0
	Object_0.SetCat(0);	// sphere
	Object_0.SetCent(-0.4f, 0.0f, -2.0f);
	Object_0.SetRad(0.5f);
	Object_0.SetAmb(0.1f, 0.1f, 0.1f);
	Object_0.SetDiff(0.3f, 0.3f, 0.3f);
	Object_0.SetSpec(0.2f, 0.2f, 0.2f);
	Object_0.SetShn(5);
	Object_0.SetRef(1.0f, 0.1f, 0.8f);

	// Object1
	Object_1.SetCat(1);	// plane
	Object_1.SetCoef(0.0f, 1.0f, 0.0f, 0.5f);
	Object_1.SetAmb(0.15f, 0.15f, 0.15f);
	Object_1.SetDiff(0.2f, 0.2f, 0.5f);
	Object_1.SetSpec(0.7f, 0.1f, 0.4f);
	Object_1.SetShn(7);
	Object_1.SetRef(0.6f, 0.4f, 0.2f);

	// Object2
	Object_2.SetCat(0);	// sphere
	Object_2.SetCent(0.2f, 5.0f, -6.0f);
	Object_2.SetRad(0.8f);
	Object_2.SetAmb(0.3f, 0.4f, 0.15f);
	Object_2.SetDiff(0.5f, 0.3f, 0.2f);
	Object_2.SetSpec(0.5f, 0.5f, 0.5f);
	Object_2.SetShn(2);
	Object_2.SetRef(0.2f, 0.5f, 0.3f);

	////////////////////////////////////////////

	// 이미지의 크기
	int width = 512;
	int height = 512;		
	unsigned char* image = new unsigned char [width*height*3];

	// 파일 저장
	FILE* fp;
	fp = fopen("result.ppm", "wb");
	if(fp == NULL){
		fprintf(stderr, "파일 생성에 실패하였습니다.\n");
		return 0;
	}
	fprintf(fp, "P6\n%d %d\n255\n", width, height);

	// Ray
	Vector u;
	u = (look.Cross(up)).Normalise();
	Vector v;
	v = (look.Cross(u)).Normalise();
	Vector o;
	o = look.Normalise() * (width/(2*tan(fovx/2 * PI / 180))) - u*(width/2.0f) - v*(height/2.0f);	

	// Raytrace()
	// For each pixel x, y
	for(int y = 0; y < height; y++){
		for(int x = 0; x < width; x++){
			Vector d = d.CalD(u, v, o, x, y);
			d = d.Normalise();
			Vector RGB = Trace(d, num_object);
			
			image[3*width*y + 3*x + 0] = (unsigned char)(RGB.GetX()*255);
			image[3*width*y + 3*x + 1] = (unsigned char)(RGB.GetY()*255);
			image[3*width*y + 3*x + 2] = (unsigned char)(RGB.GetZ()*255);
			if((RGB.GetX()*255) > 255){
				image[3*width*y + 3*x + 0] = 0xff;
			}
			if((RGB.GetY()*255) > 255){
				image[3*width*y + 3*x + 1] = 0xff;
			}
			if((RGB.GetZ()*255) > 255){
				image[3*width*y + 3*x + 2] = 0xff;
			}
		}
	}
	fwrite(image, sizeof(char), width*height*3, fp);
	fclose(fp);

	return 0;
}

// Trace(ray)
Vector Trace(Vector _ray, int _recursNumber)
{
	ObjInfo object_point = closest_intersection(_ray, eye);
	ObjInfo none;
	Vector Background_Color(0.7f, 0.7f, 0.7f);
	Vector black(0.0f, 0.0f, 0.0f);

	if(_recursNumber > 0){
		if(object_point.GetPoint() != none.GetPoint()){
			return Shade(object_point, _ray, _recursNumber);
		}else{
			return Background_Color;
		}
	}
	else{
		return black;
	}
}

// Shade(point, ray)
Vector Shade(ObjInfo _object_point, Vector _ray, int _recursNumber)
{
	Vector total(0.0f, 0.0f, 0.0f);	// black;
	// for each light source
	// source : Light_0
 	if(!Shadow_Ray(_object_point, _ray, Light_0)){
 		total = total + Local_Illumination(_object_point, _ray, Light_0);
 	}
   	// source : Light_1
   	if(!Shadow_Ray(_object_point, _ray, Light_1)){
   		total = total + Local_Illumination(_object_point, _ray, Light_1);
   	}
  	// 반사 및 굴절
   	if(_object_point.GetMtrl().GetRefl() != 0){ // material is specularly reflective
   	 	total = total + Trace(reflected_ray(_object_point, _ray), _recursNumber-1) * _object_point.GetMtrl().GetRefl();
   	}
 	if(_object_point.GetMtrl().GetRefr() != 0){ // material is specularly transmissive
 		total = total + Trace(refracted_ray(_object_point, _ray), _recursNumber-1) * _object_point.GetMtrl().GetRefr();
 	}
	return total;
}

// closest_intersection(ray)
ObjInfo closest_intersection(Vector _ray, Vector _eye)
{
	// Object_0
	Vector P;
	Vector s = Object_0.GetCent();
	Vector c = s - _eye;
	float t_c, t_u, t;

	t_c = c.Dot(_ray);
	t_u = (Object_0.GetRad()*Object_0.GetRad()) - (c.Dot(c) - t_c*t_c);

	// Object_0의 intersection Check
	if(c.Norm() > Object_0.GetRad()){	// ray origin outside
		if(t_c < 0 || t_u < 0){	
			P.SetVector(9999.0f, 9999.0f, 9999.0f);		// miss
		}
		else{
			t = t_c - sqrt(t_u);
			P = _eye + _ray*t;
		}				
	}
	else{
		t = t_c + sqrt(t_u);
		P = _eye + _ray*t;
	}

	// Object_1
	Vector P1;
	Vector n = Object_1.GetPlaneNorm();
	n = n.Normalise();
	float t_n = n.Dot(_ray);
	float t1;

	if(t_n >= 0){
		n = n * -1;
	}
	// Object_1의 intersection Check
	if(t_n == 0){
		P1.SetVector(9999.0f, 9999.0f, 9999.0f);	// miss
	}
	else{
		float t_0 = -(n.Dot(_eye) + Object_1.GetD());
		t1 = t_0/t_n;
		if(t1 < 0){
			P1.SetVector(9999.0f, 9999.0f, 9999.0f);	// miss
		}
		else{
			P1 = _eye + _ray*t1;
		}
	}

	// Object_2
	Vector P2;
	Vector s2 = Object_2.GetCent();
	Vector c2 = s2 - _eye;
	float t_c2, t_u2, t2;

	t_c2 = c2.Dot(_ray);
	t_u2 = (Object_2.GetRad()*Object_2.GetRad()) - (c2.Dot(c2) - t_c2*t_c2);

	// Object_2의 intersection Check
	if(c2.Norm() > Object_2.GetRad()){	// ray origin outside
		if(t_c2 < 0 || t_u2 < 0){
			P2.SetVector(9999.0f, 9999.0f, 9999.0f);	// miss
		}
		else{
			t2 = t_c2 - sqrt(t_u2);
			P2 = _eye + _ray*t2;
		}				
	}
	else{
		t2 = t_c2 + sqrt(t_u2);
		P2 = _eye + _ray*t2;
	}		

	// 정보(근접점, 노멀벡터, 물체) 저장
	ObjInfo info, none;
	Vector far(9999.0f, 9999.0f, 9999.0f);
	int close = pMin(P.Norm(), P1.Norm(), P2.Norm());
	if(close == 1){
 		info.SetInfo(P, (P - Object_0.GetCent()).Normalise(), Object_0);
 	}
 	if(close == 2){
 		info.SetInfo(P1, (Object_1.GetPlaneNorm()).Normalise(), Object_1);
 	}
 	if(close == 3){
	 	info.SetInfo(P2, (P2 - Object_2.GetCent()).Normalise(), Object_2);
 	}
	
	// 만나는 점이 있으면 return info, 그렇지 않으면 return none
	if(info.GetPoint() != far && info.GetPoint() != none.GetPoint())
		return info;
	else
		return none;
}

bool Shadow_Ray(ObjInfo _object_point, Vector _ray, Light _source)
{
	if(_source.GetCat() == 1){		// 점광원
		Vector shadow_direction = _object_point.GetPoint() - _source.GetPosition();
		shadow_direction = shadow_direction.Normalise();
		ObjInfo shadow_point = closest_intersection(shadow_direction, _source.GetPosition());

		// 광원에서 물체로 ray를 쏴서 만나는 점과, eye에서 물체로 ray를 쏴서 만나는 점이 같으면 그림자 효과 없음.
		if(shadow_point.GetPoint() == _object_point.GetPoint()){
			return false;
		}
		else{
			return true;
		}
	}
	else if(_source.GetCat() == 0){	// 방향성 광원
		Vector far(-10.0f, -10.0f, -10.0f);
		Vector light_position = _source.GetDirection().Mult(far);
		Vector shadow_direction2 = _object_point.GetPoint() - light_position;
		shadow_direction2 = shadow_direction2.Normalise();
		ObjInfo shadow_point2 = closest_intersection(shadow_direction2, light_position);

		// 광원에서 물체로 ray를 쏴서 만나는 점과, eye에서 물체로 ray를 쏴서 만나는 점이 같으면 그림자 효과 없음.
		if(shadow_point2.GetPoint() == _object_point.GetPoint()){
			return false;
		}
		else{
			return true;
		}
	}
	else{
		return true;	// 색상 적용 안함.
	}
}

Vector Local_Illumination(ObjInfo _object_point, Vector _ray, Light _source)
{
	Vector Local_color;
	float d = (_source.GetPosition() - _object_point.GetPoint()).Norm();
	Vector D(1.0f, d, d*d);
	Vector N, L, V, H;
	N = _object_point.GetNormal();
	N = N.Normalise();
	L = _source.GetPosition() - _object_point.GetPoint();
	L = L.Normalise();
	V = _ray * -1;
	V = V.Normalise();
	H = (L+V).Normalise();
	
	if(_source.GetCat() == 1){
		Local_color = _object_point.GetMtrl().GetAmb().Mult(_source.GetAmb())	// K_a * I_a
					+ ((_object_point.GetMtrl().GetDiff().Mult(_source.GetDiff())) * MAX(0, N.Dot(L))	// k_d*I_d*(NL)
					+ (_object_point.GetMtrl().GetSpec().Mult(_source.GetSpec())) * specN(MAX(0, N.Dot(H)), _object_point.GetMtrl().GetShn()))	// k_s*I_s*(NH)^n
					* (1/(_source.GetAtt()).Dot(D));	// 1/(a+bd+cd^2)
	}
	else if(_source.GetCat() == 0){
		Local_color = _object_point.GetMtrl().GetAmb().Mult(_source.GetAmb())	// K_a * I_a
					+ ((_object_point.GetMtrl().GetDiff().Mult(_source.GetDiff())) * MAX(0, N.Dot(L))	// k_d*I_d*(NL)
					+ (_object_point.GetMtrl().GetSpec().Mult(_source.GetSpec())) * specN(MAX(0, N.Dot(H)), _object_point.GetMtrl().GetShn()));	// k_s*I_s*(NH)^n
	}

	return Local_color;
}

Vector reflected_ray(ObjInfo _object_point, Vector _ray)
{
	Vector refl_ray;
	Vector N = _object_point.GetNormal();
	Vector I = _ray * -1;
	N = N.Normalise();
	I = I.Normalise();
	refl_ray = N * N.Dot(I) * 2 - I;
	refl_ray = refl_ray.Normalise();
	return refl_ray;
}

Vector refracted_ray(ObjInfo _object_point, Vector _ray)
{
	Vector refr_ray;
	Vector N = _object_point.GetNormal();
	Vector I = _ray * -1;
	N = N.Normalise();
	I = I.Normalise();
	float n = 1/_object_point.GetMtrl().GetIdxr();
	float _cos = n*(1 - 1/(n*n))*sqrt(1 - N.Dot(I)*N.Dot(I));
	refr_ray = (-1/n)*I - (_cos - (1/n)*N.Dot(I))*N;
	refr_ray = refr_ray.Normalise();
	return refr_ray;
}

int pMin(float a, float b, float c)
{
	if(a <= b && a <= c){
		return 1;
	}
	else if(b <= a && b <= c){
		return 2;
	}
	else if(c <= a && c <= b){
		return 3;
	}
	else return 0;
}

float specN(float x, int n)
{
	float res = 1.0f;
	for(int i = 0; i < n; i++)
	{
		res = res * x;
	}
	return res;	
}
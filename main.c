#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <netdb.h>
#include <sys/socket.h>
#include "json.h"

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#define MAX 80
#define PORT 2000
#define SA struct sockaddr

//dirty hacks for higher than implementation
double coor_x[100][26]={[0 ... 99][0 ... 25] = 16384}, coor_y[100][26]={[0 ... 99][0 ... 25] = 16384};
double coor_cm[100][26]={[0 ... 99][0 ... 25] = 0};
int squat[100]={[0 ... 99] = 0};
int station[100]={[0 ... 99] = 0};
int station_rest[100]={[0 ... 99] = 0};
int station_working[100]={[0 ... 99] = 0};
int station_hand[100]={[0 ... 99] = 0};
int sit_working[100]={[0 ... 99] = 0};
int sit_rest[100]={[0 ... 99] = 0};
int sit_hand[100]={[0 ... 99] = 0};
int sit[100]={[0 ... 99] = 0};
int rest[100]={[0 ... 99] = 0};
int working[100]={[0 ... 99] = 0};
int fall[100]={[0 ... 99] = 0};
int hand[100]={[0 ... 99] = 0};
int lefthand[100]={[0 ... 99] = 0},righthand[100]={[0 ... 99] = 0}, hand_int[100]={[0 ... 99] = 0};
//implement if needed
//double coor_x_old[100][4]={0}, coor_y_old[100][4]={0};
int num = -1;
int num_old = 0;
/*
int a=0;
int b=0;
int c=0;
int d=0;
int e=0;
int f=0;
*/

char defaultfilename[16] = "_keypoints.json";
char prependfilename[44] = "/home/ele/20200717/openpose_combined/json/";
char filenamestring[13] = "000000000000";
char filename[71] = "/home/ele/20200717/openpose_combined/json/000000000000_keypoints.json";
long long int file_i = 0;
time_t old_result = 0;
time_t result;
/*
gcc main.c json.c -lm
 */
static void print_depth_shift(int depth)
{
        int j;
        for (j=0; j < depth; j++) {
		//printf(" ");
        }
}
static void func();
static void output();

int sockfd, connfd;
struct sockaddr_in servaddr, cli;
char* body_parts(int x);
static void coorx(json_value* value, int x, int y);
static void coory(json_value* value, int x, int y);
static void coorcm(json_value* value, int x, int y);
static void spit(json_value* value, int x, int y);
static void process_value(json_value* value, int depth, int x);

static void process_object(json_value* value, int depth)
{
        int length, x;
        if (value == NULL) {
                return;
        }
        length = value->u.object.length;
        for (x = 0; x < length; x++) {
                print_depth_shift(depth);
                //printf("object[%d].name = %s\n", x, value->u.object.values[x].name);
                process_value(value->u.object.values[x].value, depth+1, x);
        }
}

static void process_array(json_value* value, int depth)
{
        int length, x;
        if (value == NULL) {
                return;
        }
        length = value->u.array.length;
        //printf("array: %d\n", depth);
        for (x = 0; x < length; x++) {
                process_value(value->u.array.values[x], depth, x);
        }
}

static void process_value(json_value* value, int depth, int x)
{
        int j;
	char a[100];
        if (value == NULL) {
                return;
        }
        if (value->type != json_object) {
                print_depth_shift(depth);
        }
        switch (value->type) {
                case json_none:
//                printf("none\n");
                        break;
                case json_object:
                        process_object(value, depth+1);
                        break;
                case json_array:
                        process_array(value, depth+1);
                        break;
                case json_integer:
//                        printf("int: %10" PRId64 "\n", value->u.integer);
                        break;
                case json_double:
                        //printf("double: %f\n", value->u.dbl);
					if(x==0)num++;
					//printf("%d",x);
					if(x/3==0 || x/3==1 || x/3==2 || x/3==3 || x/3==4 || x/3==5 || x/3==6 || x/3==7 || x/3==8 || x/3==9 || x/3==10 || x/3==11 || x/3==12 || x/3==13 || x/3==14 || x/3==15|| x/3==16 || x/3==17 || x/3==18 || x/3==19 || x/3==20 || x/3==21 || x/3==22 || x/3==23 || x/3==24 || x/3==25){
						switch(x/3){
							case 0:spit(value, x, 0);break;
							case 1:spit(value, x, 1);break;
							case 2:spit(value, x, 2);break;
							case 3:spit(value, x, 3);break;
							case 4:spit(value, x, 4);break;
							case 5:spit(value, x, 5);break;
							case 6:spit(value, x, 6);break;
							case 7:spit(value, x, 7);break;
							case 8:spit(value, x, 8);break;
							case 9:spit(value, x, 9);break;
							case 10:spit(value, x, 10);break;
							case 11:spit(value, x, 11);break;
							case 12:spit(value, x, 12);break;
							case 13:spit(value, x, 13);break;
							case 14:spit(value, x, 14);break;
							case 15:spit(value, x, 15);break;
							case 16:spit(value, x, 16);break;
							case 17:spit(value, x, 17);break;
							case 18:spit(value, x, 18);break;
							case 19:spit(value, x, 19);break;
							case 20:spit(value, x, 20);break;
							case 21:spit(value, x, 21);break;
							case 22:spit(value, x, 22);break;
							case 23:spit(value, x, 23);break;
							case 24:spit(value, x, 24);break;
							case 25:spit(value, x, 25);break;
							default:break;
						}
					}
					//if(num > num_old){
						//printf("hooman[%d], y2=%f, y3=%f, y5=%f, y6=%f\n",num,coor_y[num][0],coor_y[num][1],coor_y[num][2],coor_y[num][3]);
						//num_old++;
					//}
					break;
                case json_string:
//                        printf("string: %s\n", value->u.string.ptr);
                        break;
                case json_boolean:
//                        printf("bool: %d\n", value->u.boolean);
                        break;
        }
}
char* body_parts(int x){
	switch(x/3){
		case 0:return "Nose";
		case 1:return "Neck";
		case 2:return "RShoulder";
		case 3:return "RElbow";
		case 4:return "RWrist";
		case 5:return "LShoulder";
		case 6:return "LElbow";
		case 7:return "LWrist";
		case 8:return "MidHip";
		case 9:return "RHip";
		case 10:return "RKnee";
		case 11:return "RAnkle";
		case 12:return "LHip";
		case 13:return "LKnee";
		case 14:return "LAnkle";
		case 15:return "REye";
		case 16:return "LEye";
		case 17:return "REar";
		case 18:return "LEar";
		case 19:return "LBigToe";
		case 20:return "LSmallToe";
		case 21:return "LHeel";
		case 22:return "RBigToe";
		case 23:return "RSmallToe";
		case 24:return "RHeel";
		case 25:return "Background";
		default:return "Unimplemented";
	}
}
static void coorx(json_value* value, int x, int y){
	char* part_name=body_parts(x);
	//doing YOLO
	//if(coor_x[num][y]!=0)coor_x_old[num][y]=coor_x[num][y];
	coor_x[num][y]=value->u.dbl;
	//printf("x: %d, coor_x[%d][%d] = %f\n",x/3,num,y,coor_x[num][y]);
	///printf("Person[%d] %s xcoor=%f, x=%d",num,part_name,coor_x[num][y],x);
}
static void coory(json_value* value, int x, int y){
	coor_y[num][y]=value->u.dbl;
/*
  //運算
	int sittest = 0;
	int sittest1 = 0;
	int stationtest = 0;
	int Rstation = 0;
	int Lstation = 0;
	int Rresttest = 0;
	int Lresttest = 0;
  //坐姿
  	if(coor_y[num][8]==16384 || coor_y[num][1]==16384 || ((coor_y[num][9]==16384 || coor_y[num][10]==16384) && (coor_y[num][12]==16384 || coor_y[num][13]==16384)) || coor_x[num][8]==16384 || coor_x[num][1]==16384 || ((coor_x[num][9]==16384 || coor_x[num][10]==16384) && (coor_x[num][12]==16384 || coor_x[num][13]==16384))){
		//TODO
	}else{
  	double Rslope = ((coor_y[num][9]-coor_y[num][10])/(coor_x[num][9]-coor_x[num][10]));
  	double Lslope = ((coor_y[num][12]-coor_y[num][13])/(coor_x[num][12]-coor_x[num][13]));
  	double xaxis = pow(coor_x[num][8]-coor_x[num][1],2);
	double yaxis = pow(coor_y[num][8]-coor_y[num][1],2);
	double distance = pow(xaxis+yaxis,0.5);
	if((Rslope >= -1 && Rslope <= 1)||(Lslope >= -1 && Lslope <= 1))sittest=1;
	if(fabs(coor_x[num][8]-coor_x[num][1])<=(distance/2))sittest1 = 1;
	if(fall[num]==0&&sittest==1&&sittest1==1)sit[num]=1;
}
  //站姿
	if(coor_y[num][8]==16384 || coor_y[num][1]==16384 || ((coor_y[num][9]==16384 || coor_y[num][10]==16384) && (coor_y[num][12]==16384 || coor_y[num][13]==16384)) || coor_x[num][8]==16384 || coor_x[num][1]==16384 || ((coor_x[num][9]==16384 || coor_x[num][10]==16384) && (coor_x[num][12]==16384 || coor_x[num][13]==16384))){
		//TODO
	}else{
	double xaxis1 = pow(coor_x[num][8]-coor_x[num][1],2);
	double yaxis1 = pow(coor_y[num][8]-coor_y[num][1],2);
	double distance1 = pow(xaxis1+yaxis1,0.5);
	double Rslope_xaxis = pow(coor_x[num][10]-coor_x[num][9],2);
	double Rslope_yaxis = pow(coor_y[num][10]-coor_y[num][9],2);
	double Lslope_xaxis = pow(coor_x[num][13]-coor_x[num][12],2);
	double Lslope_yaxis = pow(coor_y[num][13]-coor_y[num][12],2);
	double Rslope_distance = pow(Rslope_xaxis+Rslope_yaxis,0.5);
	double Lslope_distance = pow(Lslope_xaxis+Lslope_yaxis,0.5);
	if(fabs(coor_x[num][8]-coor_x[num][1])<=(distance1/2))stationtest = 1;
	if(fabs(coor_x[num][10]-coor_x[num][9])<=(Rslope_distance/2))Rstation = 1;
	if(fabs(coor_x[num][13]-coor_x[num][12])<=(Lslope_distance/2))Lstation = 1;
	if(sittest==0 &&fall[num]==0 && stationtest==1 && (Rstation==1 || Lstation==1 ))station[num]=1;
	}
  //舉半手
	if(coor_y[num][4]==16384 || coor_y[num][3]==16384 || coor_y[num][2]==16384){
		//TODO
	}else{
		if(coor_y[num][3]-coor_y[num][4]>=0.5 && coor_y[num][3]-coor_y[num][2]>=0.5)working[num]=1;
	}
  //蹲姿
//	printf("dbg = %d %f %f %f %f\n", squat[num],coor_y[num][7],coor_y[num][6],coor_y[num][10],coor_y[num][9]);
//	if(coor_x[num][9]==16384 && coor_x[num][8]==16384 && coor_x[num][12] && coor_x[num][11] &&coor_y[num][9]==16384 && coor_y[num][8]==16384 && coor_y[num][12]==16384 && coor_y[num][11]==16384){
//	}else{
//		if(coor_y[num][8] > coor_y[num][9]&&coor_y[num][11] > coor_y[num][12])squat[num]=1;
//	}
  //舉手
	if((coor_y[num][2]==16384 || coor_y[num][3]==16384) && (coor_y[num][5]==16384 || coor_y[num][6]==16384)){
		//TODO
	}else{
		if(coor_y[num][2]-coor_y[num][3]>0.5)righthand[num]=1;
		if(coor_y[num][5]-coor_y[num][6]>0.5)lefthand[num]=1;
		if(lefthand[num]==1 || righthand[num]==1){
			hand[num]=1;
		}else{
  //休息
		
			if((coor_y[num][4]==16384 || coor_y[num][3]==16384 || coor_y[num][2]==16384) && (coor_y[num][7]==16384 || coor_y[num][6]==16384 || coor_y[num][5]==16384)){
			//TODO
			}else{
				if(lefthand[num]==0&&coor_y[num][4]-coor_y[num][3]>=0.5 && coor_y[num][3]-coor_y[num][2]>=0.5)Rresttest = 1;
				if(righthand[num]==0&& coor_y[num][7]-coor_y[num][6]>=0.5 && coor_y[num][6]-coor_y[num][5]>=0.5)Lresttest = 1;
				if(working[num]==0 && hand[num]==0 && (Rresttest==1 && Lresttest==1))rest[num]=1;
			}
		}
	}
  //倒下
	if(coor_x[num][1]==16384 || coor_x[num][8]==16384 || coor_y[num][1]==16384 || coor_y[num][8]==16384){
		//skip
		//printf("skip!\n");
	}else{
		double slope = ((coor_y[num][8]-coor_y[num][1])/(coor_x[num][8]-coor_x[num][1]));
		//printf("abcd = %f\n", slope);
		//char* part_name=body_parts(x);
		//YOLO
		//if(coor_y[num][y]!=0)coor_y_old[num][y]=coor_y[num][y];
		//printf("==DEBUG== Human[%d], x1=%f, y1=%f, x8=%f, y8=%f",num,coor_x[num][0],coor_y[num][0],coor_x[num][1],coor_y[num][1]);
		//printf(" x1-x8= %f, y1-y8=%f, Slope = %f\n",(coor_x[num][1]-coor_x[num][0]),(coor_y[num][1]-coor_y[num][0]), slope);

		if(slope >= -1 && slope <= 1)fall[num]=1;
		//if(coor_y[num][2]-coor_y[num][3]>0.5)lefthand[num]=1;
		//printf("x: %d, coor_x[%d][%d] = %f\n",x/3,num,y,coor_y[num][y]);
		//printf(", ycoor=%f, y=%d\n",coor_y[num][y],y),y,coor_y[num][y]);
}
  //坐姿有問題
	if(sit[num]==1 && hand[num]==1)sit_hand[num]=1;
  //坐姿工作中
	if(sit[num]==1 && working[num]==1 )sit_working[num]=1;
  //坐姿休息
	if(sit[num]==1 && rest[num]==1 )sit_rest[num]=1;
  //站姿有問題
	if(station[num]==1 && hand[num]==1)station_hand[num]=1;
  //站姿工作中
	if(station[num]==1 && working[num]==1)station_working[num]=1;
  //站姿休息
	if(station[num]==1 && rest[num]==1)station_rest[num]=1;
	//printf("dbg = %d %d %d %d \n", rest[num],righthand[num],lefthand[num],resttest);
*/
}

static void coorcm(json_value* value, int x, int y){
	coor_cm[num][y]=value->u.dbl;

//運算
	int sittest = 0;
	int sittest1 = 0;
	int stationtest = 0;
	int Rstation = 0;
	int Lstation = 0;
	int Rresttest = 0;
	int Lresttest = 0;
	double v = 0.5;
  //坐姿
  	if(coor_y[num][8]==16384 || coor_y[num][1]==16384 || ((coor_y[num][9]==16384 || coor_y[num][10]==16384) && (coor_y[num][12]==16384 || coor_y[num][13]==16384)) || coor_x[num][8]==16384 || coor_x[num][1]==16384 || ((coor_x[num][9]==16384 || coor_x[num][10]==16384) && (coor_x[num][12]==16384 || coor_x[num][13]==16384))){
		//TODO
	}else{
  	double Rslope = ((coor_y[num][9]-coor_y[num][10])/(coor_x[num][9]-coor_x[num][10]));
  	double Lslope = ((coor_y[num][12]-coor_y[num][13])/(coor_x[num][12]-coor_x[num][13]));
  	double xaxis = pow(coor_x[num][8]-coor_x[num][1],2);
	double yaxis = pow(coor_y[num][8]-coor_y[num][1],2);
	double distance = pow(xaxis+yaxis,0.5);
	if((Rslope >= -1 && Rslope <= 1)||(Lslope >= -1 && Lslope <= 1))sittest=1;
	if(fabs(coor_x[num][8]-coor_x[num][1])<=(distance/2))sittest1 = 1;
	if(fall[num]==0&&sittest==1&&sittest1==1)sit[num]=1;
}
  //站姿
	if(coor_y[num][8]==16384 || coor_y[num][1]==16384 || ((coor_y[num][9]==16384 || coor_y[num][10]==16384) && (coor_y[num][12]==16384 || coor_y[num][13]==16384)) || coor_x[num][8]==16384 || coor_x[num][1]==16384 || ((coor_x[num][9]==16384 || coor_x[num][10]==16384) && (coor_x[num][12]==16384 || coor_x[num][13]==16384))){
		//TODO
	}else{
	double xaxis1 = pow(coor_x[num][8]-coor_x[num][1],2);
	double yaxis1 = pow(coor_y[num][8]-coor_y[num][1],2);
	double distance1 = pow(xaxis1+yaxis1,0.5);
	double Rslope_xaxis = pow(coor_x[num][10]-coor_x[num][9],2);
	double Rslope_yaxis = pow(coor_y[num][10]-coor_y[num][9],2);
	double Lslope_xaxis = pow(coor_x[num][13]-coor_x[num][12],2);
	double Lslope_yaxis = pow(coor_y[num][13]-coor_y[num][12],2);
	double Rslope_distance = pow(Rslope_xaxis+Rslope_yaxis,0.5);
	double Lslope_distance = pow(Lslope_xaxis+Lslope_yaxis,0.5);
	if(fabs(coor_x[num][8]-coor_x[num][1])<=(distance1/2))stationtest = 1;
	if(fabs(coor_x[num][10]-coor_x[num][9])<=(Rslope_distance/2))Rstation = 1;
	if(fabs(coor_x[num][13]-coor_x[num][12])<=(Lslope_distance/2))Lstation = 1;
	if(sittest==0 &&fall[num]==0 && stationtest==1 && (Rstation==1 || Lstation==1 ))station[num]=1;
	}
  //舉半手
	if(coor_y[num][4]==16384 || coor_y[num][3]==16384 || coor_y[num][2]==16384){
		//TODO
	}else{
		if(coor_y[num][3]-coor_y[num][4]>=0.5 && coor_y[num][3]-coor_y[num][2]>=0.5)working[num]=1;
	}
  //蹲姿
//	printf("dbg = %d %f %f %f %f\n", squat[num],coor_y[num][7],coor_y[num][6],coor_y[num][10],coor_y[num][9]);
//	if(coor_x[num][9]==16384 && coor_x[num][8]==16384 && coor_x[num][12] && coor_x[num][11] &&coor_y[num][9]==16384 && coor_y[num][8]==16384 && coor_y[num][12]==16384 && coor_y[num][11]==16384){
//	}else{
//		if(coor_y[num][8] > coor_y[num][9]&&coor_y[num][11] > coor_y[num][12])squat[num]=1;
//	}
  //舉手
	if((coor_y[num][2]==16384 || coor_y[num][3]==16384) && (coor_y[num][5]==16384 || coor_y[num][6]==16384)){
		//TODO
	}else{
		if(coor_y[num][2]-coor_y[num][3]>0.5)righthand[num]=1;
		if(coor_y[num][5]-coor_y[num][6]>0.5)lefthand[num]=1;
		if(lefthand[num]==1 || righthand[num]==1){
			hand[num]=1;
		}else{
  //休息
		
			if((coor_y[num][4]==16384 || coor_y[num][3]==16384 || coor_y[num][2]==16384) && (coor_y[num][7]==16384 || coor_y[num][6]==16384 || coor_y[num][5]==16384)){
			//TODO
			}else{
				if(lefthand[num]==0&&coor_y[num][4]-coor_y[num][3]>=0.5 && coor_y[num][3]-coor_y[num][2]>=0.5)Rresttest = 1;
				if(righthand[num]==0&& coor_y[num][7]-coor_y[num][6]>=0.5 && coor_y[num][6]-coor_y[num][5]>=0.5)Lresttest = 1;
				if(working[num]==0 && hand[num]==0 && (Rresttest==1 && Lresttest==1))rest[num]=1;
			}
		}
	}
  //倒下
	if(coor_x[num][1]==16384 || coor_x[num][8]==16384 || coor_y[num][1]==16384 || coor_y[num][8]==16384){
		//skip
		//printf("skip!\n");
	}else{
		double slope = ((coor_y[num][8]-coor_y[num][1])/(coor_x[num][8]-coor_x[num][1]));
		//printf("abcd = %f\n", slope);
		//char* part_name=body_parts(x);
		//YOLO
		//if(coor_y[num][y]!=0)coor_y_old[num][y]=coor_y[num][y];
		//printf("==DEBUG== Human[%d], x1=%f, y1=%f, x8=%f, y8=%f",num,coor_x[num][0],coor_y[num][0],coor_x[num][1],coor_y[num][1]);
		//printf(" x1-x8= %f, y1-y8=%f, Slope = %f\n",(coor_x[num][1]-coor_x[num][0]),(coor_y[num][1]-coor_y[num][0]), slope);

		if(slope >= -1 && slope <= 1)fall[num]=1;
		//if(coor_y[num][2]-coor_y[num][3]>0.5)lefthand[num]=1;
		//printf("x: %d, coor_x[%d][%d] = %f\n",x/3,num,y,coor_y[num][y]);
		//printf(", ycoor=%f, y=%d\n",coor_y[num][y],y),y,coor_y[num][y]);
}
  //坐姿有問題
	if(sit[num]==1 && hand[num]==1)sit_hand[num]=1;
  //坐姿工作中
	if(sit[num]==1 && working[num]==1 )sit_working[num]=1;
  //坐姿休息
	if(sit[num]==1 && rest[num]==1 )sit_rest[num]=1;
  //站姿有問題
	if(station[num]==1 && hand[num]==1)station_hand[num]=1;
  //站姿工作中
	if(station[num]==1 && working[num]==1)station_working[num]=1;
  //站姿休息
	if(station[num]==1 && rest[num]==1)station_rest[num]=1;
	//printf("dbg = %d %d %d %d \n", rest[num],righthand[num],lefthand[num],resttest);


/*
	if(coor_x[num][0]==16384 || coor_y[num][0]==16384 || coor_cm[num][0]==0){
	}else{
		printf("J %d x=%f %f %f \n",num,coor_x[num][0],coor_y[num][0],coor_cm[num][0]);
		}
	if(coor_x[num][1]==16384 || coor_y[num][1]==16384 || coor_cm[num][1]==0){
	}else{
		printf("J %d x=%f %f %f \n",num,coor_x[num][1],coor_y[num][1],coor_cm[num][1]);
		}
	if(coor_x[num][2]==16384 || coor_y[num][2]==16384 || coor_cm[num][2]==0){
	}else{
		printf("J %d x=%f %f %f \n",num,coor_x[num][2],coor_y[num][2],coor_cm[num][2]);
		}
	if(coor_x[num][3]==16384 || coor_y[num][3]==16384 || coor_cm[num][3]==0){
	}else{
		printf("J %d x=%f %f %f \n",num,coor_x[num][3],coor_y[num][3],coor_cm[num][3]);
		}
	if(coor_x[num][4]==16384 || coor_y[num][4]==16384 || coor_cm[num][4]==0){
	}else{
		printf("J %d x=%f %f %f \n",num,coor_x[num][4],coor_y[num][4],coor_cm[num][4]);
		}
	if(coor_x[num][5]==16384 || coor_y[num][5]==16384 || coor_cm[num][5]==0){
	}else{
		printf("J %d x=%f %f %f \n",num,coor_x[num][5],coor_y[num][5],coor_cm[num][5]);
		}
	if(coor_x[num][6]==16384 || coor_y[num][6]==16384 || coor_cm[num][6]==0){
	}else{
		printf("J %d x=%f %f %f \n",num,coor_x[num][6],coor_y[num][6],coor_cm[num][6]);
		}
	if(coor_x[num][7]==16384 || coor_y[num][7]==16384 || coor_cm[num][7]==0){
	}else{
		printf("J %d x=%f %f %f \n",num,coor_x[num][7],coor_y[num][7],coor_cm[num][7]);
		}
	if(coor_x[num][8]==16384 || coor_y[num][8]==16384 || coor_cm[num][8]==0){
	}else{
		printf("J %d x=%f %f %f \n",num,coor_x[num][8],coor_y[num][8],coor_cm[num][8]);
		}
	if(coor_x[num][9]==16384 || coor_y[num][9]==16384 || coor_cm[num][9]==0){
	}else{
		printf("J %d x=%f %f %f \n",num,coor_x[num][9],coor_y[num][9],coor_cm[num][9]);
		}
	if(coor_x[num][10]==16384 || coor_y[num][10]==16384 || coor_cm[num][10]==0){
	}else{
		printf("J %d x=%f %f %f \n",num,coor_x[num][10],coor_y[num][10],coor_cm[num][10]);
		}
	if(coor_x[num][11]==16384 || coor_y[num][11]==16384 || coor_cm[num][11]==0){
	}else{
		printf("J %d x=%f %f %f \n",num,coor_x[num][11],coor_y[num][11],coor_cm[num][11]);
		}
	if(coor_x[num][12]==16384 || coor_y[num][12]==16384 || coor_cm[num][12]==0){
	}else{
		printf("J %d x=%f %f %f \n",num,coor_x[num][12],coor_y[num][12],coor_cm[num][12]);
		}
	if(coor_x[num][13]==16384 || coor_y[num][13]==16384 || coor_cm[num][13]==0){
	}else{
		printf("J %d x=%f %f %f \n",num,coor_x[num][13],coor_y[num][13],coor_cm[num][13]);
		}
	if(coor_x[num][14]==16384 || coor_y[num][14]==16384 || coor_cm[num][14]==0){
	}else{
		printf("J %d x=%f %f %f \n",num,coor_x[num][14],coor_y[num][14],coor_cm[num][14]);
		}
	if(coor_x[num][15]==16384 || coor_y[num][15]==16384 || coor_cm[num][15]==0){
	}else{
		printf("J %d x=%f %f %f \n",num,coor_x[num][15],coor_y[num][15],coor_cm[num][15]);
		}
	if(coor_x[num][16]==16384 || coor_y[num][16]==16384 || coor_cm[num][16]==0){
	}else{
		printf("J %d x=%f %f %f \n",num,coor_x[num][16],coor_y[num][16],coor_cm[num][16]);
		}
	if(coor_x[num][17]==16384 || coor_y[num][17]==16384 || coor_cm[num][17]==0){
	}else{
		printf("J %d x=%f %f %f \n",num,coor_x[num][17],coor_y[num][17],coor_cm[num][17]);
		}
	if(coor_x[num][18]==16384 || coor_y[num][18]==16384 || coor_cm[num][18]==0){
	}else{
		printf("J %d x=%f %f %f \n",num,coor_x[num][18],coor_y[num][18],coor_cm[num][18]);
		}
	if(coor_x[num][19]==16384 || coor_y[num][19]==16384 || coor_cm[num][19]==0){
	}else{
		printf("J %d x=%f %f %f \n",num,coor_x[num][19],coor_y[num][19],coor_cm[num][19]);
		}
	if(coor_x[num][20]==16384 || coor_y[num][20]==16384 || coor_cm[num][20]==0){
	}else{
		printf("J %d x=%f %f %f \n",num,coor_x[num][20],coor_y[num][20],coor_cm[num][20]);
		}
	if(coor_x[num][21]==16384 || coor_y[num][21]==16384 || coor_cm[num][21]==0){
	}else{
		printf("J %d x=%f %f %f \n",num,coor_x[num][21],coor_y[num][21],coor_cm[num][21]);
		}
	if(coor_x[num][22]==16384 || coor_y[num][22]==16384 || coor_cm[num][22]==0){
	}else{
		printf("J %d x=%f %f %f \n",num,coor_x[num][22],coor_y[num][22],coor_cm[num][22]);
		}
	if(coor_x[num][23]==16384 || coor_y[num][23]==16384 || coor_cm[num][23]==0){
	}else{
		printf("J %d x=%f %f %f \n",num,coor_x[num][23],coor_y[num][23],coor_cm[num][23]);
		}
	if(coor_x[num][24]==16384 || coor_y[num][24]==16384 || coor_cm[num][24]==0){
	}else{
		printf("J %d x=%f %f %f \n",num,coor_x[num][24],coor_y[num][24],coor_cm[num][24]);
		}
}
*/

	if(coor_cm[num][0]>=v||coor_cm[num][1]>=v||coor_cm[num][2]>=v||coor_cm[num][3]>=v||coor_cm[num][4]>=v||coor_cm[num][5]>=v||coor_cm[num][6]>=v||coor_cm[num][7]>=v||coor_cm[num][8]>=v||coor_cm[num][9]>=v||coor_cm[num][10]>=v||coor_cm[num][11]>=v||coor_cm[num][12]>=v||coor_cm[num][13]>=v||coor_cm[num][14]>=v||coor_cm[num][15]>=v||coor_cm[num][16]>=v||coor_cm[num][17]>=v||coor_cm[num][18]>=v||coor_cm[num][19]>=v||coor_cm[num][20]>=v||coor_cm[num][21]>=v||coor_cm[num][22]>=v||coor_cm[num][23]>=v||coor_cm[num][24]>=v){
		if(fall[num]||station_rest[num]||station_hand[num]||sit_working[num]||sit_rest[num]||sit_hand[num])
		{output();

		//func();
		//write(sockfd, "a", 80);
		}
	}else{
		fall[num]=0;
		station_rest[num]=0;
		station_hand[num]=0;
		sit_working[num]=0;
		sit_rest[num]=0;
		sit_hand[num]=0;
	}

	//printf("dbg = %f %f %f \n", coor_cm[num][2],coor_cm[num][3],coor_cm[num][4]);
}

static void output(){
	//fix for the 0th person is not existent, might need to look into it more
	if(num==0)return;
	//print the results or other stuffs
	result = time(NULL);
	/*write(3, "a", 80);
	//write(sockfd, "a", 80);
	if(fall[num]==1)
	{
	printf("人類 %d 倒下了！@ %s \n", num, ctime(&result));
	write(3, "r", 80);
	}
	if(sit[num]==1)
	{
	printf("人類 %d 坐著!@ %s \n",num, ctime(&result));
	write(3, "s", 80);
	}
	if(station[num]==1)
	{
	printf("人類 %d 站著!@ %s \n",num, ctime(&result));
	write(3, "t", 80);
	}
	*/
	//if((i%3)==0)
	//if ((file_i%10)==0)
	//{
		//if (num == 1)
		//	{






	if(sit_rest[num]==1)
	{
 		if ((file_i%16)==0)//server data show 4 data/s
		{
			printf("人類 %d 坐著休息!@ %s \n", num, ctime(&result));
			//write(3, "0101 \n", 300);
			write(sockfd, "0101", 4);
			//write(3, "a", 300);
			//c=c+1;
			}
		}

	if(sit_working[num]==1)
	{
 		if ((file_i%16)==0)
		{
			printf("人類 %d 坐著工作中！@ %s \n", num, ctime(&result));
			write(sockfd, "0102", 4);
			//e=e+1;
			}
		}

	if(sit_hand[num]==1)
	{
 		if ((file_i%16)==0)
		{
			printf("人類 %d 坐著有問題!@ %s \n", num, ctime(&result));
			write(sockfd, "0103", 4);
			//d=d+1;
			}
		}

	if(station_rest[num]==1)
	{
 		if ((file_i%16)==0)
		{
			printf("人類 %d 站著休息！@ %s \n", num, ctime(&result));
			write(sockfd, "0104", 4);
			//a=a+1;
			}
				//write(3, "b", 300);
		}

	if(station_hand[num]==1)
	{
		if ((file_i%16)==0)
		{
			printf("人類 %d 站著有問題！@ %s \n", num, ctime(&result));
			write(sockfd, "0105", 4);
			//b=b+1;
			}
		}

	if(fall[num]==1)
	{
 		if ((file_i%16)==0)
		{
			printf("人類 %d 倒下了！@ %s \n", num, ctime(&result));
			write (sockfd, "0106", 4);
			//f=f+1;
			}

		}

/*
	printf("a = %d \n", a);
	printf("b = %d \n", b);
	printf("c = %d \n", c);
	printf("d = %d \n", d);
	printf("e = %d \n", e);
	printf("f = %d \n", f);
	printf("file = %lld \n", file_i);
*/
		//	}

	//}

		/*else if (num ==2)
			{
				if(sit_rest[num]==1)
				{
				printf("人類 %d 坐著休息!@ %s \n", num, ctime(&result));
				write(3, "0201 \n", 300);
				//write(3, "0200", 300);
				}

				if(sit_working[num]==1)
				{
				printf("人類 %d 坐著工作中！@ %s \n", num, ctime(&result));
				write(3, "0202", 300);
				}

				if(sit_hand[num]==1)
				{
				printf("人類 %d 坐著有問題!@ %s \n", num, ctime(&result));
				write(3, "0203", 300);
				}

				if(station_rest[num]==1)
				{
				printf("人類 %d 站著休息！@ %s \n", num, ctime(&result));
				write(3, "0204", 300);
				}

				if(station_hand[num]==1)
				{
				printf("人類 %d 站著有問題！@ %s \n", num, ctime(&result));
				write(3, "0205", 300);
				}

				if(fall[num]==1)
				{
				printf("人類 %d 倒下了！@ %s \n", num, ctime(&result));
				write (3, "0206", 300);

				}
			}*/
	//}


/*
//	if(righthand[num])printf("人類 %d 有問題 @ %s！\n", num, ctime(&result));
//	if(lefthand[num])printf("人類 %d 有問題 @ %s！\n", num, ctime(&result));
//	if(squat[num])printf("人類 %d 蹲下了!@ %s \n", num, ctime(&result));
//	if(sit[num])printf("人類 %d 坐著!@ %s \n",num, ctime(&result));
//	if(working[num])printf("人類 %d 工作中!@ %s \n",num, ctime(&result));
	if(sit_hand[num])printf("人類 %d 坐著有問題!@ %s \n",num, ctime(&result));
	if(sit_working[num])printf("人類 %d 坐著工作中!@ %s \n",num, ctime(&result));
	if(sit_rest[num])printf("人類 %d 坐著休息!@ %s \n",num, ctime(&result));
	if(station_hand[num])printf("人類 %d 站著有問題!@ %s \n",num, ctime(&result));
//	if(station_working[num])printf("人類 %d 請勿站著工作!@ %s \n",num, ctime(&result));
	if(station_rest[num])printf("人類 %d 站著休息!@ %s \n",num, ctime(&result));
//	if(station[num])printf("人類 %d 站著!@ %s \n",num, ctime(&result));
//	if(rest[num])printf("人類 %d 休息中!@ %s \n",num, ctime(&result));
*/
}

static void func()
{
        char buff[MAX];
        int n;
        for (;;) {
        bzero(buff, sizeof(buff));
               // printf("Enter the string : ");
        n = 0;
		//char buff[]= {"a"};
               // while ((buff[n++] = getchar()) != '\n')
	     // while (buff[n++] = "aaaaaa");
          	//	;
	//write(3, "x", 80);
	//write(3, "y", 100);
	//write(3, "z", 100);
	//if(fall[num])  write(3, "a", 10);
	//if(sit[num])  write(3, "b", 10);
	//if(station[num])   write(3, "c", 10);
                //write(sockfd, buff, sizeof(buff));
                //bzero(buff, sizeof(buff));
              //read(sockfd, buff, sizeof(buff));
             // printf("From Server : %s", buff);
         if ((strncmp(buff, "exit", 4)) == 0) {
         printf("Client Exit...\n");
                    break;
             }
       }
}

static void spit(json_value* value, int x, int y){
	switch(x%3){
		case 0:coorx(value, x, y);break;
		case 1:coory(value, x, y);break;
		case 2:coorcm(value, x, y);break;
		default:break;
	}
}


int main(int argc, char** argv){
	FILE *fp;
	struct stat filestatus;
	int file_size;
	char* file_contents;
	int pollingDelay = 100;
	json_char* json;
	json_value* value;

       // socket create and varification
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if (sockfd == -1) {
                printf("socket creation failed...\n");
                exit(0);
        }
        else{
                //printf("Socket successfully created..=%d \n", sockfd);
				printf("Socket successfully created.. \n");
		//printf("sockfd=%d \n", sockfd);
       	}
        bzero(&servaddr, sizeof(servaddr));

	//printf("sockfd=%d \n", sockfd);

	// assign IP, PORT
        servaddr.sin_family = AF_INET;
        servaddr.sin_addr.s_addr = inet_addr("192.168.100.8");
        servaddr.sin_port = htons(PORT);

        // connect the client socket to server socket
        if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) {
                printf("connection with the server failed...\n");
                exit(0);
        }
        else{
                printf("connected to the server..\n");
	//write(3, "b", 80);
	//write(3, "c", 80);
	/*for(file_i = 0;file_i < 10; file_i++){
		write(3, "w", 80);
	}*/
		printf("file_i = %lld \n", file_i);
	for(file_i = 0;file_i < 999999999999; file_i++){
	  //for(file_i = 0;file_i < 999999999999; file_i++){
	  /*
	  for(int j = 0;j< 1000; j++){
		write(3, "z", 80);
 		printf("j = %d \n", j);
		}
	  */
		/*for(file_i = 0;file_i < 100; file_i++){
			write(3, "q", 80);
		}*/
		sprintf(filenamestring, "%012lld", file_i);
		strcpy(filename, prependfilename);
		strcat(filename, filenamestring);
		strcat(filename, defaultfilename);
		//if file not found
		if ( stat(filename, &filestatus) != 0) {
			//printf("Filename: %s\n", filename);
			file_i--;
			#ifdef _WIN32
			Sleep(pollingDelay);
			#else
			usleep(pollingDelay*1000);
			#endif
		}
		else{
			//if OOM
			file_size = filestatus.st_size;
			file_contents = (char*)malloc(filestatus.st_size);
			if ( file_contents == NULL) {
				fprintf(stderr, "Memory error: unable to allocate %d bytes\n", file_size);
				return 1;
			}

			//if no read permission
			fp = fopen(filename, "rt");
			if (fp == NULL) {
				fprintf(stderr, "Unable to open %s\n", filename);
				fclose(fp);
				free(file_contents);
				return 1;
			}
			//if unable to read for some reason
			if ( fread(file_contents, file_size, 1, fp) != 1 ) {
				fprintf(stderr, "Unable to read content of %s\n", filename);
			}
			fclose(fp);

			//printf("%s\n", file_contents);

			json = (json_char*)file_contents;

			value = json_parse(json,file_size);

			if (value == NULL) {
				fprintf(stderr, "Unable to parse data\n");
			}

			process_value(value, 0, 0);

			json_value_free(value);
			free(file_contents);

			/*#ifdef _WIN32
			Sleep(pollingDelay);
			#else
			usleep(pollingDelay*1000);
			#endif
			*/

			remove(filename);
			for(int l=0; l<=num; l++){
				for(int n=0; n<16; n++){
					coor_y[l][n] = 16384.0;
					coor_x[l][n] = 16384.0;
					coor_cm[l][n] = 0;
				}
				lefthand[l] = 0;
				righthand[l] = 0;
				fall[l] = 0;
				hand[l] = 0;
				squat[l] = 0;
				sit[l] = 0;
				working[l] = 0;
				station[l] = 0;
				station_rest[l] = 0;
				station_working[l] = 0;
				station_hand[l] = 0;
				sit_working[l] = 0;
				sit_rest[l] = 0;
				sit_hand[l] = 0;
				rest[l] = 0;
			}
			num = -1;
			num_old = 0;
		}
	   }
         // close the socket
         close(sockfd);
	}
	return 0;
}

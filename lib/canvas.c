//
// Created by Evgeniy Vinogradov on 8/10/22.
//
#include <stdio.h>
#include <emscripten.h>
#include <stdlib.h>
#include <time.h>
//init  circle data

#define NUM_CIRCLES 20

struct Circle {
 int x;
 int y;
 int r;
 int cr;
 int cg;
 int cb;

};

struct CircleAnimationData {
    int x;
    int y;
    int r;
    int xv;
    int yv;
    int xd;
    int yd;
};

struct Circle circles[NUM_CIRCLES];
struct CircleAnimationData animationData[NUM_CIRCLES];

int getRand(int max) {
    return (rand() % max);
}

int main() {

    srand(time(NULL));

    for(int i=0; i <NUM_CIRCLES; i++) {
        int rad = getRand(50);

        int x= getRand(1000) + rad;
        int y = getRand(1000) + rad;

        animationData[i].x=x;
        animationData[i].y=y;
        animationData[i].r=rad;
        animationData[i].xv= getRand(10);
        animationData[i].yv= getRand(10);
        animationData[i].xd=1;
        animationData[i].yd=1;


        circles[i].x=x;
        circles[i].y=y;
        circles[i].r=rad;
        circles[i].cr= getRand(255);
        circles[i].cg= getRand(255);
        circles[i].cb= getRand(255);
    }
    EM_ASM({ render($0, $1);}, NUM_CIRCLES*6, 6 );
}

struct Circle * getCircles(int canvasHeight, int canvasWidth) {

    for (int i = 0; i <NUM_CIRCLES; i++) {

        if((animationData[i].x + animationData[i].r) >= canvasWidth ) animationData[i].xd=0;
        if((animationData[i].x - animationData[i].r) <=0 ) animationData[i].xd=1;

        if((animationData[i].y + animationData[i].r) >= canvasHeight ) animationData[i].yd=0;
        if((animationData[i].y - animationData[i].r) <=0 ) animationData[i].yd=1;

        if(animationData[i].xd==1) {
            animationData[i].x+=animationData[i].xv;
        } else {
            animationData[i].x-= animationData[i].xv;
        }

        if(animationData[i].yd==1) {
            animationData[i].y+=animationData[i].yv;
        } else {
            animationData[i].y-= animationData[i].yv;
        }

        circles[i].x= animationData[i].x;
        circles[i].y=animationData[i].y;
    }
    return circles;
}
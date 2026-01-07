#include <stdio.h>
#include <conio.h>
#include <dos.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define H 11
#define W 15
#define STUN_DURATION 15

char map[H][W+1] = {
    "###############",
    "#@....#.......#",
    "#.##..#..###..#",
    "#..#..#..#....#",
    "#..#..#..#.##.#",
    "#..#..#..#....#",
    "#..####..###..#",
    "#......#......#",
    "#.######.####.#",
    "#...D..K....E.#",
    "###############"
};

int px, py;
int dx_, dy_;
int has_key = 0;
int turns = 400;

int bx, by, bdx, bdy;
int bullet = 0;
int droid_stun = 0;
int droid_mode = 0;
int patrol_dir = 0;

void beep(int f){ sound(f); delay(25); nosound(); }
void shoot(){ beep(900); }
void stun(){ beep(1200); }
void warn(){ beep(600); }
void die(){ beep(200); }
void win(){ beep(1400); }

int inmap(int y,int x){ return x>=0 && y>=0 && x<W && y<H; }
int passable(int y,int x){ return inmap(y,x) && map[y][x] != '#'; }

void find_entities(){
    int y, x;
    for(y=0;y<H;y++)
        for(x=0;x<W;x++){
            if(map[y][x]=='@'){ px=x; py=y; map[y][x]='.'; }
            if(map[y][x]=='D'){ dx_=x; dy_=y; map[y][x]='.'; }
        }
}

void draw(){
    int y, x;
    clrscr();
    for(y=0;y<H;y++){
        for(x=0;x<W;x++){
            if(bullet && y==by && x==bx) 
                putch('-');
            else if(y==py && x==px) 
                putch('@');
            else if(y==dy_ && x==dx_){
                if(droid_stun > 0)
                    putch('X');
                else
                    putch('D');
            }
            else 
                putch(map[y][x]);
        }
        printf("\n");
    }
    printf("\nTIME:%d  KEY:%s  DROID:%s",
           turns, has_key?"YES":"NO", droid_stun?"STUNNED":"HUNTING");
}

void move_droid(){
    int vx[4]={0,0,-1,1};
    int vy[4]={-1,1,0,0};
    int i, nx, ny, d;
    int best_dx = 0, best_dy = 0;
    int best_dist, dist_to_player;
    
    dist_to_player = abs(px-dx_) + abs(py-dy_);
    
    if(dist_to_player < 8){
        droid_mode = 0;
    } else if(rand() % 10 < 3){
        droid_mode = 1;
    }
    
    if(droid_mode == 0){
        best_dist = dist_to_player;
        for(i=0;i<4;i++){
            nx = dx_ + vx[i];
            ny = dy_ + vy[i];
            if(passable(ny,nx)){
                d = abs(px-nx) + abs(py-ny);
                if(d < best_dist){
                    best_dist = d;
                    best_dx = vx[i];
                    best_dy = vy[i];
                }
            }
        }
    } else {
        best_dx = vx[patrol_dir];
        best_dy = vy[patrol_dir];
        
        nx = dx_ + best_dx;
        ny = dy_ + best_dy;
        
        if(!passable(ny, nx) || rand() % 20 == 0){
            patrol_dir = rand() % 4;
            best_dx = vx[patrol_dir];
            best_dy = vy[patrol_dir];
        }
    }
    
    dx_ += best_dx;
    dy_ += best_dy;
}

void update_bullet(){
    if(!bullet) return;
    bx += bdx;
    by += bdy;
    if(!inmap(by,bx) || map[by][bx]=='#'){
        bullet = 0;
        return;
    }
    if(bx==dx_ && by==dy_){
        droid_stun = STUN_DURATION;
        bullet = 0;
        stun();
    }
}

int main(){
    char ch;
    int last_dx = 1, last_dy = 0;
    int nx, ny;

    clrscr();
    printf("LOCATION - 6302 CORPORATION ROBOTICS ANNEX\n\n");
    printf("A hunter droid stalks the corridors.\n\n");
    printf("Find the key [K] and reach the exit [E].\n\n");
    printf("[W/A/S/D] to move, [SPACE] to shoot stun bolt.\n\n");
    printf("Press any key...");
    getch();

    randomize();
    find_entities();

    while(1){
        draw();

        if(turns-- <= 0){
            die();
            printf("\n\nLIFE SUPPORT FAILURE...\n");
            getch();
            return 0;
        }

        if(abs(px-dx_) + abs(py-dy_) <= 2 && droid_stun == 0)
            warn();

        if(px==dx_ && py==dy_){
            die();
            printf("\n\nYOU WERE TERMINATED...\n");
            getch();
            return 0;
        }

        ch = getch();

        if((ch=='w'||ch=='W') && passable(py-1,px)){
            py--; last_dx=0; last_dy=-1;
        }
        else if((ch=='s'||ch=='S') && passable(py+1,px)){
            py++; last_dx=0; last_dy=1;
        }
        else if((ch=='a'||ch=='A') && passable(py,px-1)){
            px--; last_dx=-1; last_dy=0;
        }
        else if((ch=='d'||ch=='D') && passable(py,px+1)){
            px++; last_dx=1; last_dy=0;
        }
        else if(ch==' ' && !bullet){
            nx = px + last_dx;
            ny = py + last_dy;
            if(passable(ny, nx)){
                bx = nx;
                by = ny;
                bdx = last_dx;
                bdy = last_dy;
                bullet = 1;
                shoot();
            }
        }

        update_bullet();

        if(map[py][px]=='K'){
            has_key = 1;
            map[py][px]='.';
        }

        if(map[py][px]=='E' && has_key){
            win();
            printf("\n\nYOU ESCAPE INTO THE WASTELAND. GOOD LUCK OUT THERE!\n");
            getch();
            return 0;
        }

        if(droid_stun > 0)
            droid_stun--;
        else
            move_droid();
    }
}
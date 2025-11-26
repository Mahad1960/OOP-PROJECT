#include<iostream>
#include<cstdlib>
#include<ctime>
#include<windows.h>
using namespace std;
class Entity{
public:
    int x, y;
    char ch;
    Entity(int px=1, int py=1, char c='P'){
	    x=px; y=py; ch=c;
	}
};
class Pacman : public Entity{
public:
    int score;
    Pacman(int px, int py) : Entity(px, py, 'P'), score(0) {}
    void move(){ 
    if((GetAsyncKeyState('A') || GetAsyncKeyState('a')) && x>1) x--; 
    if((GetAsyncKeyState('D') || GetAsyncKeyState('d')) && x<38) x++; 
    if((GetAsyncKeyState('W') || GetAsyncKeyState('w')) && y>1) y--; 
    if((GetAsyncKeyState('S') || GetAsyncKeyState('s')) && y<20) y++; 
    }
};
class Ghost : public Entity{
public:
    Ghost(int px, int py) : Entity(px, py, 'G') {}
    void chaseRandom(Pacman p){
        int r=rand()%2;
        if(r==0){ 
            if(p.x>x && x<38) x++;
            else if(p.x<x && x>1) x--;
        }else{ 
            if(p.y>y && y<20) y++;
            else if(p.y<y && y>1) y--;
        }
    }
};
class Game{
public:
    Pacman p;
    Ghost g1, g2;
    int pelletX[10], pelletY[10];
    bool eaten[10];
    Game() : p(4,5), g1(20,4), g2(20,12){
        srand(time(NULL));
        pelletX[0]=5;  pelletY[0]=2;
        pelletX[1]=10; pelletY[1]=3;
        pelletX[2]=15; pelletY[2]=5;
        pelletX[3]=20; pelletY[3]=7;
        pelletX[4]=25; pelletY[4]=9;
        pelletX[5]=30; pelletY[5]=4;
        pelletX[6]=7;  pelletY[6]=12;
        pelletX[7]=12; pelletY[7]=15;
        pelletX[8]=18; pelletY[8]=17;
        pelletX[9]=32; pelletY[9]=10;
        for(int i=0;i<10;i++){
        	eaten[i]=false;
		}
    }
    void drawFrame(){
        system("cls");
        for(int i=0;i<40;i++){
        	cout<<"*";
		} 
        cout<<endl;
        for(int y=1;y<=20;y++){
            cout<<"|";
            for(int x=1;x<39;x++){
                if(x==p.x && y==p.y) cout<<p.ch;
                else if(x==g1.x && y==g1.y) cout<<g1.ch;
                else if(x==g2.x && y==g2.y) cout<<g2.ch;
                else{
                    bool printed=false;
                    for(int k=0;k<10;k++){
                        if(!eaten[k] && x==pelletX[k] && y==pelletY[k]){ 
                            cout<<".";
                            printed=true;
                            break;
                        }
                    }
                    if(!printed) cout<<" ";
                }
            }
            cout<<"|"<<endl;
        }
        for(int i=0;i<40;i++){
        	cout<<"*";
		} 
        cout<<endl;
        cout<<"\nScore: "<<p.score<<endl;
    }
    void checkPelletEat(){
        for(int i=0;i<10;i++){
            if(!eaten[i] && p.x==pelletX[i] && p.y==pelletY[i]){
                eaten[i]=true;
                p.score++;
            }
        }
    }
    bool isCaught(){ 
		return (p.x==g1.x && p.y==g1.y) || (p.x==g2.x && p.y==g2.y);
	}   
    bool allPelletsEaten(){
        for(int i=0;i<10;i++){
        	if(!eaten[i]){
        	    return false;	
			} 
		}
        return true;
    }
    void run(){
        while(true){
            p.move();
            checkPelletEat();
            g1.chaseRandom(p);
            g2.chaseRandom(p);
            drawFrame();
            if(isCaught()){
                cout<<"GAME OVER! You were caught!\n";
                break;
            }
            if(allPelletsEaten()){
                cout<<"CONGRATULATIONS! You ate all the pellets!\n";
                break;
            }
            Sleep(200);
        }
        cout<<"Final Score: "<<p.score<<endl;
        cout<<"Press any key to exit...\n";
    }
};
int main(){
    Game game;
    game.run();
}

#define ALLEGRO_STATICLINK
#include <stdio.h>
#include <conio.h>
#include <allegro.h>

//prototypes of functions
void draw_tiger(int j,int k);
void draw_goat(int j,int k);

void draw_target(int j,int k);
void draw_board();
void reset_bord_player();
void show_bord_player();
void remove_player(int j,int k);
void add_tiger_player(int j,int k);
void add_goat_player(int j,int k);
int check_out_of_bord(int j, int k);
int check_location_available(int j,int k);

int check_up(int j,int k);
int check_down(int j,int k);
int check_left(int j,int k);
int check_right(int j,int k);
int check_up_left(int j,int k);
int check_up_right(int j,int k);
int check_down_left(int j,int k);
int check_down_right(int j,int k);

int check_possible_movement(int j,int k);
int check_possible_jump_movement(int j,int k);
void show_possible_movement(int j,int k);
void show_possible_jump_movement(int j,int k);
int check_movement_ok(int j,int k,int m,int n);
int check_jump_movement_ok(int j,int k,int m,int n);

//mouse location
int getx(int x);
int gety(int y);
int check_game_over();


//bitmaps decleration
    BITMAP *pointer;
    BITMAP *tiger;
    BITMAP *goat;
    BITMAP *target;
    BITMAP *board;
    BITMAP *buffer;
//GLOBAL VARIABLES DECLERATION
    int location[5][5];    
//misc variables
    int mx,my,mb;
    int turn, count_steps, count_dead_goat=0;
    int move,jump;
    int move_loc[8][1],jump_loc[8][1];
 
    
    

int check_game_over()
{
    int fixed_tiger=0;
    int game,m1,m2;
    for(int j=0; j<5;j++)
    {
     for (int k=0; k<5;k++)
     {
         m1=check_possible_movement(j,k);
         m2=check_possible_jump_movement(j,k);
      if (location[j][k]==1 && m1==0 && m2==0)     
         fixed_tiger++;
     }
    }

    if(fixed_tiger==4)
    {
               game=1;
               allegro_message("tigers that are fixed=%d GOAT WINS",fixed_tiger);
    }           
    else if (count_dead_goat > 5)
    {
         game=2;
         allegro_message("goats dead= %d TIGER WINS",count_dead_goat);
    }
    else
         game=0;
}
    
int getx(int x)
{
    int j;
    if( x>0 && x<95)
    j=0;
    else if( x>105 && x<175)
    j=1;
    else if( x>185 && x<260)
    j=2;
    else if( x>270 && x<345)
    j=3;
    else if( x>355 && x<430)
    j=4;
    else 
    j=-1;
    return j;
}
int gety(int y)
{
    int k;
    if( y>0 && y<95)
    k=0;
    else if( y>105 && y<175)
    k=1;
    else if( y>185 && y<260)
    k=2;
    else if( y>270 && y<345)
    k=3;
    else if( y>355 && y<430)
    k=4;
    else 
    k=-1;
    return k;
}


int check_jump_movement_ok(int j,int k,int m,int n)
{
  int count=0;
    int ok=0;

    if( check_up(j,k)==2 && check_up(j,k-1)==0)
    {
        jump_loc[count][0]=j;
        jump_loc[count][1]=k-2;        
        if(jump_loc[count][0]==m && jump_loc[count][1]==n)
        ok=1;
        count++;
    }
        if( check_down(j,k)==2 && check_down(j,k+1)==0)
    {
        jump_loc[count][0]=j;
        jump_loc[count][1]=k+2;        
        if(jump_loc[count][0]==m && jump_loc[count][1]==n)
        ok=1;
        count++;
    }
        if( check_left(j,k)==2 && check_left(j-1,k)==0)
    {
        jump_loc[count][0]=j-2;
        jump_loc[count][1]=k;        
        if(jump_loc[count][0]==m && jump_loc[count][1]==n)
        ok=1;
        count++;        
    }
        if( check_right(j,k)==2 && check_right(j+1,k)==0)
    {
        jump_loc[count][0]=j+2;
        jump_loc[count][1]=k;        
        if(jump_loc[count][0]==m && jump_loc[count][1]==n)
        ok=1;
        count++;        
    }
    if((j+k)%2==0)
    {
        if( check_up_left(j,k)==2 && check_up_left(j-1,k-1)==0)
    {
        jump_loc[count][0]=j-2;
        jump_loc[count][1]=k-2;        
        if(jump_loc[count][0]==m && jump_loc[count][1]==n)
        ok=1;
        count++;
    }
        if( check_up_right(j,k)==2  && check_up_right(j+1,k-1)==0)
    {
        jump_loc[count][0]=j+2;
        jump_loc[count][1]=k-2;        
        if(jump_loc[count][0]==m && jump_loc[count][1]==n)
        ok=1;
        count++;
    }
        if( check_down_left(j,k)==2 && check_down_left(j+1,k+1)==0)
    {
        jump_loc[count][0]=j+2;
        jump_loc[count][1]=k+2;        
        if(jump_loc[count][0]==m && jump_loc[count][1]==n)
        ok=1;
        count++;
    }
        if( check_down_right(j,k)==2 && check_down_right(j-1,k+1)==0)
    {
        jump_loc[count][0]=j-2;
        jump_loc[count][1]=k+2;        
        if(jump_loc[count][0]==m && jump_loc[count][1]==n)
        ok=1;
        count++;
    }
    }                          
    return ok;
}
int check_movement_ok(int j,int k,int m,int n)
{
  int count=0;
    int ok=0;  
        if( check_up(j,k)==0)
    {
        move_loc[count][0]=j;
        move_loc[count][1]=k-1;
        if(move_loc[count][0]==m && move_loc[count][1]==n)
        ok=1;
        count++;
    }
        if( check_down(j,k)==0)
    {
        move_loc[count][0]=j;
        move_loc[count][1]=k+1;
        if(move_loc[count][0]==m && move_loc[count][1]==n)
        ok=1;
        count++;
    }
        if( check_left(j,k)==0)
    {
        move_loc[count][0]=j-1;
        move_loc[count][1]=k;
        if(move_loc[count][0]==m && move_loc[count][1]==n)
        ok=1;
        count++;
    }
        if( check_right(j,k)==0)
    {
        move_loc[count][0]=j+1;
        move_loc[count][1]=k;
        if(move_loc[count][0]==m && move_loc[count][1]==n)
        ok=1;
        count++;
    }
    if((j+k)%2==0)
    {
        if( check_up_left(j,k)==0)
    {
        move_loc[count][0]=j-1;
        move_loc[count][1]=k-1;
        if(move_loc[count][0]==m && move_loc[count][1]==n)
        ok=1;
        count++;
    }
        if( check_up_right(j,k)==0)
    {
        move_loc[count][0]=j+1;
        move_loc[count][1]=k-1;
        if(move_loc[count][0]==m && move_loc[count][1]==n)
        ok=1;
        count++;
    }
        if( check_down_left(j,k)==0)
    {
        move_loc[count][0]=j+1;
        move_loc[count][1]=k+1;
        if(move_loc[count][0]==m && move_loc[count][1]==n)
        ok=1;
        count++;
    }
        if( check_down_right(j,k)==0)
    {
        move_loc[count][0]=j-1;
        move_loc[count][1]=k+1;
        if(move_loc[count][0]==m && move_loc[count][1]==n)
        ok=1;
        count++;
    }
    }           

    return ok;
}

void show_possible_jump_movement(int j,int k)
{
    int count=0;
    if( check_up(j,k)==2 && check_up(j,k-1)==0)
    {
        jump_loc[count][0]=j;
        jump_loc[count][1]=k-2;        
        draw_target(jump_loc[count][0],jump_loc[count][1]);
        count++;
    }
        if( check_down(j,k)==2 && check_down(j,k+1)==0)
    {
        jump_loc[count][0]=j;
        jump_loc[count][1]=k+2;        
        draw_target(jump_loc[count][0],jump_loc[count][1]);        
        count++;
    }
        if( check_left(j,k)==2 && check_left(j-1,k)==0)
    {
        jump_loc[count][0]=j-2;
        jump_loc[count][1]=k;        
        draw_target(jump_loc[count][0],jump_loc[count][1]);        
        count++;                
    }
        if( check_right(j,k)==2 && check_right(j+1,k)==0)
    {
        jump_loc[count][0]=j+2;
        jump_loc[count][1]=k;        
        draw_target(jump_loc[count][0],jump_loc[count][1]);        
        count++;
    }
    if((j+k)%2==0)
    {
        if( check_up_left(j,k)==2 && check_up_left(j-1,k-1)==0)
    {
        jump_loc[count][0]=j-2;
        jump_loc[count][1]=k-2;        
        draw_target(jump_loc[count][0],jump_loc[count][1]);        
        count++;
    }
        if( check_up_right(j,k)==2  && check_up_right(j+1,k-1)==0)
    {
        jump_loc[count][0]=j+2;
        jump_loc[count][1]=k-2;        
        draw_target(jump_loc[count][0],jump_loc[count][1]);
        count++;
    }
        if( check_down_left(j,k)==2 && check_down_left(j+1,k+1)==0)
    {
        jump_loc[count][0]=j+2;
        jump_loc[count][1]=k+2;        
        draw_target(jump_loc[count][0],jump_loc[count][1]);
        count++;
    }
        if( check_down_right(j,k)==2 && check_down_right(j-1,k+1)==0)
    {
        jump_loc[count][0]=j-2;
        jump_loc[count][1]=k+2;        
        draw_target(jump_loc[count][0],jump_loc[count][1]);        
        count++;
    }
    }
}
int check_possible_jump_movement(int j,int k)
{
    int count=0;
    if( check_up(j,k)==2 && check_up(j,k-1)==0)
    {
        jump_loc[count][0]=j;
        jump_loc[count][1]=k-2;        
//        draw_target(jump_loc[count][0],jump_loc[count][1]);
        count++;
    }
        if( check_down(j,k)==2 && check_down(j,k+1)==0)
    {
        jump_loc[count][0]=j;
        jump_loc[count][1]=k+2;        
  //      draw_target(jump_loc[count][0],jump_loc[count][1]);        
        count++;
    }
        if( check_left(j,k)==2 && check_left(j-1,k)==0)
    {
        jump_loc[count][0]=j-2;
        jump_loc[count][1]=k;        
    //    draw_target(jump_loc[count][0],jump_loc[count][1]);        
        count++;                
    }
        if( check_right(j,k)==2 && check_right(j+1,k)==0)
    {
        jump_loc[count][0]=j+2;
        jump_loc[count][1]=k;        
      //  draw_target(jump_loc[count][0],jump_loc[count][1]);        
        count++;
    }
    if((j+k)%2==0)
    {
        if( check_up_left(j,k)==2 && check_up_left(j-1,k-1)==0)
    {
        jump_loc[count][0]=j-2;
        jump_loc[count][1]=k-2;        
        //draw_target(jump_loc[count][0],jump_loc[count][1]);        
        count++;
    }
        if( check_up_right(j,k)==2  && check_up_right(j+1,k-1)==0)
    {
        jump_loc[count][0]=j+2;
        jump_loc[count][1]=k-2;        
//        draw_target(jump_loc[count][0],jump_loc[count][1]);
        count++;
    }
        if( check_down_left(j,k)==2 && check_down_left(j+1,k+1)==0)
    {
        jump_loc[count][0]=j+2;
        jump_loc[count][1]=k+2;        
  //      draw_target(jump_loc[count][0],jump_loc[count][1]);
        count++;
    }
        if( check_down_right(j,k)==2 && check_down_right(j-1,k+1)==0)
    {
        jump_loc[count][0]=j-2;
        jump_loc[count][1]=k+2;        
    //    draw_target(jump_loc[count][0],jump_loc[count][1]);        
        count++;
    }
    }
    return count;    
}
    
    
void show_possible_movement(int j,int k)
{
    int count=0;
        if( check_up(j,k)==0)
    {
        move_loc[count][0]=j;
        move_loc[count][1]=k-1;
        draw_target(move_loc[count][0],move_loc[count][1]);
        count++;
    }
        if( check_down(j,k)==0)
    {
        move_loc[count][0]=j;
        move_loc[count][1]=k+1;
        draw_target(move_loc[count][0],move_loc[count][1]);        
        count++;
    }
        if( check_left(j,k)==0)
    {
        move_loc[count][0]=j-1;
        move_loc[count][1]=k;
        draw_target(move_loc[count][0],move_loc[count][1]);        
        count++;
    }
        if( check_right(j,k)==0)
    {
        move_loc[count][0]=j+1;
        move_loc[count][1]=k;
        draw_target(move_loc[count][0],move_loc[count][1]);        
        count++;
    }
    if((j+k)%2==0)
    {
        if( check_up_left(j,k)==0)
    {
        move_loc[count][0]=j-1;
        move_loc[count][1]=k-1;
        draw_target(move_loc[count][0],move_loc[count][1]);        
        count++;
    }
        if( check_up_right(j,k)==0)
    {
        move_loc[count][0]=j+1;
        move_loc[count][1]=k-1;
        draw_target(move_loc[count][0],move_loc[count][1]);        
        count++;
    }
        if( check_down_left(j,k)==0)
    {
        move_loc[count][0]=j+1;
        move_loc[count][1]=k+1;
        draw_target(move_loc[count][0],move_loc[count][1]);        
        count++;
    }
        if( check_down_right(j,k)==0)
    {
        move_loc[count][0]=j-1;
        move_loc[count][1]=k+1;
        draw_target(move_loc[count][0],move_loc[count][1]);        
        count++;
    }
    }   
}    
    
int check_possible_movement(int j,int k)
{
    int count=0;
        if( check_up(j,k)==0)
    {
        move_loc[count][0]=j;
        move_loc[count][1]=k-1;
  //      draw_target(move_loc[count][0],move_loc[count][1]);
        count++;
    }
        if( check_down(j,k)==0)
    {
        move_loc[count][0]=j;
        move_loc[count][1]=k+1;
    //    draw_target(move_loc[count][0],move_loc[count][1]);        
        count++;
    }
        if( check_left(j,k)==0)
    {
        move_loc[count][0]=j-1;
        move_loc[count][1]=k;
      //  draw_target(move_loc[count][0],move_loc[count][1]);        
        count++;
    }
        if( check_right(j,k)==0)
    {
        move_loc[count][0]=j+1;
        move_loc[count][1]=k;
        //draw_target(move_loc[count][0],move_loc[count][1]);        
        count++;
    }
    if((j+k)%2==0)
    {
        if( check_up_left(j,k)==0)
    {
        move_loc[count][0]=j-1;
        move_loc[count][1]=k-1;
//        draw_target(move_loc[count][0],move_loc[count][1]);        
        count++;
    }
        if( check_up_right(j,k)==0)
    {
        move_loc[count][0]=j+1;
        move_loc[count][1]=k-1;
  //      draw_target(move_loc[count][0],move_loc[count][1]);        
        count++;
    }
        if( check_down_left(j,k)==0)
    {
        move_loc[count][0]=j+1;
        move_loc[count][1]=k+1;
    //    draw_target(move_loc[count][0],move_loc[count][1]);        
        count++;
    }
        if( check_down_right(j,k)==0)
    {
        move_loc[count][0]=j-1;
        move_loc[count][1]=k+1;
      //  draw_target(move_loc[count][0],move_loc[count][1]);        
        count++;
    }
    }   
    return count;
}    

      

int check_down_right(int j,int k)
{ 
  return check_location_available(j-1,k+1);
}

    
int check_down_left(int j,int k)
{ 
    return check_location_available(j+1,k+1);
}
    
    
int check_up_right(int j,int k)
{ 
    return check_location_available(j+1,k-1);
}

    
int check_up_left(int j,int k)
{ 
    return check_location_available(j-1,k-1);
}
    
    
int check_right(int j,int k)
{ 
    return check_location_available(j+1,k);
}


int check_left(int j,int k)
{ 
    return check_location_available(j-1,k);
}


int check_down(int j,int k)
{ 
  return check_location_available(j,k+1);
}


int check_up(int j,int k)
{ 
    return check_location_available(j,k-1);
}

int check_location_available(int j,int k)
{
    int ans;
    if (check_out_of_bord(j, k)==0)
       ans=3;
    else 
         ans=location[j][k];
    return ans;
}

int check_out_of_bord(int j, int k)
{
    int ans;
    if (j>4||k>4||j<0||k<0)
       ans=0;
    else
        ans=1;
    return ans;
}

void remove_player(int j,int k)
{
     location[j][k]=0;
}
void add_tiger_player(int j,int k)
{
     location[j][k]=1;
}
void add_goat_player(int j,int k)
{
     location[j][k]=2;
}
void reset_bord_player()
{
    for (int j=0;j<=4 ;j++)
    {
     for (int k=0 ;k<=4;k++)    
     {
         if (j==4&&k==0||j==4&&k==4||j==0&&k==4||j==0&&k==0)
            add_tiger_player(j,k);
         else
            remove_player(j,k);
     }
    }
}


void show_bord_player()
{
     draw_board();
    for (int j=0;j<=4 ;j++)
    {
     for (int k=0 ;k<=4;k++)    
     {
         if (location[j][k]==1)
            draw_tiger(j,k);
         else if(location[j][k]==2)
            draw_goat(j,k);              
     }
    }

    blit(buffer,screen,0,0,0,0,640,480);
}

void draw_board()
{
    masked_blit(board,buffer,0,0,0,0,460,460);     
}
void draw_target(int j,int k)
{
     //target screen not buffer
     masked_blit(target, screen,0,0,j*95-5,k*95-5,78,78);
}



void draw_tiger(int j,int k)
{
     masked_blit(tiger, buffer,0,0,j*95+20-31,k*95+20-39,63,78);
}

void draw_goat(int j,int k)
{
     masked_blit(goat, buffer,0,0,j*95+20-25,k*95+20-20,76,60);
}



int main()
{
    //initialize allegro
    allegro_init();
    install_keyboard();
    install_mouse();      
    //initialize video mode to 640x480
    set_color_depth(16);
    int ret = set_gfx_mode(GFX_AUTODETECT_WINDOWED, 640, 480, 0, 0);
    

    pointer = load_bitmap("pointer.bmp", NULL);
    board=load_bitmap("bord.bmp",NULL);
    tiger=load_bitmap("tiger.bmp",NULL);
    goat=load_bitmap("goat.bmp",NULL);
    target=load_bitmap("target.bmp",NULL);
    buffer = create_bitmap(640,480);
    // mouse
    set_mouse_sprite(pointer);
    set_mouse_sprite_focus(15,15);
    show_mouse(screen);

    reset_bord_player();
    show_bord_player();
    turn=2;  

//wait
int tempx,tempy,temp_player ;    
while (!key[KEY_ESC])
{
//grab the current mouse values
mx = mouse_x;
my = mouse_y;
mb = (mouse_b & 1);

    

 temp_player= check_location_available(getx(mx),getx(my));
if (temp_player!=3 && mb==1)
{
    if (turn==1 && temp_player==1)
    {
             textout_ex(buffer, font, "TIGER'S TURN", 480, 1, 1, -1);
              textout_ex(buffer, font, "FIND TIGER PLACE",480, 1 , 14, -1);
                  tempx=getx(mx);
                  tempy=gety(my);
                turn=11;
    }
    else if(turn==11 && temp_player==0)
    {
         if(check_movement_ok(tempx,tempy,getx(mx),gety(my))==1)
         {
        add_tiger_player(getx(mx),gety(my));
        remove_player(tempx,tempy);
        turn=2;
         textout_ex(buffer, font, "FIND TIGER PLACE", 480, 1, 1, -1);
         textout_ex(buffer, font, "GOAT'S TURN",480, 1 , 14, -1);
         }
         else if(check_jump_movement_ok(tempx,tempy,getx(mx),gety(my))==1)
         {
        add_tiger_player(getx(mx),gety(my));
        remove_player(tempx,tempy);
        remove_player((tempx+getx(mx))/2,(tempy+gety(my))/2);
        turn=2;
         textout_ex(buffer, font, "FIND TIGER PLACE", 480, 1, 1, -1);
         textout_ex(buffer, font, "GOAT'S TURN",480, 1 , 14, -1);
         count_dead_goat++;
         }

         
    }
    else if(turn==2  && temp_player==2 && count_steps>=20)
    {
         turn=22;
         textout_ex(buffer, font, "GOAT'S TURN",480, 1 , 1, -1);
         textout_ex(buffer, font, "FIND GOAT PLACE",480, 1 , 14, -1);
                  tempx=getx(mx);
                  tempy=gety(my);

    }
    else if(turn==22 && temp_player==0)
    {
         if(check_movement_ok(tempx,tempy,getx(mx),gety(my))==1)
         {
             add_goat_player(getx(mx),gety(my));
              remove_player(tempx,tempy);
    turn=1;
         textout_ex(buffer, font, "FIND GOAT PLACE",480, 1 , 1, -1);
         textout_ex(buffer, font, "TIGER'S TURN", 480, 1, 14, -1);
         }
    }
    else if(turn==2 && temp_player==0 && count_steps<20)
    {
         count_steps++;
    add_goat_player(getx(mx),gety(my));
    turn=1;
         textout_ex(buffer, font, "GOAT'S TURN",480, 1 , 1, -1);
         textout_ex(buffer, font, "TIGER'S TURN", 480, 1, 14, -1);

    }
    if ( check_game_over()==1)
    {
         textout_ex(buffer, font, "GOAT WINS", 480, 30, 14, -1);
         goto end;
         }
    else if ( check_game_over()==2)
    {
         textout_ex(buffer, font, "TIGER WINS", 480, 30, 14, -1);
         goto end;
         }
    

    show_bord_player();
       if (turn==11)
    {     

          jump=check_possible_jump_movement(tempx,tempy);     
          move=check_possible_movement(tempx,tempy);
          show_possible_jump_movement(tempx,tempy);
          show_possible_movement(tempx,tempy);
          if( jump==0 && move==0 )
          {
          turn=1;
          textout_ex(buffer, font,"FIND TIGER PLACE" , 480, 1, 1, -1);
          textout_ex(buffer, font, "TIGER'S TURN",480, 1 , 14, -1);
          }
    }
       if (turn==22)
    {
          move=check_possible_movement(tempx,tempy);
          show_possible_movement(tempx,tempy);          
          if (move==0)
          {
          turn=2;
          textout_ex(buffer, font, "FIND GOAT PLACE",480, 1 , 1, -1);
          textout_ex(buffer, font, "GOAT'S TURN", 480, 1, 14, -1);
          }

     
    }
}
     
//pause
rest(10);
}
end:;
allegro_message("game over");    
    set_mouse_sprite(NULL);
    destroy_bitmap(pointer);
    destroy_bitmap(board);
    destroy_bitmap(tiger);
    destroy_bitmap(goat);
    destroy_bitmap(buffer);
    destroy_bitmap(target);
    allegro_exit();    
    return 0;
}
END_OF_MAIN()

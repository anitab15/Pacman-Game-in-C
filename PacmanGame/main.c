#include "header.h"
#define NO_STDIO_REDIRECT

SDL_Rect cor={24,25};
SDL_Rect offset={0,0};
int quit=no;

SDL_Surface *load_image( char filename[] )
{
    //Temporary storage for the image that's loaded
    SDL_Surface* loadedImage = NULL;

    //The optimized image that will be used
    SDL_Surface* optimizedImage = NULL;
    //Load the image
    char file[]="sprites/";
    strcat(file,filename);

    loadedImage = IMG_Load( file);
    //If nothing went wrong in loading the image
    if( loadedImage != NULL )
    {
        //Create an optimized image
        optimizedImage = SDL_DisplayFormat( loadedImage );
if(optimizedImage!=NULL)
printf("\nImage Loaded");

        //Free the old image0
        SDL_FreeSurface( loadedImage );
    }

    else
        printf("\nImage not loaded: %s",SDL_GetError());
    //Return the optimized image
    return optimizedImage;
}



int main(int argc, char *argv[])
{

       if(SDL_Init(SDL_INIT_EVERYTHING)!=-1)

 printf("SDL INITIALIZED");


    SDL_Surface* screen;
    screen=SDL_SetVideoMode(500,350,32,SDL_SWSURFACE);
  /*  SDL_Surface* bg=load_image("dark.jpg");

if(bg==NULL)
    printf(SDL_GetError());
else
    printf("\ngot an img");
*/
    int key_press;
    SDL_WM_SetIcon(IMG_Load("pacman_16X16.png"), NULL);
    SDL_WM_SetCaption("Pacman","pacman_16X16.png");

    SDL_Event event;
    extern int quit;

  /*  int n=SDL_BlitSurface(bg,NULL,screen,&offset);
  printf("\n%d",n);
*/
 //build_map(screen);
  gameplay(screen);

if(SDL_Flip(screen)==-1)
    printf("not done");
else
    printf("\ndone");

freopen("CON","w",stdout);
  freopen("CON","w",stderr);


SDL_Delay(500);
      getch();
        return 0;
}






void pacman_sprites(SDL_Rect location,int direction,SDL_Surface* screen,char comp[20][12])
{



    SDL_Rect char_up,char_down,char_left,char_right,char_neutral,char_dead;
//definition of sprites
    char_up.x=0; char_up.y=20;  char_up.w=20;  char_up.h=20;
    char_down.x=20; char_down.y=20;  char_down.w=20;  char_down.h=20;
    char_left.x=20; char_left.y=0;  char_left.w=20;  char_left.h=20;
    char_right.x=40; char_right.y=0;  char_right.w=20;  char_right.h=20;
    char_neutral.x=0; char_neutral.y=0;  char_neutral.w=20;  char_neutral.h=20;
    char_dead.x=40; char_dead.y=20;  char_dead.w=20;  char_dead.h=20;
// end def of sprites
    SDL_Surface *one,*two;
    one=load_image("pac.gif");
    two=load_image("pac_f.gif");

   if  (legibility(comp,&direction)==yes)
    {
        moveit(direction); // it just changes  the co-ordinates.....doesnt animate sprites
    switch(direction)
    {
        case SDLK_UP:
        SDL_BlitSurface(one,&char_up,screen,&location);
        SDL_Flip(screen);
        break;
        case SDLK_DOWN:
        SDL_BlitSurface(one,&char_down,screen,&location);
        SDL_Flip(screen);
         break;
        case SDLK_RIGHT:
        SDL_BlitSurface(one,&char_right,screen,&location);
        SDL_Flip(screen);
        break;
        case SDLK_LEFT:
        SDL_BlitSurface(one,&char_left,screen,&location);
        SDL_Flip(screen);
        break;
    }


    SDL_Delay(75);
    SDL_BlitSurface(one,&char_neutral,screen,&location);
    SDL_Flip(screen);


    SDL_Delay(75);
    SDL_BlitSurface(two,NULL,screen,&location);
    SDL_Flip(screen);
    }
    else
    {
        SDL_Delay(1000);
        SDL_BlitSurface(one,&char_neutral,screen,&location);
        SDL_Flip(screen);
    }



    SDL_FreeSurface(one);
    SDL_FreeSurface(two);

}



void gameplay(SDL_Surface* screen)
{

    extern int quit;
    char comp[20][12];
    extern SDL_Rect cor;
    SDL_Event event;
    int key_press;



    createmap(screen,comp);

    while (quit==no)
    {
           while(SDL_PollEvent(&event))
           {

                if(event.type==SDL_QUIT) quit=yes;
                if (event.type==SDL_KEYDOWN)   key_press=event.key.keysym.sym;
            }




           pacman_sprites(cor,key_press,screen,comp);

    }
}

#include <Gamebuino-Meta.h>

int ship_pos_x = 15;
int ship_pos_y = 35;

int ast_pos_x = random(gb.display.width(), (gb.display.width() +5));
int ast_pos_y = random(6, (gb.display.height()-5));
int ast_size = random(5, 7);

int asteroids[2][2];
int compteur;
void setup()
{
    gb.begin();
    for(int i = 0; i < 2; i++){
      asteroids[i][0] = random(gb.display.width(), (gb.display.width() +5));
      asteroids[i][1] = random(6, (gb.display.height()-5));
    }
}

void loop()
{
    while (!gb.update())
        ;
    gb.display.clear();

    //DISPLAY SHIP
    gb.display.setColor(GREEN);
    gb.display.fillRect(ship_pos_x, ship_pos_y, 5, 5);
    gb.display.drawRect(ship_pos_x, ship_pos_y, 5, 5);

    //SHIP MOVEMENTS
    if (gb.buttons.repeat(BUTTON_UP, 0))
    {
        gb.display.drawRect(ship_pos_x, --ship_pos_y, 5, 5);
    }

    if (gb.buttons.repeat(BUTTON_DOWN, 0))
    {
        gb.display.drawRect(ship_pos_x, ++ship_pos_y, 5, 5);
    }

    if (gb.buttons.repeat(BUTTON_RIGHT, 0))
    {
        gb.display.drawRect(++ship_pos_x, ship_pos_y, 5, 5);
    }

    if (gb.buttons.repeat(BUTTON_LEFT, 0))
    {
        gb.display.drawRect(--ship_pos_x, ship_pos_y, 5, 5);
    }

    if (ship_pos_y < 6)
    {
        ship_pos_y = 6;
    }
    if ((ship_pos_y + 5) >= gb.display.height())
    {
        ship_pos_y = 63 - 5;
    }
    if (ship_pos_x <= 0)
    {
        ship_pos_x = 0;
    }
    if ((ship_pos_x + 5) >= gb.display.width())
    {
        ship_pos_x = gb.display.width() - 5;
    }

    //ASTEROIDS
    //refaire apparaître l'astéroide quand il arrive au bout de l'écran
    
      //ast_pos_x = gb.display.width();
      for(int i = 0; i < 2; i++){
        if(asteroids[i][0] + 5 < 0){
          asteroids[i][0] = random(gb.display.width(), (gb.display.width() +5));
          asteroids[i][1] = random(6, (gb.display.height()-5));
          gb.display.drawRect(asteroids[i][0], asteroids[i][1], ast_size, ast_size);
        }
      }

    //Astéroides : Apparaissent de façon aléatoire de 0(+5 dimensions) à 69(-5) et se dirigent à une speed_x de -1
    for(int i = 0; i < 2 ; i++){
      gb.display.drawRect(asteroids[i][0], asteroids[i][1], ast_size, ast_size);
    }
    for(int i = 0; i < 2; i++){
       asteroids[i][0] = asteroids[i][0] -1;
    }
    

    //collision entre ship & asteroide
    bool crash = gb.collide.rectRect(ship_pos_x, ship_pos_y, 5, 5, ast_pos_x, ast_pos_y, ast_size, ast_size);
    
    //Compteur qui s'incrémente de 1 tant qu'il n'y à pas de collisions entre un astéroide et le joueur
}

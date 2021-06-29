#include <Gamebuino-Meta.h>

//infos vaisseau
int ship_pos_x = 15;
int ship_pos_y = 35;

//infos asteroides
int asteroids[3][4];
int last_pos_y;
int ast_size = random(5, 10);

//etat vaisseau 
bool vaisseau = true;

int score;

void setup()
{
  gb.begin();
  for (int i = 0; i < 3; i++) {
    //asteroids[i][0] correspond à la position X
    asteroids[i][0] = random(gb.display.width(), (gb.display.width() + 10));
    //asteroids[i][1] correspond à la position Y
    asteroids[i][1] = random(6, (gb.display.height() - 5));
    asteroids[i][2] = random(5, 10);
    asteroids[i][3] = random(5, 10);
    while(asteroids[i][1] >= last_pos_y && asteroids[i][1] <= last_pos_y + 10){
      asteroids[i][1] = random(6, (gb.display.height() - 5));
    }
    last_pos_y = asteroids[i][1];
  }
}

void loop()
{
  while (!gb.update())
    ;
  gb.display.clear();

  if (vaisseau) {
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

    //Compteur qui s'incrémente de 1 tant qu'il n'y à pas de collisions entre un astéroide et le joueur
    gb.display.print("score : ");
    gb.display.print(score);
    score = score + 1;

    //big condition collision
    for (int i = 0; i < 3; i++) {
      //ASTEROIDS
      //refaire apparaître l'astéroide quand il arrive au bout de l'écran
      gb.display.setColor(BROWN);
      if (asteroids[i][0] + 5 < 0) {
        asteroids[i][0] = random(gb.display.width(), (gb.display.width() + 10));
        asteroids[i][1] = random(6, (gb.display.height() - ast_size));
        asteroids[i][2] = random(5, 10);
        asteroids[i][3] = random(5, 10);
        //eviter la collision entre deux asteroides
        while(asteroids[i][1] >= last_pos_y && asteroids[i][1] <= last_pos_y + 10){
          asteroids[i][1] = random(6, (gb.display.height() - 5));
        }
        gb.display.drawRect(asteroids[i][0], asteroids[i][1], asteroids[i][2], asteroids[i][3]);
        last_pos_y = asteroids[i][1];
      }
      //Astéroides : Apparaissent de façon aléatoire de 0(+5 dimensions) à 69(-5) et se dirigent à une speed_x de -1
      gb.display.drawRect(asteroids[i][0], asteroids[i][1], asteroids[i][2], asteroids[i][3]);
      asteroids[i][0] = asteroids[i][0] - 1;
      
      //collision entre vaisseau et astéroide
      if(gb.collide.rectRect(asteroids[i][0], asteroids[i][1], asteroids[i][2], asteroids[i][3], ship_pos_x, ship_pos_y, 5, 5)){
        gb.display.clear();
        gb.display.print("You loose !");
        delay(1500);
        vaisseau = false; 
      }
    }
  }
}

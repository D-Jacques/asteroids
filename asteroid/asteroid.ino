#include <Gamebuino-Meta.h>

//infos vaisseau
int ship_pos_x = 15;
int ship_pos_y = 35;

//infos asteroides
int asteroids[3][4];
int last_pos_y;

//etat vaisseau
bool vaisseau = true;

//Ecran
enum ecrans {MAIN, JEU};
enum ecrans ecran = MAIN;

//Score du jeu
int score;
int highscore = 0;

void setup()
{
  gb.begin();
  //initialisation du tableau des asteroides
  for (int i = 0; i < 3; i++) {
    //gérer les tailles avant les positions pour que les astéroides ne quittent pas l'écrans
    //size X
    asteroids[i][2] = random(5, 10);
    //size Y
    asteroids[i][3] = random(5, 10);
    //asteroids[i][0] correspond à la position X
    asteroids[i][0] = random(gb.display.width(), (gb.display.width() + 10));
    //asteroids[i][1] correspond à la position Y
    asteroids[i][1] = random(6, (gb.display.height() - 5));
    //gérer la superposition
    while (asteroids[i][1] >= last_pos_y && asteroids[i][1] <= last_pos_y + asteroids[i][3]) {
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

  switch (ecran)
  {
    case MAIN:
      //visuel de l'ecran d'accueil
      gb.display.setColor (BLACK);
      gb.display.fillRect(0, 0, gb.display.width(), gb.display.height());
      gb.display.setColor (WHITE);
      gb.display.setCursorX(10);
      gb.display.setCursorY(7);
      gb.display.print("Asteroid Dodger");
      gb.display.setCursorX(10);
      gb.display.setCursorY(30);
      gb.display.printf("Highscore: %d", highscore);
      //On affiche les différentes options
      gb.display.setColor (WHITE);
      gb.display.setCursorX(10);
      gb.display.setCursorY(20);
      gb.display.print("A: New Game");
      //lancer une parti en pressant le bouton A
      if (gb.buttons.pressed(BUTTON_A)) {
        vaisseau = true;
        setup();
        ecran = JEU;
      }
      break;
    case JEU:
      if (vaisseau) {
        //VAISSEAU
        //affichage du vaisseau
        gb.display.setColor(GREEN);
        gb.display.fillRect(ship_pos_x, ship_pos_y, 5, 5);
        gb.display.drawRect(ship_pos_x, ship_pos_y, 5, 5);

        //déplacement vaisseau
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

        //score qui s'incremente de 1 tant qu'il n'y a pas de collisions entre un asteroide et le joueur
        gb.display.print("score : ");
        gb.display.print(score);
        score = score + 1;

        //ASTEROIDES
        gb.display.setColor(BROWN);
        for (int i = 0; i < 3; i++) {
          //refaire apparaître un nouvel asteroide à droite quand il arrive au bout de l'ecran
          if (asteroids[i][0] + asteroids[i][2] < 0) {
            asteroids[i][2] = random(5, 10);
            asteroids[i][3] = random(5, 10);
            asteroids[i][0] = random(gb.display.width(), (gb.display.width() + 10));
            asteroids[i][1] = random(6, (gb.display.height() - asteroids[i][3]));
            //eviter la superposition entre deux asteroides
            //for (int j = i + 1; j < 3 - 1; j++) {
            while (asteroids[i][1] >= last_pos_y && asteroids[i][1] <= (last_pos_y + asteroids[i][3])) {
              //gb.collide.rectRect(asteroids[i][0], asteroids[i][1], asteroids[i][2], asteroids[i][3], asteroids[j][0], asteroids[j][1], asteroids[j][2], asteroids[j][3])
              asteroids[i][1] = random(6, (gb.display.height() - asteroids[i][3]));
            }
            //}
            gb.display.drawRect(asteroids[i][0], asteroids[i][1], asteroids[i][2], asteroids[i][3]);
            last_pos_y = asteroids[i][1];
          }
          //faire apparaitre les asteroides de façon aleatoire de 0(+ random dimensions) à 69 et se dirigent a une vitesse de -1
          gb.display.drawRect(asteroids[i][0], asteroids[i][1], asteroids[i][2], asteroids[i][3]);
          asteroids[i][0] = asteroids[i][0] - 1;

          //collision entre vaisseau et astéroide
          if (gb.collide.rectRect(asteroids[i][0], asteroids[i][1], asteroids[i][2], asteroids[i][3], ship_pos_x, ship_pos_y, 5, 5)) {
            gb.display.clear();
            gb.display.print("You loose !");
            delay(1500);
            //modifier le plus haut score si meilleure performance
            if (score > highscore) {
              highscore = score;
            }
            score = 0;
            ecran = MAIN;
            vaisseau = false;
          }
        }
      }
      break;
  }
}

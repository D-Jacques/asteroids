#include <Gamebuino-Meta.h>

int ship_pos_x = 15;
int ship_pos_y = 35;

void setup()
{
    gb.begin();
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
    if (gb.buttons.pressed(BUTTON_UP))
    {
        gb.display.drawRect(ship_pos_x, --ship_pos_y, 5, 5);
    }

    if (gb.buttons.pressed(BUTTON_DOWN))
    {
        gb.display.drawRect(ship_pos_x, ++ship_pos_y, 5, 5);
    }

    if (gb.buttons.pressed(BUTTON_RIGHT))
    {
        gb.display.drawRect(++ship_pos_x, ship_pos_y, 5, 5);
    }

    if (gb.buttons.pressed(BUTTON_LEFT))
    {
        gb.display.drawRect(--ship_pos_x, ship_pos_y, 5, 5);
    }

    //Astéroides : Apparaissent de façon aléatoire de 0(+5 dimensions) à 69(-5) et se dirigent à une speed_x de -1
    //Compteur qui s'incrémente de 1 tant qu'il n'y à pas de collisions entre un astéroide et le joueur
}
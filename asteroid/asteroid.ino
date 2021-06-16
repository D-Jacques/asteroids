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
    if (gb.buttons.repeat(BUTTON_UP, 5))
    {
        gb.display.drawRect(ship_pos_x, --ship_pos_y, 5, 5);
    }

    if (gb.buttons.repeat(BUTTON_DOWN, 5))
    {
        gb.display.drawRect(ship_pos_x, ++ship_pos_y, 5, 5);
    }

    if (gb.buttons.repeat(BUTTON_RIGHT, 5))
    {
        gb.display.drawRect(++ship_pos_x, ship_pos_y, 5, 5);
    }

    if (gb.buttons.repeat(BUTTON_LEFT, 5))
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

    //Astéroides : Apparaissent de façon aléatoire de 0(+5 dimensions) à 69(-5) et se dirigent à une speed_x de -1
    //Compteur qui s'incrémente de 1 tant qu'il n'y à pas de collisions entre un astéroide et le joueur
}
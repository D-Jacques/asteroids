# 1 "e:\\Logiciels\\arduino\\portable\\sketchbook\\asteroid\\asteroid.ino"
# 1 "e:\\Logiciels\\arduino\\portable\\sketchbook\\asteroid\\asteroid.ino"
# 2 "e:\\Logiciels\\arduino\\portable\\sketchbook\\asteroid\\asteroid.ino" 2

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
}

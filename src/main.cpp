#include <Arduino.h>
#include <ui.hpp>

void setup()
{
    ui::UI *ui = new ui::UI;
    ui::Interface *interface = new ui::Interface(ui,
    new ui::Buttons({
        new ui::StaticButton(15, 15, 20, 25, ui),
        new ui::StaticButton(100, 200, 37, 31, ui)
    }));
    interface->buttons->buttons[1]->select(true);
    ui->init();
    //ui::StaticButton TestButton(15, 15, 20, 25, ui);
    //TestButton.draw();
    interface->draw();
    while(true);
}

void loop()
{
}
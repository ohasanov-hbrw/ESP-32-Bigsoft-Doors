#include <Arduino.h>
#include <ui.hpp>

void setup()
{
    Serial.begin(115200);
    ui::UI *ui = new ui::UI;
    ui::Interface *interface = new ui::Interface(ui,
    {
        new ui::StaticButton(15, 15, 20, 25, ui, [](ui::UI *ui){
            Serial.println("Button 0 is clicked");
            ui->tft.setCursor(20,150);
            ui->tft.setTextColor(TFT_WHITE);
            ui->tft.setTextSize(2);
            ui->tft.print("Button 0 yay");
        }),
        new ui::StaticButton(100, 200, 31, 69, ui, [](ui::UI *ui){
            Serial.println("Button 1 is clicked");
            ui->tft.setCursor(20,150);
            ui->tft.setTextColor(TFT_WHITE);
            ui->tft.setTextSize(2);
            ui->tft.print("Button 1 yay");
        })
    });
    ui->init();
    interface->draw();
    /*delay(300);
    interface->container->cycle(1);
    interface->container->click();
    delay(300);
    interface->container->cycle(1);
    interface->container->click();
    delay(300);
    interface->container->cycle(1);
    interface->container->click();*/
    while(true);
}

void loop()
{
}
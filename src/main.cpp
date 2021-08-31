#include <Arduino.h>
#include <ui.hpp>
#include <io.hpp>


#define SCREEN_HEIGHT (320)
#define SCREEN_WIDTH (240)
void setup()
{
    Serial.begin(115200);
    ui::UI *ui = new ui::UI;
    ui::Interface *interface = new ui::Interface(ui, {
        new ui::Container({
            new ui::StaticButton(0, 0, 26, 26, TFT_MAGENTA, TFT_WHITE, ui, [](ui::UI *ui)
            {
                Serial.println("Home:");
                ui->tft.setCursor(20, 150);
                ui->tft.setTextColor(TFT_WHITE);
                ui->tft.setTextSize(2);
                ui->tft.print("Home");
            })
        }),
        new ui::Container({
            new ui::StaticButton(0, SCREEN_HEIGHT-26, SCREEN_WIDTH/2, 26, TFT_BLUE, TFT_BLACK, ui, [](ui::UI *ui)
            {
                Serial.println("Menu:");
                ui->tft.setCursor(20, 150);
                ui->tft.setTextColor(TFT_WHITE);
                ui->tft.setTextSize(2);
                ui->tft.print("Menu");
            }),
            new ui::TextButton(SCREEN_WIDTH/2, SCREEN_HEIGHT-26, "keyboard", 2, TFT_GREEN, TFT_BLACK, TFT_BLACK, ui, [](ui::UI *ui)
            {
                Serial.println("Keyb:");
                ui->tft.setCursor(20, 150);
                ui->tft.setTextColor(TFT_WHITE);
                ui->tft.setTextSize(2);
                ui->tft.print("Keyb");
            })
        })
    });
    pcfinit();
    ui->init();
    interface->draw();
    while (true){
        unsigned int buttonstates = readallbuttons();
        if(buttonstates & 0b1){
            interface->clickcontainer();
        }
        if(buttonstates & 0b10){
            interface->cyclecontainer(1);
        }
        if(buttonstates & 0b100){
            interface->cycle(1);
        }
        if(buttonstates & 0b1000){
            interface->selectcontainer(-1);
        }
        delay(50); //need this delay or the pcf chip freaks out
    }
}

void loop()
{
}
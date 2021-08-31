#include <Arduino.h>
#include <ui.hpp>
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
            new ui::TextButton(SCREEN_WIDTH/2, SCREEN_HEIGHT-26, "keyboard", 2, TFT_GREEN, TFT_BLACK, TFT_WHITE, ui, [](ui::UI *ui)
            {
                Serial.println("Keyb:");
                ui->tft.setCursor(20, 150);
                ui->tft.setTextColor(TFT_WHITE);
                ui->tft.setTextSize(2);
                ui->tft.print("Keyb");
            })
        })
    });
    ui->init();
    interface->draw();
    delay(2000);
    interface->cycle(1);
    interface->clickcontainer();
    delay(2000);
    interface->cycle(1);
    interface->clickcontainer();
    delay(2000);
    interface->cyclecontainer(1);
    interface->clickcontainer();
    while (true);
}

void loop()
{
}
#define LGFX_USE_V1
#include <LovyanGFX.hpp>
#include <vector>
class LGFX : public lgfx::LGFX_Device
{
    lgfx::Panel_ILI9341 _panel_instance;
    lgfx::Bus_SPI _bus_instance;

public:
    LGFX(void);
};

namespace ui
{
    class UI
    {
    public:
        UI();
        void init();
        LGFX tft;
    };
    class Button
    {
    public:
        virtual ~Button() = 0;
        virtual void draw();
        virtual void select(bool selected);
        int x, y, w, h;
        bool selected;
        UI *ui;
    };
    class StaticButton : public virtual Button
    {
    public:
        StaticButton(int x, int y, int w, int h, UI *ui);
    };
    class Buttons
    {
    public:
        std::vector<Button*> buttons;
        Buttons(std::vector<Button*> buttons);
        void draw();
    };
    class Interface
    {
    public:
        Interface(UI *ui, Buttons *buttons);
        UI *ui;
        Buttons *buttons;
        void draw();
    };
}

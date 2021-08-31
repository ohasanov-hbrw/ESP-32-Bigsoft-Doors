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
    class Object
    {
    public:
        virtual ~Object() = 0;
        virtual void draw();
        virtual void select(bool selected);
        void (*action)(UI *);
        int x, y, w, h;
        bool selected;
        UI *ui;
    };
    class StaticButton : public virtual Object
    {
    public:
        StaticButton(int x, int y, int w, int h, UI *ui, void (*action)(UI *));
    };
    class Container
    {
    public:
        std::vector<Object *> objects;
        Container(std::vector<Object *> objects);
        int index;
        void draw();
        void cycle(int cycles);
        void click();
    };
    class Interface
    {
    public:
        Interface(UI *ui, std::vector<Container *> container);
        UI *ui;
        int selectedcontainer = -1;
        std::vector<Container *> container;
        void cycle(int cycles);
        void cyclecontainer(int cycles);
        void clickcontainer();
        void draw();
    };
}

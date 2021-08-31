#define LGFX_USE_V1
#define FONT_HEIGHT (8)
#define FONT_WIDTH (6)
#include <LovyanGFX.hpp>
#include <vector>
#include <string>
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
        virtual void drawoutline();
        virtual void select(bool selected);
        void (*action)(UI *);
        int x, y, w, h, selectedcolor;
        bool selected;
        UI *ui;
    };
    class StaticButton : public virtual Object
    {
    public:
        StaticButton(int x, int y, int w, int h, int color, int selectedcolor, UI *ui, void (*action)(UI *));
        int color;
        void draw() override;
    };
    class TextButton : public virtual Object
    {
    public:
        TextButton(int x, int y, std::string text, int h, int color, int selectedcolor, int textcolor, UI *ui, void (*action)(UI *));
        std::string text;
        int textcolor;
        int color;
        void draw() override;
    };
    class Container
    {
    public:
        std::vector<Object *> objects;
        Container(std::vector<Object *> objects);

        int index;
        void selectindex(int index);
        void deselect();
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
        void selectcontainer(int selectedcontainer);
        void cyclecontainer(int cycles);
        void clickcontainer();
        void draw();
    };
}

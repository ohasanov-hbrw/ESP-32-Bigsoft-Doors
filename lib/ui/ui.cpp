#include <ui.hpp>

LGFX::LGFX(void)
{
    {
        auto cfg = _bus_instance.config();

        cfg.spi_host = VSPI_HOST;
        cfg.spi_mode = 0;
        cfg.freq_read = 20000000;
        cfg.freq_write = 40000000;
        cfg.spi_3wire = false;
        cfg.use_lock = true;

        cfg.dma_channel = 1;
        cfg.pin_sclk = 18;
        cfg.pin_mosi = 23;
        cfg.pin_miso = 19;
        cfg.pin_dc = 2;

        _bus_instance.config(cfg);
        _panel_instance.setBus(&_bus_instance);
    }

    {
        auto cfg = _panel_instance.config();

        cfg.pin_cs = 15;
        cfg.pin_rst = 4;
        cfg.pin_busy = -1;

        cfg.memory_width = 240;
        cfg.memory_height = 320;
        cfg.panel_width = 240;
        cfg.panel_height = 320;
        cfg.offset_x = 0;
        cfg.offset_y = 0;
        cfg.offset_rotation = 0;
        cfg.dummy_read_pixel = 8;
        cfg.dummy_read_bits = 1;
        cfg.readable = true;
        cfg.invert = false;
        cfg.rgb_order = false;
        cfg.dlen_16bit = false;
        cfg.bus_shared = true;
        _panel_instance.config(cfg);
    }
    setPanel(&_panel_instance);
}

ui::Object::~Object() {}

void ui::Object::draw()
{
    this->ui->tft.fillRect(this->x, this->y, this->w, this->h, TFT_BLACK);
    this->drawoutline();
}

void ui::StaticButton::draw()
{
    this->ui->tft.fillRect(this->x, this->y, this->w, this->h, this->color);
    this->drawoutline();
}

void ui::TextButton::draw()
{
    this->ui->tft.setCursor(this->x, this->y);
    this->ui->tft.setTextSize(this->h/FONT_HEIGHT);
    this->ui->tft.setTextColor(this->textcolor);
    this->ui->tft.fillRect(this->x, this->y, this->w, this->h, this->color);
    this->ui->tft.print(this->text.c_str());
    this->drawoutline();
}

void ui::Object::drawoutline(){
    if(this->selected) this->ui->tft.drawRect(this->x, this->y, this->w, this->h, this->selectedcolor);
}

void ui::Object::select(bool selected)
{
    if (this->selected != selected)
    {
        this->selected = selected;
        this->draw();
    }
}

ui::StaticButton::StaticButton(int x, int y, int w, int h, int color, int selectedcolor, UI *ui, void (*action)(UI *))
{
    selected = false;
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
    this->ui = ui;
    this->action = action;
    this->color = color;
    this->selectedcolor = selectedcolor;
}

ui::TextButton::TextButton(int x, int y, std::string text, int h, int color, int selectedcolor, int textcolor, UI *ui, void (*action)(UI *))
{
    selected = false;
    this->x = x;
    this->y = y;
    this->w = h*(text.length())*FONT_WIDTH;
    this->h = h*FONT_HEIGHT;
    this->ui = ui;
    this->action = action;
    this->color = color;
    this->selectedcolor = selectedcolor;
    this->text = text;
    this->textcolor = textcolor;
}

ui::UI::UI(){};

void ui::UI::init()
{
    this->tft.init();
    this->tft.setRotation(0);
    this->tft.fillScreen(TFT_RED);
};

ui::Container::Container(std::vector<Object *> objects)
{
    this->objects = objects;
    this->index = -1;
}

void ui::Container::draw()
{
    for (auto thing : this->objects)
        thing->draw();
}

ui::Interface::Interface(UI *ui, std::vector<Container *> container)
{
    this->container = container;
    this->ui = ui;
}
void ui::Interface::draw()
{
    for (auto thing : this->container)
        thing->draw();
}

void ui::Container::cycle(int cycles)
{
    if (this->index >= 0)
        this->objects[this->index]->select(false);
    if(this->objects.size() > 0){
        this->index = (this->index + cycles) % this->objects.size();
        this->objects[this->index]->select(true);
    }
}

void ui::Container::click()
{
    if (this->index < 0 || this->index >= this->objects.size())
        return;
    this->objects[this->index]->action(this->objects[index]->ui);
}

void ui::Interface::cycle(int cycles)
{
    if (this->selectedcontainer >= 0) this->container[selectedcontainer]->deselect();
    if (this->container.size() > 0){
        this->selectedcontainer = (this->selectedcontainer + cycles) % this->container.size();
        this->container[this->selectedcontainer]->cycle(1);
    }
}

void ui::Interface::cyclecontainer(int cycles)
{
    if (this->selectedcontainer >= 0 && this->selectedcontainer < this->container.size())
        this->container[this->selectedcontainer]->cycle(cycles);
}

void ui::Interface::clickcontainer()
{
    if (this->selectedcontainer >= 0 && this->selectedcontainer < this->container.size())
        this->container[this->selectedcontainer]->click();
}

void ui::Container::deselect(){
    if(this->index >= 0) this->objects[index]->select(false);
    this->index = -1;
}

void ui::Interface::selectcontainer(int selectedcontainer){
    if(this->container.size() > 0) this->selectedcontainer = selectedcontainer % this->container.size();
}

void ui::Container::selectindex(int index){
    if(this->objects.size() > 0) this->index = index % this->objects.size();
}
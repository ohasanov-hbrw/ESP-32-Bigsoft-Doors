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

ui::Button::~Button() {}

void ui::Button::draw()
{
    this->ui->tft.fillRect(this->x, this->y, this->w, this->h, TFT_BLUE);
    this->selected && [&]() {
        this->ui->tft.drawRect(this->x, this->y, this->w, this->h, TFT_WHITE);
        return false;
    }();
}

void ui::Button::select(bool selected) {
    if(this->selected != selected){
        this->selected = selected;
        this->draw();
    }
}

ui::StaticButton::StaticButton(int x, int y, int w, int h, UI *ui)
{
    selected = false;
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
    this->ui = ui;
}

ui::UI::UI(){};

void ui::UI::init()
{
    this->tft.init();
    this->tft.setRotation(0);
    this->tft.fillScreen(TFT_RED);
};

ui::Buttons::Buttons(std::vector<Button*> buttons)
{
    this->buttons = buttons;
}

void ui::Buttons::draw()
{
    for (auto button : this->buttons)
    {   
        button->draw();
    }
}

ui::Interface::Interface(UI *ui, Buttons *buttons)
{
    this->buttons = buttons;
    this->ui = ui;
}
void ui::Interface::draw(){
    this->buttons->draw();
}
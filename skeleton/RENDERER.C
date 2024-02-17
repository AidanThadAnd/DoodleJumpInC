#include "MODEL.H"
#include "RASTER.H"
#include "BITMAP.H"
#include "RENDERER.H"

void render(const Model *model, UINT32 *base)
{

    render_doodle(&(model->doodle), base);
    render_monster(&(model->monster), base);
    /*render_platform(model->platforms, base);*/
}

void render_doodle(const Doodle *doodle, UINT32 *base)
{

    plot_bitmap_32(base, doodle->x, doodle->y, doodle_bitmap, DOODLE_HEIGHT);

}

void render_monster(const Monster *monster, UINT32 *base)
{

    plot_bitmap_32(base, monster->x, monster->y, monster_bitmap, MONSTER_HEIGHT);

}

void render_platform(const Platform *platform, UINT32 *base)
{
    int total_platform = sizeof(*platform);
    plot_bitmap_32(base, platform->x, platform->y, platform_bitmap, PLATFORM_HEIGHT);

}
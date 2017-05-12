#include "render_geometry.hpp"
#include "model.hpp"
#include "tgaimage.hpp"
#include "viewmatrix.hpp"
#include "z_buffer.hpp"
#include <cmath>
#include <chrono>

const static std::string base_dir = "obj/african_head/";
const static std::string tex_file = base_dir + "diffuse.tga";
const static std::string obj_file = base_dir + "model.obj";

int main(int argc, char** argv)
{
    using std::chrono::high_resolution_clock;
    using std::chrono::duration;
    using std::chrono::duration_cast;

    const auto window_width = 1000;
    const auto window_height = 1000;
    const auto camera_distance = 3.0f;

    TGAImage image(window_width, window_height, TGAImage::RGB);
    TGAImage tex;
    tex.read_tga_file(tex_file.c_str());
    tex.flip_vertically();
    z_buffer zbuf(window_width, window_height);

    auto model_ptr = load_model(obj_file.c_str());

    auto starttime = high_resolution_clock::now();
    render_model(image, tex, zbuf, *model_ptr,
            glm::vec3 {window_width / 2, window_height / 2, 1},
            glm::vec3 {window_width / 2, window_height / 2, 0});
    auto endtime = high_resolution_clock::now();

    auto render_time = duration_cast<duration<double>>(endtime - starttime);
    printf("Render took: %f seconds\n", render_time.count());

    image.flip_vertically(); // move origin to the bottom-left corner
    image.write_tga_file("output.tga");

    return 0;
}

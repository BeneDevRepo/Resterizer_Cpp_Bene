/*

#include <iostream>
#include <cstdlib>
#include <cstdint>
#include <cmath>
#include <windows.h>

#include "linear.hh"
#include "hash_map.hh"
#include "draw.hh"
#include "input.hh"

LRESULT WINAPI _wnd_proc(HWND wnd, UINT msg, WPARAM wparam, LPARAM lparam) {
    switch (msg) {
        case WM_CLOSE:
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default: 
            return DefWindowProcW(wnd, msg, wparam, lparam);
    }
    return 0;
}

int width = 800;
int height = 600;

vec3_t *_transformed;
vec3_t *_bound;
size_t _size = 0;

void *_last_bound = NULL;

void transform(void *vectors, size_t count, vec3_t(*op)(vec3_t)) {
    _bound = (vec3_t*)vectors;

    if (!_transformed || count > _size) {
        _transformed = new vec3_t[count];//(vec3_t*)malloc(count * sizeof(vec3_t));
        _size = count;
    }

    vec3_t *vptr = (vec3_t*)vectors;

    for (int i = 0; i < count; i++) {
        _transformed[i] = op(vptr[i]);
    }
}

vec<float, 3> i = {100, 100, 100};

const float FAR_DIST = 15000.0f;
const float NEAR_DIST = 10.0f;

const vec3_t _face_limit = {0, 0, 1};

void draw_array(uint32_t *buffer, size_t triangle_count, uint32_t color)
{
    vec3_t *vptr = (vec3_t*)transform;
    for (size_t i = 0; i < triangle_count; i++)
    {
        if (vptr[0].z <= FAR_DIST || vptr[1].z <= FAR_DIST || vptr[2].z <= FAR_DIST)
            goto cont1;

        // vec2_t v[3] = {
        //     { vptr[0].x / (vptr[0].z * 0.001) + width / 2, vptr[0].y / (vptr[0].z * 0.001) + height / 2}, 
        //     { vptr[1].x / (vptr[1].z * 0.001) + width / 2, vptr[1].y / (vptr[1].z * 0.001) + height / 2}, 
        //     { vptr[2].x / (vptr[2].z * 0.001) + width / 2, vptr[2].y / (vptr[2].z * 0.001) + height / 2}, 
        // };
        vec2_t v[3];
        v[0] = vec2_t{(float)(vptr[0].x / (vptr[0].z * 0.001) + width / 2), (float)(vptr[0].y / (vptr[0].z * 0.001) + height / 2)};
        v[1] = vec2_t{(float)(vptr[1].x / (vptr[1].z * 0.001) + width / 2), (float)(vptr[1].y / (vptr[1].z * 0.001) + height / 2)}; 
        v[2] = vec2_t{(float)(vptr[2].x / (vptr[2].z * 0.001) + width / 2), (float)(vptr[2].y / (vptr[2].z * 0.001) + height / 2)}; 

        plot_line(buffer, v[0].x, v[0].y, v[1].x, v[1].y, color);
        plot_line(buffer, v[1].x, v[1].y, v[2].x, v[2].y, color);
        plot_line(buffer, v[2].x, v[2].y, v[0].x, v[0].y, color);

cont1:
        vptr += 3;
    }
}

vec3_t vertex_shader(vec3_t v);

void draw_indices(uint32_t *buffer, void *indices, size_t triangle_count, uint32_t color) {
    vec3_t *vptr = (vec3_t*)_transformed;
    int *iptr = (int*)indices;

    for (size_t i = 0; i < triangle_count; i++) {
        if (vptr[iptr[0]].z <= NEAR_DIST || vptr[iptr[1]].z <= NEAR_DIST || vptr[iptr[2]].z <= NEAR_DIST)
        goto cont2;
        if (vptr[iptr[0]].z > FAR_DIST || vptr[iptr[1]].z > FAR_DIST || vptr[iptr[2]].z > FAR_DIST)
        goto cont2;

        vec2_t v[3];
        v[0] = { (float)(vptr[iptr[0]].x / (vptr[iptr[0]].z * 0.001) + width / 2), (float)(vptr[iptr[0]].y / (vptr[iptr[0]].z * 0.001) + height / 2)}; 
        v[1] = { (float)(vptr[iptr[1]].x / (vptr[iptr[1]].z * 0.001) + width / 2), (float)(vptr[iptr[1]].y / (vptr[iptr[1]].z * 0.001) + height / 2)}; 
        v[2] = { (float)(vptr[iptr[2]].x / (vptr[iptr[2]].z * 0.001) + width / 2), (float)(vptr[iptr[2]].y / (vptr[iptr[2]].z * 0.001) + height / 2)}; 
        

        if (v[0].x < 0 && v[1].x < 0 && v[2].x < 0) goto cont2;
        if (v[0].y < 0 && v[1].y < 0 && v[2].y < 0) goto cont2;
        if (v[0].x >= width && v[1].x >= width && v[2].x >= width) goto cont2;
        if (v[0].y >= height && v[1].y >= height && v[2].y >= height) goto cont2;

        plot_line(buffer, v[0].x, v[0].y, v[1].x, v[1].y, color);
        plot_line(buffer, v[1].x, v[1].y, v[2].x, v[2].y, color);
        plot_line(buffer, v[2].x, v[2].y, v[0].x, v[0].y, color);


        plot_triangle(
                buffer, 
                vptr[iptr[0]].x, vptr[iptr[0]].y, 
                vptr[iptr[1]].x, vptr[iptr[1]].y, 
                vptr[iptr[2]].x, vptr[iptr[2]].y, 
                color
                );


cont2:
        iptr += 3;
    }
}

static int _mouse_delta_x = 0;
static int _mouse_delta_y = 0;


static hash_map_t *uniforms = NULL;
#define write_uniform(name, value) (hash_map_insert(uniforms, name, &value)) 
#define read_uniform(name, type) (*(type*)hash_map_get(uniforms, name)) 

vec3_t vertex_shader(vec3_t v) {
    vec3_t scale = read_uniform("scale", vec3_t);
    vec3_t position = read_uniform("pos", vec3_t);
    vec2_t mouse = read_uniform("mouse", vec2_t);

    float angle = read_uniform("angle", float);
    vec3_t local_pos = read_uniform("lpos", vec3_t);

    v = vec3_mul(v, scale);
    v = vec3_mul_mat3(v, mat3_rotate_y(angle));
    v = vec3_mul_mat3(v, mat3_rotate_x(angle));
    v = vec3_add(v, position);
    v = vec3_add(v, local_pos);
    v = vec3_mul_mat3(v, mat3_rotate_y(mouse.x));
    v = vec3_mul_mat3(v, mat3_rotate_x(mouse.y));

    return v;
}

int main(void) {
    printf("Hello World!\n");

    uniforms = hash_map_init();

    WNDCLASSW win_class = {0};
    win_class.hInstance = GetModuleHandle(NULL);
    win_class.hCursor = LoadCursor(NULL, IDC_ARROW);
    win_class.lpszClassName = L"CLASS";
    win_class.lpfnWndProc = _wnd_proc;

    int r = RegisterClassW(&win_class);
    if (!r) 
    {
        printf("Err: %i\n", GetLastError());
        exit(-1);
    }

    RECT win_rect = {0, 0, width, height};
    AdjustWindowRect(&win_rect, WS_OVERLAPPEDWINDOW, false);

    HWND wnd = CreateWindowExW(
            0,
            win_class.lpszClassName,
            win_class.lpszClassName,
            WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            win_rect.right - win_rect.left,
            win_rect.bottom - win_rect.top,
            NULL, NULL, NULL, NULL
            );

    ShowWindow(wnd, SW_SHOW);
    UpdateWindow(wnd);

    HDC device_context = GetDC(wnd);

    BITMAPINFO bi = {0};
    bi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bi.bmiHeader.biBitCount = 32;
    bi.bmiHeader.biPlanes = 1;
    bi.bmiHeader.biCompression = BI_RGB;
    bi.bmiHeader.biWidth = width;
    bi.bmiHeader.biHeight = height;

    uint32_t *buffer = (uint32_t*)malloc(width * height * sizeof(uint32_t)); 

    int x = 0;

    float vertices[] {
         0.5f,-0.5f,-0.5f,
         0.5f,-0.5f, 0.5f,
        -0.5f,-0.5f, 0.5f,
        -0.5f,-0.5f,-0.5f,
         0.5f, 0.5f,-0.5f,
         0.5f, 0.5f, 0.5f,
        -0.5f, 0.5f, 0.5f,
        -0.5f, 0.5f,-0.5f
    };

    int indices[] {
        0, 2, 3,
        0, 1, 2,
        0, 5, 4,
        0, 1, 5,
        4, 0, 3,
        4, 3, 7,
        4, 5, 6,
        6, 7, 4,
        5, 1, 2,
        2, 6, 5,
        3, 2, 6,
        3, 6, 7
    };

    vec3_t scale {100.0f, 100.0f, 100.0f};

    float dt = 0.0f;

    vec3_t position = {0.0f, 0.0f, 200.0f};
    vec3_t lp = {0.0f, 0.0f, 0.0f};
    vec2_t mouse = {0.0f, 0.0f};

    constexpr const int  MAX_CUBES = 100;

    float angles[MAX_CUBES] = {0};
    vec3_t positions[MAX_CUBES] = {0};
    unsigned colors[MAX_CUBES] = {0};

    for (int i = 0; i < MAX_CUBES; i++) {
        angles[i] = (rand() % 1000) / 10.0f;
        positions[i].x = (float)(rand() % 5000) - 2500.0f;
        positions[i].y = (float)(rand() % 5000) - 2500.0f;
        positions[i].z = (float)(rand() % 5000) - 2500.0f;

#define COLOR(r, g, b) (1 | ((r) << 16) | ((g) << 8) | (b))

        colors[i] = COLOR(
                rand() % 255,
                rand() % 255,
                rand() % 255
                );
    }

    MSG msg;
    LARGE_INTEGER beg, end, freq;
    bool running = true;

    write_uniform("scale", scale);
    write_uniform("pos", position);
    write_uniform("mouse", mouse);

    while (running) {
        QueryPerformanceCounter(&beg);

        if (PeekMessageW(&msg, NULL, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessageW(&msg);

            if (msg.message == WM_QUIT) 
                running = false;
        }

        
        GetKeyboardState(_keys);// get_keys();
        POINT last_mouse_pos = get_mouse(wnd);

#define MOV_VEL 300.0f
// #define PI 3.1416f
// #define HALF_PI 1.5708f
    constexpr const int HALF_PI = 3.1415926535/2;
#define LEFT_CLICK 0x01

        if (key_pressed('W')) {
           position.x +=  MOV_VEL * sin(mouse.x) * dt; 
           position.z -=  MOV_VEL * cos(mouse.x) * cos(mouse.y) * dt; 
        }
        
        if (key_pressed('A')) {
           position.x += MOV_VEL * sin(mouse.x + HALF_PI) * dt; 
           position.z -= MOV_VEL * cos(mouse.x + HALF_PI) * dt; 
        }

        if (key_pressed('S')) {
           position.x -=  MOV_VEL * sin(mouse.x) * dt; 
           position.z +=  MOV_VEL * cos(mouse.x) * cos(mouse.y) * dt;  
        }

        if (key_pressed('D')) {
           position.x += MOV_VEL * sin(mouse.x - HALF_PI) * dt; 
           position.z -= MOV_VEL * cos(mouse.x - HALF_PI) * dt; 
        }

        if (key_pressed(LEFT_CLICK)) {
            mouse.x += _mouse_delta_x * dt;
            mouse.y += _mouse_delta_y * dt;
        }


        clear(buffer, 0x00);

        for (int i = 0; i < MAX_CUBES; i++) {
            write_uniform("angle", angles[i]);
            write_uniform("lpos", positions[i]);

            transform(vertices, 8, vertex_shader);
            
            draw_indices(buffer, indices, sizeof(indices) / 32 * 3, colors[i]);
            
            angles[i] += 1.0f * dt;
        }

        SetDIBitsToDevice(
                device_context,
                0, 0,
                width, height,
                0, 0,
                0,
                height,
                buffer,
                &bi,
                DIB_RGB_COLORS
                );

        
        POINT recent_mouse_pos = get_mouse(wnd);
        _mouse_delta_x = recent_mouse_pos.x - last_mouse_pos.x;
        _mouse_delta_y = recent_mouse_pos.y - last_mouse_pos.y;

        QueryPerformanceCounter(&end);
        QueryPerformanceFrequency(&freq);

        dt = (float)(end.QuadPart - beg.QuadPart) / freq.QuadPart;
        float fps = 1 / dt;

        char msg[255];
        sprintf(msg, "%f fps", fps);

        RECT rect = {0, 0, 200, 100};

        DrawTextA(device_context, msg, strlen(msg), &rect, DT_BOTTOM);
    }

    ReleaseDC(wnd, device_context);
    DestroyWindow(wnd);
    free(buffer);

    hash_map_terminate(uniforms);

    return 0;
}
*/

int width, height;

#include "linear.hh"
#include "hash_map.hh"
#include <iostream>

using vec3f = vec<float, 3>;
using mat3f = mat<float, 3, 3>;

template <typename _Type, int _Length>
std::ostream& operator<<(std::ostream& os, vec<_Type, _Length> const& v) {
    printf("vec<%i>[", _Length);
    for (int i = 0; i < _Length - 1; i++)
        std::cout << v.v[i] << ", ";
    
    std::cout << v.v[_Length - 1] << ']';
    return os;
}

int main() {
    vec3f v = {100.f, 100.f, 100.f};

    hash_map<int> map;
    map.insert("One", 1);
    map.insert("Two", 2);
    map.insert("three", 3);
    map.insert("nine", 9);
    map.insert("four", 4);
    map.insert("five", 5);
    map.insert("six", 6);

    std::cout << "Output 1: " << map.get("One") << "\n";
    std::cout << "Output 3: " << map.get("three") << "\n";
    std::cout << "Output 9: " << map.get("nine") << "\n";
    std::cout << "Output 6: " << map.get("six") << "\n";
    std::cout << "Output 5: " << map.get("five") << "\n";
    std::cout << "Output 4: " << map.get("four") << "\n";

    mat3f m = {
        1.f, 0.f, 0.f,
        0.f, 1.f, 0.f,
        0.f, 0.f, 1.f
    };

    vec3f v1 = v * m;
    std::cout << v1 << "\n";
    std::cout << v1.v[1] << "\n";

    //test
}